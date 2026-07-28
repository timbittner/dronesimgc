#pragma once

#include <QAbstractTableModel>
#include <QHash>
#include <QVector>

#include "mavlink_listener.h"

class QColor;

// Shared by the table and the map so a contact reads the same in both.
QColor entityColor(Entity::Kind k);

// Live roster of contacts. Rows drop out when the sim stops emitting them.
class EntityModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Column { Id, Type, Name, Alt, Speed, Heading, Signal, Age, ColumnCount };

    explicit EntityModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation o, int role) const override;

    const QVector<Entity> &entities() const { return rows_; }
    int rowOf(quint64 key) const { return index_.value(key, -1); }

public slots:
    void upsert(const Entity &e);

private:
    void sweep();  // age out contacts and refresh the Age column

    QVector<Entity> rows_;
    QHash<quint64, int> index_;
};
