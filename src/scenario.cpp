#include "scenario.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

bool Scenario::save(const QString &path, QString *error) const
{
    QJsonArray arr;
    for (const SpawnRecord &r : spawns_)
        arr.append(QJsonObject{{"lat", r.lat},
                               {"lon", r.lon},
                               {"radius", r.radius},
                               {"type", int(r.type)}});

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (error)
            *error = f.errorString();
        return false;
    }
    f.write(QJsonDocument(QJsonObject{{"version", 1}, {"spawns", arr}}).toJson());
    return true;
}

bool Scenario::load(const QString &path, QString *error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        if (error)
            *error = f.errorString();
        return false;
    }
    QJsonParseError parse{};
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &parse);
    if (parse.error != QJsonParseError::NoError || !doc.isObject()) {
        if (error)
            *error = parse.errorString();
        return false;
    }

    // Parse into a scratch list first: a file that goes bad halfway through
    // must not leave half a scenario loaded.
    QVector<SpawnRecord> parsed;
    for (const QJsonValue &v : doc.object()["spawns"].toArray()) {
        const QJsonObject o = v.toObject();
        if (!o.contains("lat") || !o.contains("lon")) {
            if (error)
                *error = QStringLiteral("a spawn entry has no position");
            return false;
        }
        parsed.append({o["lat"].toDouble(), o["lon"].toDouble(),
                       float(o["radius"].toDouble()), quint8(o["type"].toInt())});
    }
    spawns_ = parsed;
    return true;
}
