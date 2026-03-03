#!/usr/bin/env python3
"""
cub3D Live Map Viewer
Usage: python3 viewer.py <map.cub>
Then open http://localhost:8042 in your browser.
"""

import sys
import os
import http.server
import json
import time

if len(sys.argv) < 2:
    print("Usage: python3 viewer.py <fichier.cub>")
    print("Exemple: python3 viewer.py maps/dungeon.cub")
    sys.exit(1)

CUB_FILE = sys.argv[1]
PORT = 8042

if not os.path.exists(CUB_FILE):
    print(f"Erreur: fichier '{CUB_FILE}' introuvable")
    sys.exit(1)

HTML = r'''<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>cub3D Live Viewer</title>
<style>
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body { background: #1a1a2e; color: #eee; font-family: 'Segoe UI', monospace; padding: 20px; }
  h1 { color: #e94560; margin-bottom: 4px; }
  #filename { color: #aaa; font-size: 13px; margin-bottom: 10px; }
  #live-dot { display: inline-block; width: 8px; height: 8px; border-radius: 50%;
    background: #4ade80; margin-right: 6px; animation: pulse 1.5s infinite; }
  @keyframes pulse { 0%,100% { opacity: 1; } 50% { opacity: 0.3; } }
  .legend { display: flex; gap: 12px; margin: 8px 0; flex-wrap: wrap; font-size: 13px; }
  .legend-item { display: flex; align-items: center; gap: 5px; }
  .legend-box { width: 14px; height: 14px; border: 1px solid #555; border-radius: 2px; }
  #stats { color: #aaa; margin: 8px 0; font-size: 14px; }
  #errors { margin: 6px 0; font-size: 13px; white-space: pre-wrap; }
  .err { color: #ff6b6b; }
  .ok { color: #4ade80; }
  .controls { margin: 8px 0; display: flex; gap: 10px; align-items: center; font-size: 13px; }
  .controls label { color: #aaa; }
  canvas { border: 2px solid #e94560; image-rendering: pixelated; cursor: crosshair; display: block; margin-top: 8px; }
  #info { color: #aaa; margin-top: 6px; font-size: 14px; height: 20px; }
</style>
</head>
<body>

<h1><span id="live-dot"></span>cub3D Live Viewer</h1>
<div id="filename"></div>
<div class="legend">
  <div class="legend-item"><div class="legend-box" style="background:#444"></div> Mur (1)</div>
  <div class="legend-item"><div class="legend-box" style="background:#c8b896"></div> Sol (0)</div>
  <div class="legend-item"><div class="legend-box" style="background:#6a4c93"></div> Anim (2)</div>
  <div class="legend-item"><div class="legend-box" style="background:#8B4513"></div> Porte (D)</div>
  <div class="legend-item"><div class="legend-box" style="background:#FFD700"></div> Cle (K)</div>
  <div class="legend-item"><div class="legend-box" style="background:#FF0000"></div> Enderman (M)</div>
  <div class="legend-item"><div class="legend-box" style="background:#00FF00"></div> Spawn (N/S/E/W)</div>
</div>
<div id="stats"></div>
<div id="errors"></div>
<div class="controls">
  <label>Zoom: </label>
  <input type="range" id="zoom" min="2" max="20" value="9">
  <span id="zoom-val">9</span>px
  <label style="margin-left:12px">Grille: </label>
  <input type="checkbox" id="grid-toggle" checked>
  <span id="last-update" style="margin-left: auto; color: #555; font-size: 12px;"></span>
</div>
<canvas id="map"></canvas>
<div id="info"></div>

<script>
var mapData = [], mapW = 0, mapH = 0, scale = 9, showGrid = true;
var lastHash = "";

var colors = {
  "1":"#444444","0":"#c8b896","2":"#6a4c93",
  "D":"#8B4513","K":"#FFD700","M":"#FF0000",
  "N":"#00FF00","S":"#00FF00","E":"#00FF00","W":"#00FF00",
  " ":"#111111"
};
var tnames = {
  "1":"Mur","0":"Sol","D":"Porte","K":"Cle","M":"Enderman",
  "N":"Spawn N","S":"Spawn S","E":"Spawn E","W":"Spawn W",
  "2":"Mur anime"," ":"Vide"
};

function parseCub(text) {
  var lines = text.split("\n");
  var ml = [], inMap = false, cfg = {f:"",c:""}, errors = [];
  for (var i = 0; i < lines.length; i++) {
    var line = lines[i].replace(/\r$/, "");
    var t = line.trim();
    if (!inMap) {
      if (t.indexOf("F ") === 0) { cfg.f = t; continue; }
      if (t.indexOf("C ") === 0) { cfg.c = t; continue; }
      if (/^[NO|SO|WE|EA]/.test(t) && t.indexOf(" ") > 0) continue;
      if (t === "") continue;
      if (/^[01 \tDKMNSEW2]+$/.test(line)) inMap = true;
      else continue;
    }
    if (inMap) {
      if (t === "") break;
      ml.push(line.replace(/\t/g, " "));
    }
  }
  var maxW = 0;
  for (var j = 0; j < ml.length; j++) { if (ml[j].length > maxW) maxW = ml[j].length; }

  var cts = {doors:0,keys:0,endermen:0,spawns:0,floors:0};
  var shortLines = [];
  for (var y = 0; y < ml.length; y++) {
    if (ml[y].length < maxW) shortLines.push({row:y+1, len:ml[y].length});
    while (ml[y].length < maxW) ml[y] += "1";
    for (var x = 0; x < ml[y].length; x++) {
      var c = ml[y][x];
      if (c==="D") cts.doors++;
      if (c==="K") cts.keys++;
      if (c==="M") cts.endermen++;
      if ("NSEW".indexOf(c)>=0) cts.spawns++;
      if (c==="0") cts.floors++;
    }
  }

  if (cts.spawns!==1) errors.push("Spawns: "+cts.spawns+" (doit etre 1)");
  if (cts.doors>64) errors.push("Portes: "+cts.doors+" (max 64)");
  if (cts.keys>64) errors.push("Cles: "+cts.keys+" (max 64)");
  if (cts.endermen>32) errors.push("Endermen: "+cts.endermen+" (max 32)");
  for (var s = 0; s < shortLines.length; s++) {
    errors.push("Ligne "+shortLines[s].row+": "+shortLines[s].len+" chars (attendu "+maxW+")");
  }

  for (var y = 0; y < ml.length; y++) {
    for (var x = 0; x < ml[y].length; x++) {
      var c = ml[y][x];
      if ("0DKMNSEW".indexOf(c)>=0) {
        if (y===0||y===ml.length-1||x===0||x===ml[y].length-1)
          errors.push("Bordure ouverte: '"+c+"' en ("+x+","+y+")");
        var dirs = [[-1,0],[1,0],[0,-1],[0,1]];
        for (var d=0;d<4;d++) {
          var ny=y+dirs[d][0], nx=x+dirs[d][1];
          if (ny>=0&&ny<ml.length&&nx>=0&&nx<ml[ny].length) {
            if (ml[ny][nx]===" ") errors.push("Espace adjacent: '"+c+"' ("+x+","+y+") -> ("+nx+","+ny+")");
          }
        }
      }
    }
  }

  return {map:ml, w:maxW, h:ml.length, counts:cts, errors:errors, config:cfg};
}

function draw() {
  var canvas = document.getElementById("map");
  var ctx = canvas.getContext("2d");
  canvas.width = mapW * scale;
  canvas.height = mapH * scale;
  for (var y = 0; y < mapH; y++) {
    for (var x = 0; x < mapW; x++) {
      var c = (x<mapData[y].length)?mapData[y][x]:"1";
      ctx.fillStyle = colors[c]||"#111";
      ctx.fillRect(x*scale, y*scale, scale, scale);
    }
  }
  if (showGrid && scale >= 5) {
    ctx.strokeStyle = "rgba(255,255,255,0.06)";
    ctx.lineWidth = 0.5;
    for (var i=0;i<=Math.max(mapW,mapH);i++) {
      ctx.beginPath();ctx.moveTo(i*scale,0);ctx.lineTo(i*scale,mapH*scale);ctx.stroke();
      ctx.beginPath();ctx.moveTo(0,i*scale);ctx.lineTo(mapW*scale,i*scale);ctx.stroke();
    }
  }
}

function loadMap(text) {
  var result = parseCub(text);
  mapData = result.map;
  mapW = result.w;
  mapH = result.h;
  var c = result.counts;
  document.getElementById("stats").innerHTML =
    "<b>"+mapW+"x"+mapH+"</b> | "+
    "<b>"+c.doors+"</b> Portes | "+
    "<b>"+c.keys+"</b> Cles | "+
    "<b>"+c.endermen+"</b> Endermen | "+
    "<b>"+c.floors+"</b> Sol";
  var errEl = document.getElementById("errors");
  if (result.errors.length > 0) {
    errEl.className = "err";
    var unique = result.errors.filter(function(v,i,a){return a.indexOf(v)===i;});
    errEl.textContent = unique.slice(0,10).map(function(e){return "\u26a0 "+e;}).join("\n");
    if (unique.length > 10) errEl.textContent += "\n... et "+(unique.length-10)+" autres erreurs";
  } else {
    errEl.className = "ok";
    errEl.textContent = "\u2705 Map valide !";
  }
  draw();
}

function simpleHash(s) {
  var h = 0;
  for (var i = 0; i < s.length; i++) { h = ((h << 5) - h + s.charCodeAt(i)) | 0; }
  return h.toString(36);
}

function poll() {
  fetch("/map?" + Date.now())
    .then(function(r) { return r.json(); })
    .then(function(data) {
      document.getElementById("filename").textContent = data.filename;
      var h = simpleHash(data.content);
      if (h !== lastHash) {
        lastHash = h;
        loadMap(data.content);
        var now = new Date();
        document.getElementById("last-update").textContent =
          "Mis a jour: " + now.toLocaleTimeString();
      }
    })
    .catch(function(){});
}

setInterval(poll, 500);
poll();

var firstLoad = true;
var observer = new MutationObserver(function() {
  if (firstLoad && mapW > 0) {
    firstLoad = false;
    var maxPx = Math.min(window.innerWidth - 60, 900);
    scale = Math.max(2, Math.min(20, Math.floor(maxPx / Math.max(mapW, mapH))));
    document.getElementById("zoom").value = scale;
    document.getElementById("zoom-val").textContent = scale;
    draw();
  }
});
observer.observe(document.getElementById("stats"), {childList:true});

document.getElementById("zoom").addEventListener("input", function(e) {
  scale = parseInt(e.target.value);
  document.getElementById("zoom-val").textContent = scale;
  if (mapData.length > 0) draw();
});
document.getElementById("grid-toggle").addEventListener("change", function(e) {
  showGrid = e.target.checked;
  if (mapData.length > 0) draw();
});
document.getElementById("map").addEventListener("mousemove", function(e) {
  var rect = e.target.getBoundingClientRect();
  var x = Math.floor((e.clientX - rect.left) / scale);
  var y = Math.floor((e.clientY - rect.top) / scale);
  if (x>=0&&x<mapW&&y>=0&&y<mapH) {
    var c = mapData[y][x];
    document.getElementById("info").textContent = "("+x+", "+y+") = "+(tnames[c]||c);
  }
});
</script>
</body>
</html>'''


class Handler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/" or self.path == "/index.html":
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.end_headers()
            self.wfile.write(HTML.encode("utf-8"))
        elif self.path.startswith("/map"):
            try:
                with open(CUB_FILE, "r") as f:
                    content = f.read()
                data = json.dumps({"filename": CUB_FILE, "content": content})
                self.send_response(200)
                self.send_header("Content-Type", "application/json")
                self.send_header("Cache-Control", "no-cache")
                self.end_headers()
                self.wfile.write(data.encode("utf-8"))
            except Exception as e:
                self.send_response(500)
                self.end_headers()
                self.wfile.write(str(e).encode("utf-8"))
        else:
            self.send_response(404)
            self.end_headers()

    def log_message(self, format, *args):
        pass  # silence logs


print(f"\033[1;35m")
print(f"  ╔══════════════════════════════════════╗")
print(f"  ║     cub3D Live Map Viewer            ║")
print(f"  ╠══════════════════════════════════════╣")
print(f"  ║  Fichier: {CUB_FILE:<25s}  ║" if len(CUB_FILE) <= 25 else f"  ║  Fichier: {CUB_FILE[:25]:<25s}  ║")
print(f"  ║  URL:     http://localhost:{PORT:<10}║")
print(f"  ║  Ctrl+C pour arreter                 ║")
print(f"  ╚══════════════════════════════════════╝")
print(f"\033[0m")

server = http.server.HTTPServer(("", PORT), Handler)
try:
    server.serve_forever()
except KeyboardInterrupt:
    print("\nBye!")
    server.server_close()
