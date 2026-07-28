# dronesimgc

A Qt6 ground control station for the [dronesim](https://github.com/) drone
swarm simulator. It listens to the sim's MAVLink v2 downlink and renders the
battlespace over the baked Sebexen map: friendlies as vehicles, hostiles and
SAM interceptors as ADS-B traffic.

Phase 9.1: read-only — entity table + map view against the stock P8 stream.

## Build

```bash
brew install qt cmake ninja            # macOS; CI uses apt qt6-base-dev
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
./build/dronesimgc
```

Qt 6.4 is the minimum (what CI builds against).

## Run

Start the sim, then the GCS — it binds UDP 14550 and shows whatever it hears.
**Close QGroundControl first:** both want that port, and only one gets it (the
status bar says so if the bind fails).

## Syncing from the sim

`tools/sync_map.sh` copies the map pair and the golden wire vectors out of a
dronesim checkout (`DRONESIM_DIR`, default `~/dev/dronesim`). Nothing under
`assets/` is edited here. The MAVLink headers under `third_party/mavlink/` are
mavgen output; regenerate them when the dialect changes:

```bash
mavgen.py --lang=C --wire-protocol=2.0 -o third_party/mavlink <dialect>.xml
```

## Attribution

The Sebexen map assets carry third-party licenses, reproduced here as required
and shown in the map view:

- Elevation: DGM1 © LGLN Niedersachsen 2016, [dl-de/by-2-0](https://www.govdata.de/dl-de/by-2-0)
- Map data © OpenStreetMap contributors, [ODbL](https://www.openstreetmap.org/copyright)
