#!/usr/bin/env bash
# Copies the three files dronesimgc borrows from the sim: the baked map pair
# and the golden MAVLink wire vectors. They are checked in here so CI needs no
# dronesim checkout; run this after the sim rebakes the map or regenerates the
# vectors. Nothing under assets/ is ever edited in this repo.
set -euo pipefail

src="${DRONESIM_DIR:-$HOME/dev/dronesim}"
dst="$(cd "$(dirname "$0")/.." && pwd)"
map="$src/assets/maps/sebexen/map.json"

[ -f "$map" ] || { echo "no map at $map (set DRONESIM_DIR)" >&2; exit 1; }
# The map assets carry LGLN/OSM licenses; a copy without the credits is a
# license violation, not a missing nicety.
grep -q '"attribution"' "$map" || { echo "map.json has no attribution block" >&2; exit 1; }

cp "$src/assets/maps/sebexen/albedo.png" "$dst/assets/sebexen/"
cp "$map" "$dst/assets/sebexen/"
cp "$src/scripts/test/mavlink_vectors.json" "$dst/tests/"
echo "synced map + golden vectors from $src"
