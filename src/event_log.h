#pragma once

#include <QListWidget>

// Timestamped scrolling log of world transitions. WorldState decides what is
// worth a line; this only renders and bounds it.
class EventLog : public QListWidget {
    Q_OBJECT
public:
    explicit EventLog(QWidget *parent = nullptr);

public slots:
    void append(const QString &line);

private:
    static constexpr int kMaxLines = 500;
};
