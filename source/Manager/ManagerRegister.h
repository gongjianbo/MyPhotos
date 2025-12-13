#pragma once
#include <QQmlEngine>
#include <QQmlContext>
#include "FileManager.h"

namespace MyPhotos
{

namespace Manager
{

void registerType(QQmlEngine *engine)
{
    engine->setObjectOwnership(FileManager::getInstance(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonType<FileManager>(
        "MyPhotos.Manager", 1, 0,
        "FileManager", [](QQmlEngine*, QJSEngine*){
            return FileManager::getInstance();
        });
}

}

}
