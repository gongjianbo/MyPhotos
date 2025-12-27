#include "DataAccessDef.h"
#include <QDateTime>

QString FileInfo::toString() const
{
    if (!isValid()) {
        return QString("[FileInfo] null");
    }
    // todo 时间转换放到工具类，统一格式
    return QString("[FileInfo] id:%1 folder:%2 fielName:%3 suffix:%4 importTime:%5 modifyTime:%6")
        .arg(id).arg(folder).arg(fileName).arg(suffix)
        .arg(QDateTime::fromMSecsSinceEpoch(importTime).toString("yyyy-MM-dd hh:mm:ss.zzz"))
        .arg(QDateTime::fromMSecsSinceEpoch(modifyTime).toString("yyyy-MM-dd hh:mm:ss.zzz"));
}

bool FileInfo::compare(const FileInfo &other) const
{
    if (id != other.id ||
        folder != other.folder || fileName != other.fileName ||
        suffix != other.suffix || size != other.size ||
        createTime != other.createTime || importTime != other.importTime || modifyTime != other.modifyTime ||
        type != other.type || comment != other.comment ||
        sourceId != other.sourceId || sourcePath != other.sourcePath)
        return false;
    return true;
}

bool FileInfo::operator!=(const FileInfo &other) const
{
    return !compare(other);
}

bool FileInfo::operator==(const FileInfo &other) const
{
    return compare(other);
}

QString ImageInfo::toString() const
{
    if (!isValid()) {
        return QString("[ImageInfo] null");
    }
    return QString("[ImageInfo] id:%1 width:%2 height:%3 fileId:%4 folder:%5 fielName:%6 suffix:%7 importTime:%8 modifyTime:%9")
        .arg(id).arg(width).arg(height)
        .arg(fileInfo.id).arg(fileInfo.folder).arg(fileInfo.fileName).arg(fileInfo.suffix)
        .arg(QDateTime::fromMSecsSinceEpoch(fileInfo.importTime).toString("yyyy-MM-dd hh:mm:ss.zzz"))
        .arg(QDateTime::fromMSecsSinceEpoch(fileInfo.modifyTime).toString("yyyy-MM-dd hh:mm:ss.zzz"));
}

bool ImageInfo::compare(const ImageInfo &other) const
{
    if (id != other.id ||
        width != other.width || height != other.height ||
        fileInfo != other.fileInfo)
        return false;
    return true;
}

bool ImageInfo::operator!=(const ImageInfo &other) const
{
    return !compare(other);
}

bool ImageInfo::operator==(const ImageInfo &other) const
{
    return compare(other);
}
