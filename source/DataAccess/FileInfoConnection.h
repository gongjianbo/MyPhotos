#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief 文件信息数据库连接
 * @author 龚建波
 * @date 2025-12-27
 */
class FileInfoConnection
{
private:
    // 数据库版本
    enum DbVersion {
        DbV1 = 0x01, // 初版，包含基本的文件信息
        Last = DbV1
    };
public:
    FileInfoConnection();
    ~FileInfoConnection();

    // 打开数据库
    bool open();
    // 关闭数据库
    void close();
    // 数据库是否已打开
    bool isOpen() const;

    // 创建一个 query 对象
    QSqlQuery query() const;
    // 开启事务
    bool transaction();
    // 关闭事务
    bool commit();
    // 回滚事务
    bool rollback();

private:
    // 创建表
    bool createTable();
    // 更新表
    bool updateTable();

private:
    QSqlDatabase mDb;
};
