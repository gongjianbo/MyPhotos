#include "FileInfoAccess.h"
#include <QSqlDatabase>
#include "FileInfoConnection.h"

FileInfoAccess::FileInfoAccess(QObject *parent)
    : QObject{parent}
{

}

FileInfoAccess::~FileInfoAccess()
{

}

FileInfoAccess *FileInfoAccess::instance()
{
    static FileInfoAccess obj;
    return &obj;
}

bool FileInfoAccess::ready()
{
    FileInfoConnection con;
    return con.open();
}
