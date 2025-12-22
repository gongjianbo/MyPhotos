#pragma once
#include <QObject>
#include <QUrl>

/**
 * @brief 文件管理
 * @author 龚建波
 * @date 2025-12-15
 */
class FileManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileManager)
private:
    explicit FileManager(QObject *parent = nullptr);
public:
    ~FileManager();
    static FileManager* instance();

    Q_INVOKABLE void importFiles(const QList<QUrl> &urls);
};
