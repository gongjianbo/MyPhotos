#pragma once
#include <memory>
#include <QObject>

/**
 * @brief 文件信息管理
 */
class FileInfoAccess : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileInfoAccess)
private:
    explicit FileInfoAccess(QObject *parent = nullptr);
public:
    ~FileInfoAccess();
    static FileInfoAccess *instance();

    // 测试数据库是否可访问，不存在时会尝试初始化
    bool ready();

    // 新增图片信息-单个文件
    // 查询图片信息
    // 查询图片信息-单个文件
    // 修改图片信息
    // 修改图片信息-单个文件
    // 删除图片信息
    // 删除图片信息-单个文件
};
