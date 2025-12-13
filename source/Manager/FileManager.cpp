#include "FileManager.h"
#include <QCoreApplication>
#include <QtConcurrentRun>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QImageReader>
#include <QUuid>
#include <QDebug>

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{

}

FileManager::~FileManager()
{

}

FileManager *FileManager::getInstance()
{
    static FileManager instance;
    return &instance;
}

void FileManager::importFiles(const QList<QUrl> &urls)
{
    qDebug() << __FUNCTION__ << urls.size();
    QtConcurrent::run([urls]{
        QString dir_t = QString("%1/Data/Files/%2").arg(qApp->applicationDirPath());

        for (int i = 0; i < urls.size(); ++i)
        {
            auto src_path = urls.at(i).toLocalFile();
            QFileInfo info(src_path);
            auto birth_time = info.birthTime().toString("yyyy-MM-dd");
            auto modify_time = info.lastModified().toString("yyyy-MM-dd");
            qDebug() << "\t[info]" << i << birth_time << modify_time;
            auto dir_path = dir_t.arg(modify_time);
            QDir dir(dir_path);
            if (!dir.exists()) {
                dir.mkpath(dir_path);
            }
            auto dst_path = QString("%1/%2.%3").arg(dir_path).arg(QUuid::createUuid().toString()).arg(info.suffix());
            qDebug() << "\t<-" << src_path;
            qDebug() << "\t->" << dst_path;
            if (!QFile::copy(src_path, dst_path)) {
                qDebug() << "copy failed:" << info.fileName();
            }
        }
    });
}
