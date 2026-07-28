# dronesimgc — Project Guide

**Doc rule (this file and all docs here):** as long as necessary to
understand, as short as possible. Do not restate what code, CMakeLists,
or CI already show. State each fact once, in one place.

## What This Is

A Qt ground control station (GCS) for the dronesim simulator
(`~/dev/dronesim`, Godot — the telemetry producer). It renders the whole
battlespace — swarm telemetry, hostiles, SAM sites, mission state — and,
from phase 9.3, sends commands back. Plan of record:
`dronesim/plans/P9-dronesimgc.md` (phases 9.1–9.4). Deep protocol detail
stays in `dronesim/docs/systems/net.md`; this file carries only what a
dronesimgc session needs without opening the sim repo.

## Tech Stack

- Qt **6.4+ Widgets — no QML**, C++20, CMake + ninja
- macOS dev: `brew install qt cmake ninja`; CI: ubuntu-24.04 + apt Qt6
  (Qt 6.4 is the minimum supported version — it is what CI builds)
- Tests: QTest binaries, run with `ctest`
- Only dependency beyond Qt: vendored mavgen-generated MAVLink C headers
  (header-only) in `third_party/mavlink/`

## Protocol Contract (P8 downlink — what the GCS consumes)

- MAVLink **v2 over UDP, port 14550** (QGC's autoconnect port). The sim
  sends every packet twice: to 127.0.0.1 and to the subnet broadcast
  address. Gotcha: QGC and this GCS cannot both bind 14550 — close QGC.
- Friendlies are MAVLink *systems*: `HEARTBEAT` (0) + `SYS_STATUS` (1) at
  1 Hz, `ATTITUDE` (30) + `GLOBAL_POSITION_INT` (33) at 5 Hz.
  `SYS_STATUS.drop_rate_comm` carries signal quality; battery and sensor
  fields are −1 (the sim does not model them).
- Hostiles and interceptors are ADS-B *traffic*: `ADSB_VEHICLE` (246),
  ICAO `0xD00000 + n`, callsign `HSTL<n>` / `SAM<n>`.
- A dead entity simply stops being emitted. Age entities out
  receiver-side: heartbeat timeout for systems, last-seen for ADS-B.
- sysid 1 is always the player. Other drones take ids from 2 up, never
  reused; a replacement airframe gets a **new** sysid.
- The custom dialect (`dronesim.xml`, msgids 55000+, from phase 9.2)
  lives in the dronesim repo — the producer owns the protocol. When it
  changes, regenerate the vendored headers with mavgen
  (`.venv/bin/pip install pymavlink`, then mavgen against the XML).
- Golden wire vectors: `dronesim/scripts/test/mavlink_vectors.json`
  (`frames` = hex-pinned packets, `geo` = local↔lat/lon pairs from
  pyproj), copied to `tests/` by `tools/sync_map.sh` so CI needs no
  dronesim checkout. Decode and transform tests pin against them.

## Map / Georeference

`assets/sebexen/albedo.png` + `map.json` are copied from dronesim by
`tools/sync_map.sh` (never edited here) and compiled in as Qt resources
under `:/sebexen/`. `map.json` keys: `cell_size`
(metres/pixel), `grid_width`/`grid_height` (pixels), `origin_x`/`origin_z`
(sim-local metres of pixel (0,0)), `height_datum` (AMSL metres of local
y = 0), `utm` (`epsg` 25832, `e_min`, `n_max`, `spawn_e`/`spawn_n`).

- Local metres → pixel: `px = (x − origin_x) / cell_size`,
  `py = (z − origin_z) / cell_size`.
- Frames: sim-local **+X = east, +Z = south**; heading 0 = true north,
  clockwise. lat/lon ↔ local goes through UTM zone 32N; pin the
  conversion with a QTest against the golden `geo` vectors.
- **License-required attribution (do not drop):** elevation © LGLN
  Niedersachsen (DGM1, dl-de/by-2-0); map features © OpenStreetMap
  contributors (ODbL). Keep the `map.json` attribution block intact,
  repeat both credits in the README, and show a small attribution line
  in the map view.

## Conventions

Mirror dronesim: snake_case file names, PascalCase classes, Conventional
Commits, work on feature branches. **Always ask before pushing `main` or
opening a PR into it.** Keep build + ctest CI green from the first commit
that carries code.
