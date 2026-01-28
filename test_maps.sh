#!/bin/bash

echo "=== TEST DES MAPS ==="
echo ""

for map in maps/*.cub; do
    name=$(basename "$map")

    # Lance le programme en arrière-plan
    ./cub3D "$map" > /tmp/cub_output.txt 2>&1 &
    pid=$!

    # Attend un court instant
    sleep 0.3

    # Vérifie si le processus tourne encore (fenêtre ouverte)
    if kill -0 $pid 2>/dev/null; then
        kill $pid 2>/dev/null
        wait $pid 2>/dev/null
        echo "✓ $name - LANCE (fenêtre ouverte)"
    else
        # Le processus s'est terminé, vérifie le message d'erreur
        error=$(cat /tmp/cub_output.txt | head -2 | tail -1)
        if [ -z "$error" ]; then
            error="(pas de message)"
        fi
        echo "✗ $name - ERREUR: $error"
    fi
done

rm -f /tmp/cub_output.txt
