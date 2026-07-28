#!/usr/bin/env bash
# Regenerates third_party/mavlink/ from the sim's dialect XML. The producer
# owns the protocol, so this repo never edits dronesim.xml — it only vendors
# mavgen's output. Run after any protocol change on the sim side, then run
# tools/sync_map.sh to pick up the matching golden vectors.
#
# Needs pymavlink: python3 -m venv .venv && .venv/bin/pip install pymavlink
set -euo pipefail

src="${DRONESIM_DIR:-$HOME/dev/dronesim}"
dst="$(cd "$(dirname "$0")/.." && pwd)"
py="${PYTHON:-$src/.venv/bin/python}"

defs="$("$py" -c 'import pymavlink,pathlib;print(pathlib.Path(pymavlink.__file__).parent)')/message_definitions/v1.0"
# common.xml includes standard.xml/minimal.xml by bare filename, so the dialect
# has to be generated from inside pymavlink's definitions directory.
cp "$src/mavlink/dronesim.xml" "$defs/"

rm -rf "$dst/third_party/mavlink"
"$py" "$(dirname "$py")/mavgen.py" --lang=C --wire-protocol=2.0 \
    --output="$dst/third_party/mavlink" "$defs/dronesim.xml"
echo "vendored headers regenerated from $src/mavlink/dronesim.xml"
