#include <QApplication>
#include <QHeaderView>
#include <QMainWindow>
#include <QSplitter>
#include <QStatusBar>
#include <QTableView>

#include "entity_model.h"
#include "map_view.h"
#include "mavlink_listener.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("dronesimgc");

    const MapMeta meta = MapMeta::load(QStringLiteral(":/sebexen/map.json"));

    auto *model = new EntityModel(&app);
    auto *listener = new MavlinkListener(&app);
    QObject::connect(listener, &MavlinkListener::entityUpdated, model, &EntityModel::upsert);

    auto *table = new QTableView;
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    auto *map = new MapView(model, meta);

    QObject::connect(map, &MapView::selectionChanged, table, [table, model](quint64 key) {
        const int row = model->rowOf(key);
        if (row < 0)
            table->clearSelection();
        else
            table->selectRow(row);
    });
    QObject::connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, map,
                     [map, model](const QModelIndex &cur) {
                         map->setSelected(cur.isValid() ? model->entities()[cur.row()].key() : 0);
                     });

    auto *split = new QSplitter;
    split->addWidget(map);
    split->addWidget(table);
    split->setStretchFactor(0, 3);

    QMainWindow win;
    win.setCentralWidget(split);
    win.resize(1280, 800);
    win.statusBar()->showMessage(
        listener->listen()
            ? QStringLiteral("listening on UDP %1").arg(MavlinkListener::kDefaultPort)
            : QStringLiteral("cannot bind UDP %1 — is QGroundControl running?")
                  .arg(MavlinkListener::kDefaultPort));
    win.show();
    return app.exec();
}
