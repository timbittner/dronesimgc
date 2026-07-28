#include "entity_model.h"

#include <QColor>
#include <QDateTime>
#include <QTimer>

namespace {
const char *kindName(Entity::Kind k)
{
    switch (k) {
    case Entity::Friendly: return "friendly";
    case Entity::Hostile: return "hostile";
    case Entity::Interceptor: return "SAM";
    }
    return "";
}
}  // namespace

QColor entityColor(Entity::Kind k)
{
    switch (k) {
    case Entity::Friendly: return QColor(80, 200, 255);
    case Entity::Hostile: return QColor(230, 60, 60);
    case Entity::Interceptor: return QColor(255, 170, 40);
    }
    return Qt::white;
}

EntityModel::EntityModel(QObject *parent) : QAbstractTableModel(parent)
{
    auto *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &EntityModel::sweep);
    t->start(500);
}

int EntityModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : rows_.size();
}

int EntityModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : ColumnCount;
}

void EntityModel::upsert(const Entity &e)
{
    const int row = index_.value(e.key(), -1);
    if (row >= 0) {
        rows_[row] = e;
        emit dataChanged(index(row, 0), index(row, ColumnCount - 1));
        return;
    }
    beginInsertRows({}, rows_.size(), rows_.size());
    index_.insert(e.key(), rows_.size());
    rows_.append(e);
    endInsertRows();
}

void EntityModel::sweep()
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    for (int row = rows_.size() - 1; row >= 0; --row) {
        if (!rows_[row].stale(now))
            continue;
        beginRemoveRows({}, row, row);
        rows_.remove(row);
        endRemoveRows();
    }
    index_.clear();
    for (int row = 0; row < rows_.size(); ++row)
        index_.insert(rows_[row].key(), row);
    if (!rows_.isEmpty())
        emit dataChanged(index(0, Age), index(rows_.size() - 1, Age));
}

QVariant EntityModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || idx.row() >= rows_.size())
        return {};
    const Entity &e = rows_[idx.row()];

    if (role == Qt::ForegroundRole)
        return entityColor(e.kind);
    if (role == Qt::TextAlignmentRole && idx.column() >= Alt)
        return int(Qt::AlignRight | Qt::AlignVCenter);
    if (role != Qt::DisplayRole)
        return {};

    switch (idx.column()) {
    case Id:
        return e.kind == Entity::Friendly ? QString::number(e.id)
                                          : QStringLiteral("%1").arg(e.id, 6, 16, QChar('0')).toUpper();
    case Type: return kindName(e.kind);
    case Name: return e.name;
    case Alt: return QString::number(e.alt_amsl, 'f', 0);
    case Speed: return QString::number(e.speed, 'f', 1);
    case Heading: return QString::number(e.heading, 'f', 0);
    case Signal: return e.signal < 0 ? QStringLiteral("—")
                                     : QString::number(e.signal * 100, 'f', 0) + "%";
    case Age: {
        const qint64 ms = QDateTime::currentMSecsSinceEpoch() - e.last_seen;
        return QString::number(ms / 1000.0, 'f', 1) + "s";
    }
    }
    return {};
}

QVariant EntityModel::headerData(int section, Qt::Orientation o, int role) const
{
    if (o != Qt::Horizontal || role != Qt::DisplayRole)
        return {};
    static const char *names[ColumnCount] = {"ID",  "Type",    "Name",   "Alt m",
                                             "m/s", "Hdg", "Signal", "Age"};
    return names[section];
}
