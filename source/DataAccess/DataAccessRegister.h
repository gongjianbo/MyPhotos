#pragma once
#include <QQmlEngine>
#include <QQmlContext>
#include "DataAccessDef.h"
#include "FileInfoAccess.h"

namespace MyPhotos
{

namespace DataAccess
{

inline void registerMeta()
{
    // 自定义类型
    qRegisterMetaType<FileInfo>("FileInfo");
    qRegisterMetaType<QVector<FileInfo>>("QVector<FileInfo>");
    qRegisterMetaType<QList<FileInfo>>("QList<FileInfo>");

    qRegisterMetaType<ImageInfo>("ImageInfo");
    qRegisterMetaType<QVector<ImageInfo>>("QVector<ImageInfo>");
    qRegisterMetaType<QList<ImageInfo>>("QList<ImageInfo>");
}

inline void registerType(QQmlEngine *engine)
{
    registerMeta();

}

}

}
