#pragma once
#include <QQmlEngine>
#include <QQmlContext>
#include "MPCore.h"
#include "MPApplication.h"

namespace MyPhotos
{

namespace Core
{

void registerType(QQmlEngine *engine)
{
    qmlRegisterUncreatableType<MPApplication>("MyPhotos.Core", 1, 0, "MPApplication",
                                              "can not instantiate MPApplication in qml");
    engine->rootContext()->setContextProperty("mpApp", qobject_cast<MPApplication*>(qApp));
}

}

}
