#include "event_log.h"

#include <QTime>

EventLog::EventLog(QWidget *parent) : QListWidget(parent)
{
    setMaximumHeight(140);
    setUniformItemSizes(true);
}

void EventLog::append(const QString &line)
{
    addItem(QTime::currentTime().toString("HH:mm:ss ") + line);
    while (count() > kMaxLines)
        delete takeItem(0);
    scrollToBottom();
}
