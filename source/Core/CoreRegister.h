#pragma once
#include <QQmlEngine>
#include <QQmlContext>
#include <QImage>
#include <QUrl>
#include "MPApplication.h"
#include "MPCore.h"
#include "MPConfig.h"

namespace MyPhotos
{

namespace Core
{

inline void registerMeta()
{
    // 基本类型
    qRegisterMetaType<QImage>("QImage");
    qRegisterMetaType<qint32>("qint32");
    qRegisterMetaType<quint32>("quint32");
    qRegisterMetaType<qint64>("qint64");
    qRegisterMetaType<quint64>("quint64");
    qRegisterMetaType<QUrl>("QUrl");

    qRegisterMetaType<QVector<QImage>>("QVector<QImage>");
    qRegisterMetaType<QVector<qint32>>("QVector<qint32>");
    qRegisterMetaType<QVector<quint32>>("QVector<quint32>");
    qRegisterMetaType<QVector<qint64>>("QVector<qint64>");
    qRegisterMetaType<QVector<quint64>>("QVector<quint64>");
    qRegisterMetaType<QVector<QUrl>>("QVector<QUrl>");

    qRegisterMetaType<QList<QImage>>("QList<QImage>");
    qRegisterMetaType<QList<qint32>>("QList<qint32>");
    qRegisterMetaType<QList<quint32>>("QList<quint32>");
    qRegisterMetaType<QList<qint64>>("QList<qint64>");
    qRegisterMetaType<QList<quint64>>("QList<quint64>");
    qRegisterMetaType<QList<QUrl>>("QList<QUrl>");

    qRegisterMetaType<QStringList>("QStringList");
    qRegisterMetaType<QVariantMap>("QVariantMap");

    // 自定义类型
}

inline void registerType(QQmlEngine *engine)
{
    registerMeta();

    qmlRegisterUncreatableType<MPApplication>("MyPhotos.Core", 1, 0, "MPApplication",
                                              "can not instantiate MPApplication in qml");
    engine->rootContext()->setContextProperty("mpApp", qobject_cast<MPApplication*>(qApp));
}

}

}
