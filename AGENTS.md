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
- The custom dialect (`dronesim.xml`, msgids 55000+) lives in the dronesim
  repo — the producer owns the protocol, this repo never edits the XML.
  `tools/sync_dialect.sh` regenerates `third_party/mavlink/` from it; run
  `tools/sync_map.sh` after, for the matching golden vectors.
- Golden wire vectors: `dronesim/scripts/test/mavlink_vectors.json`
  (`frames` = hex-pinned packets, `geo` = local↔lat/lon pairs from
  pyproj), copied to `tests/` by `tools/sync_map.sh` so CI needs no
  dronesim checkout. Decode and transform tests pin against them.

## Dialect Contract (P9.2 downlink — sim-only state)

Three messages at 1 Hz from sysid 1, all fields listed in the XML in wire
order. `DRONESIM_STATUS` (55000) carries mission state, backup pool and
live counts; `DRONESIM_OBJECTIVE` (55001) and `DRONESIM_SAM_SITE` (55002)
are sent once per object per tick. What the field list does not say:

- `reload_progress >= 1.0` **is** "ready to fire" — there is deliberately
  no ready flag. It is 0 immediately after a launch.
- `progress` is OBSERVE dwell only, always 0 for CRASH/DELIVER. Do not
  render it as a generic progress bar.
- `id` is a small per-run integer from 1, stable for the object's life and
  never reused — safe to key on, but **not** stable across runs.
- Objectives and SAM sites age out like ADS-B: one that stops being sent
  is gone. From 9.3 an objective can also appear mid-run, from our own
  uplink — the new id in the next burst is the only confirmation there is.
- Absent sim nodes are normal, not errors: no MissionTracker reports
  RUNNING, no SwarmManager reports `backup_pool = 0`. "No swarm manager"
  and "pool empty" are indistinguishable — do not build a heuristic on it.
- `friendly_count`/`hostile_count` are redundant with the heartbeat and
  ADS-B tracking. Sanity check or ignore.
- Stock QGC ignores unknown msgids, so the P8 conformance check stands.

## Uplink Contract (P9.3/9.4 — what the GCS sends)

Three dialect messages to the sim's **UDP 14556** (`command_port`), not 14550 —
the GCS holds that one to receive. The GCS transmits as sysid 255 / compid 190
and the sim accepts any sysid.

- `DRONESIM_SPAWN_OBJECTIVE` (55003): lat, lon, radius, type. Height and dwell
  come from the sim's scene defaults; the sim clamps radius to 5–500 m and
  drops anything more than 5 km from the sim origin.
- `DRONESIM_DISPATCH` (55004): lat, lon, icao, sysid. `icao != 0` strikes that
  ADS-B contact and ignores lat/lon; `sysid = 0` means nearest formation
  follower. A contact the sim has already lost drops the command.
- `DRONESIM_CLEAR` (55005): `confirm` must be 1 — zero is what a truncated
  packet decodes to, and this is the command that throws work away. It
  despawns only objectives the uplink spawned and resets the mission tracker.
  Editor-placed objectives survive: they are part of the map, not the scenario.
- **Nothing is acknowledged, by design.** A spawn confirms itself in the next
  `DRONESIM_OBJECTIVE` burst, a dispatch by the drone moving. Log commands as
  *sent*, never as *done*.
- The uplink is LAN-trusted with no auth (`ponytail:` localhost sim). The sim
  validates; the GCS does not pretend to.

## Scenarios (P9.4)

A scenario is **the list of spawn commands that produced the world**, not a
snapshot of it — which is why save/load needs no state transfer protocol.
`Scenario` collects each spawn as it is issued and writes JSON; a load sends
`DRONESIM_CLEAR` and replays the spawns. The sim has no concept of a scenario
and does not need one. A load that fails to parse leaves the current scenario
untouched rather than half-replaced.

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
