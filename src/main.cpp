#include <QApplication>
#include <QHeaderView>
#include <QMainWindow>
#include <QSplitter>
#include <QStatusBar>
#include <QTableView>

#include "detail_pane.h"
#include "entity_model.h"
#include "event_log.h"
#include "map_view.h"
#include "mavlink_listener.h"
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
    win.resize(1400, 860);
    win.statusBar()->showMessage(
        listener->listen()
            ? QStringLiteral("listening on UDP %1").arg(MavlinkListener::kDefaultPort)
            : QStringLiteral("cannot bind UDP %1 — is QGroundControl running?")
                  .arg(MavlinkListener::kDefaultPort));
    win.show();
    return app.exec();
}
