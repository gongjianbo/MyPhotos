#include "FileInfoConnection.h"
#include <thread>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include "Core/MPConfig.h"

FileInfoConnection::FileInfoConnection()
{

}

FileInfoConnection::~FileInfoConnection()
{
    close();
}

bool FileInfoConnection::open()
{
    if (mDb.isOpen()) {
        return true;
    }
    QString db_path = MPConfig::instance()->common()->dbFilePath();
    if (db_path.isEmpty()) {
        return false;
    }
    const bool db_exists = QFile::exists(db_path);
    if (!db_exists) {
        // todo 文件夹操作待封装
        QString db_dir = QFileInfo(db_path).absolutePath();
        QDir dir(db_dir);
        // mkpath 递归创建父级目录
        if (!dir.exists() && !dir.mkpath(db_dir)) {
            return false;
        }
    }
    // 连接名加上线程id，每个线程通过不同的连接操作
    const QString con_name = QString("%1_%2").arg(
        MP_APP_NAME, std::hash<std::thread::id>{}(std::this_thread::get_id()));
    if (QSqlDatabase::contains(con_name)) {
        mDb = QSqlDatabase::database(con_name);
    } else {
        mDb = QSqlDatabase::addDatabase("QSQLITE", con_name);
    }
    mDb.setDatabaseName(db_path);
    mDb.open();
    if (!mDb.isOpen()) {
        // 打开数据库失败
    } else if (db_exists) {
        // 存在就尝试升级
        if (!updateTable()) {
            mDb.close();
        }
    } else {
        // 不存在就新建
        if (!createTable()) {
            mDb.close();
        }
    }
    return mDb.isOpen();
}

void FileInfoConnection::close()
{
    mDb.close();
}

bool FileInfoConnection::isOpen() const
{
    return mDb.isOpen();
}

QSqlQuery FileInfoConnection::query() const
{
    return QSqlQuery(mDb);
}

bool FileInfoConnection::transaction()
{
    return mDb.transaction();
}

bool FileInfoConnection::commit()
{
    return mDb.commit();
}

bool FileInfoConnection::rollback()
{
    return mDb.rollback();
}

bool FileInfoConnection::createTable()
{
    transaction();
    bool ret = false;
    do {
        auto &&db_query = query();
        QString sql;

        // 版本号表，只记录当前版本号
        sql = QString(R"(CREATE TABLE IF NOT EXISTS [version] (
version     INTEGER,
create_time TEXT,
update_time TEXT,
comment     TEXT
);)");
        if (!db_query.exec(sql)) {
            break;
        }
        QString date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        // 写入版本号
        sql = QString(R"(INSERT INTO [version](version, create_time, update_time, comment) VALUES(%1, "%2", "%3", "%4");)")
                  .arg(DbVersion::Last).arg(date_time).arg(date_time).arg("Create by application");
        if (!db_query.exec(sql)) {
            break;
        }

        // 文件信息表
        sql = QString(R"(CREATE TABLE IF NOT EXISTS [file_info] (
id          INTEGER PRIMARY KEY,
folder      TEXT,
file_name   TEXT,
suffix      TEXT,
size        INTEGER,
create_time INTEGER,
import_time INTEGER,
modify_time INTEGER,
type        INTEGER,
comment     TEXT,
source_id   INTEGER,
source_path TEXT,
status      INTEGER DEFAULT (0)
);)");
        if (!db_query.exec(sql)) {
            break;
        }

        // 图片信息表
        sql = QString(R"(CREATE TABLE IF NOT EXISTS [image_info] (
id      INTEGER PRIMARY KEY,
file_id INTEGER NOT NULL,
width   INTEGER,
height  INTEGER
);)");
        if (!db_query.exec(sql)) {
            break;
        }

        ret = commit();
    }
    while(false);
    if (!ret) {
        rollback();
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool FileInfoConnection::updateTable()
{
    auto &&db_query = query();
    QString sql;

    sql = QString(R"(SELECT version FROM [version];)");
    qint64 version = -1;
    if (db_query.exec(sql) && db_query.next() && db_query.value(0).isValid()) {
        version = db_query.value(0).toInt();
    }
    // 判断版本是否需要升级
    if (version < 0 || version > DbVersion::Last) {
        return false;
    }
    if (version == DbVersion::Last) {
        return true;
    }
    return true;
}
