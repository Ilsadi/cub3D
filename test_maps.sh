#!/bin/bash

echo "=== TEST DES MAPS ==="
echo ""

for map in maps/*.cub; do
    name=$(basename "$map")
    output=$(timeout 0.3 ./cub3d "$map" 2>&1)
    
    if [ $? -eq 124 ]; then
        echo "✓ $name - LANCE (fenêtre ouverte)"
    elif [ -z "$output" ]; then
        echo "? $name - Aucun message"
    else
        echo "✗ $name - ERREUR: $(echo "$output" | head -1)"
    fi
done
