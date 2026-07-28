#pragma once

#include <QWidget>

#include "entity_model.h"
#include "world_state.h"

class QLabel;

// Mission banner + backup pool on top, telemetry for the selected contact
// below. Rich-text labels: this is a readout, not a form.
class DetailPane : public QWidget {
    Q_OBJECT
public:
    DetailPane(EntityModel *model, WorldState *world, QWidget *parent = nullptr);

public slots:
    void setSelected(quint64 key);

private:
    void refresh();

    EntityModel *model_;
    WorldState *world_;
    QLabel *banner_;
    QLabel *mission_;
    QLabel *entity_;
    quint64 selected_ = 0;
};
