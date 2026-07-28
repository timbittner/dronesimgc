# dronesimgc

A Qt6 ground control station for the [dronesim](https://github.com/) drone
swarm simulator. It listens to the sim's MAVLink v2 downlink and renders the
battlespace over the baked Sebexen map: friendlies as vehicles, hostiles and
SAM interceptors as ADS-B traffic.

Phase 9.3: the full loop — entity table, map view, mission/pool panel and event
log over the P8 stream plus the sim's custom dialect (objectives, SAM sites,
mission state), and commands back the other way: right-click the map to spawn
an objective, dispatch a drone, or send one at a hostile.

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
status bar says so if the bind fails). Commands go out to 127.0.0.1:14556,
which is where the sim listens; nothing acknowledges them, so a command is
confirmed by the world changing on the downlink.

## Syncing from the sim

Two scripts, both taking `DRONESIM_DIR` (default `~/dev/dronesim`):

```bash
tools/sync_dialect.sh   # third_party/mavlink/ from the sim's dronesim.xml
tools/sync_map.sh       # albedo.png + map.json + tests/mavlink_vectors.json
```

Run the dialect one first after a protocol change, then the map one so the
vendored headers and the golden vectors come from the same sim build — the
decode test fails loudly if they don't. Nothing under `assets/`,
`third_party/` or `tests/mavlink_vectors.json` is hand-edited here.
`sync_dialect.sh` needs pymavlink (it uses the sim's `.venv` by default).

## Attribution

The Sebexen map assets carry third-party licenses, reproduced here as required
and shown in the map view:

- Elevation: DGM1 © LGLN Niedersachsen 2016, [dl-de/by-2-0](https://www.govdata.de/dl-de/by-2-0)
- Map data © OpenStreetMap contributors, [ODbL](https://www.openstreetmap.org/copyright)
