#include <QApplication>
#include <QFileDialog>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QStatusBar>
#include <QTableView>

#include "command_sender.h"
#include "detail_pane.h"
#include "entity_model.h"
#include "event_log.h"
#include "map_view.h"
#include "mavlink_listener.h"
#include "scenario.h"
#include "world_state.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("dronesimgc");

    const MapMeta meta = MapMeta::load(QStringLiteral(":/sebexen/map.json"));

    auto *model = new EntityModel(&app);
    auto *world = new WorldState(&app);
    auto *listener = new MavlinkListener(&app);
    QObject::connect(listener, &MavlinkListener::entityUpdated, model, &EntityModel::upsert);
    QObject::connect(listener, &MavlinkListener::objectiveUpdated, world, &WorldState::onObjective);
    QObject::connect(listener, &MavlinkListener::samSiteUpdated, world, &WorldState::onSamSite);
    QObject::connect(listener, &MavlinkListener::statusUpdated, world, &WorldState::onStatus);

    auto *table = new QTableView;
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    auto *detail = new DetailPane(model, world);
    auto *map = new MapView(model, world, meta);

    // Transitions worth logging are detected in WorldState, where the previous
    // value lives; the log only renders them.
    auto *log = new EventLog;
    QObject::connect(world, &WorldState::event, log, &EventLog::append);

    // Uplink (P9.3). Commands are logged as sent, never as done: the sim acks
    // nothing, so the proof of a command is the world changing on the downlink.
    auto *commands = new CommandSender(&app);
    QObject::connect(commands, &CommandSender::sent, log, &EventLog::append);
    // A scenario is just the spawns we issued, so it is built here, as they go.
    auto *scenario = new Scenario;
    QObject::connect(map, &MapView::spawnRequested, commands,
                     [commands, scenario](double lat, double lon, quint8 type) {
                         commands->spawnObjective(lat, lon, type);
                         scenario->add({lat, lon, CommandSender::kDefaultRadius, type});
                     });
    QObject::connect(map, &MapView::dispatchRequested, commands, &CommandSender::dispatch);

    QObject::connect(map, &MapView::selectionChanged, table, [table, model](quint64 key) {
        const int row = model->rowOf(key);
        if (row < 0)
            table->clearSelection();
        else
            table->selectRow(row);
    });
    QObject::connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, map,
                     [map, detail, model](const QModelIndex &cur) {
                         const quint64 key =
                             cur.isValid() ? model->entities()[cur.row()].key() : 0;
                         map->setSelected(key);
                         detail->setSelected(key);
                     });

    auto *side = new QSplitter(Qt::Vertical);
    side->addWidget(detail);
    side->addWidget(table);
    side->addWidget(log);

    auto *split = new QSplitter;
    split->addWidget(map);
    split->addWidget(side);
    split->setStretchFactor(0, 3);

    QMainWindow win;
    win.setCentralWidget(split);

    // Scenario menu (P9.4). Load is CLEAR followed by the saved spawns — the
    // sim has no other idea of "a scenario", and does not need one.
    QMenu *menu = win.menuBar()->addMenu(QStringLiteral("&Scenario"));
    menu->addAction(QStringLiteral("&Save…"), &win, [&win, scenario, log] {
        const QString path = QFileDialog::getSaveFileName(
            &win, QStringLiteral("Save scenario"), {}, QStringLiteral("JSON (*.json)"));
        if (path.isEmpty())
            return;
        QString err;
        if (scenario->save(path, &err))
            log->append(QStringLiteral("scenario saved (%1 spawns)").arg(scenario->spawns().size()));
        else
            QMessageBox::warning(&win, QStringLiteral("Save failed"), err);
    });
    menu->addAction(QStringLiteral("&Load…"), &win, [&win, scenario, commands, log] {
        const QString path = QFileDialog::getOpenFileName(
            &win, QStringLiteral("Load scenario"), {}, QStringLiteral("JSON (*.json)"));
        if (path.isEmpty())
            return;
        QString err;
        if (!scenario->load(path, &err)) {
            QMessageBox::warning(&win, QStringLiteral("Load failed"), err);
            return;
        }
        commands->clearWorld();
        for (const SpawnRecord &r : scenario->spawns())
            commands->spawnObjective(r.lat, r.lon, r.type, r.radius);
        log->append(QStringLiteral("scenario loaded (%1 spawns)").arg(scenario->spawns().size()));
    });
    menu->addAction(QStringLiteral("&Clear"), &win, [scenario, commands] {
        scenario->clear();
        commands->clearWorld();
    });
    win.resize(1400, 860);
    win.statusBar()->showMessage(
        listener->listen()
            ? QStringLiteral("listening on UDP %1, commands to %2")
                  .arg(MavlinkListener::kDefaultPort)
                  .arg(CommandSender::kDefaultPort)
            : QStringLiteral("cannot bind UDP %1 — is QGroundControl running?")
                  .arg(MavlinkListener::kDefaultPort));
    win.show();
    return app.exec();
}
