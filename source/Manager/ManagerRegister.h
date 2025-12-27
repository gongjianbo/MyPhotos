#pragma once
#include <QQmlEngine>
#include <QQmlContext>
#include "FileManager.h"

namespace MyPhotos
{

namespace Manager
{

inline void registerType(QQmlEngine *engine)
{
    engine->setObjectOwnership(FileManager::instance(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonType<FileManager>(
        "MyPhotos.Manager", 1, 0,
        "FileManager", [](QQmlEngine*, QJSEngine*){
            return FileManager::instance();
        });
}

}

}
