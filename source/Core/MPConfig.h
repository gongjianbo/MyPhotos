#pragma once
#include <QSettings>
#include "MPCoreDef.h"

class CommonConfigGroup;

/**
 * @brief 配置管理
 * @author 龚建波
 * @date 2025-12-22
 * @details
 * 程序目录结构
 * App/...................
 *     MyPhotos.exe.......
 *     动态库.dll..........
 * Config/................
 *     配置文件............
 * Data/..................
 *     Db/................
 *         数据库文件.......
 *     Files/.............
 *         YYYY-MM-DD.....
 *             图片视频等...
 * Temp/..................
 *     缓存文件............
 * Launcher.exe...........
 * @note
 * 程序main初始化时先调用setAppPath，使其他模块能正确地获取到配置信息
 */
class MPConfig : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MPConfig)
public:
    // 模块枚举
    enum ModuleType {
        Module_Common, // 程序通用配置
    };
    Q_ENUM(ModuleType)
private:
    explicit MPConfig(QObject *parent = nullptr);
public:
    ~MPConfig();
    static MPConfig *instance();

    // 主程序路径，初始化时设置
    // 主程序用applicationDirPath初始化，子程序通过启动参数传递
    QString appDirPath() const;
    void setAppDirPath(const QString &path);

    // 配置文件路径
    QString configDirPath() const;
    QString configFilePath(int module) const;

    // 配置读写
    QSettings *configSettings(int module) const;

    // 通用配置
    Q_INVOKABLE CommonConfigGroup *common() const { return mCommon; }

private:
    // 主程序所在目录
    QString mAppDirPath;

    // 通用配置
    CommonConfigGroup *mCommon;
};

/**
 * @brief 配置分组基类
 */
class MPConfigGroup : public QObject
{
    Q_OBJECT
public:
    explicit MPConfigGroup(MPConfig *config, QObject *parent = nullptr)
        : QObject{parent}, config{config}
    {
    }

protected:
    MPConfig *config{nullptr};
};

/**
 * @brief 通用配置
 */
class CommonConfigGroup : public MPConfigGroup
{
    Q_OBJECT
    // 数据存储路径
    CONFIG_PROPERTY(QString, dataPath, DataPath, "")
public:
    using MPConfigGroup::MPConfigGroup;
    // 在 ini 配置中的分组
    const QString group{"Common"};
    // 所属模块，模块对应具体的 ini 配置文件
    const int module{MPConfig::Module_Common};

    // 数据存放目录
    Q_INVOKABLE QString dataDirPath() const;
    // 数据库目录
    Q_INVOKABLE QString dbDirPath() const;
    // 数据库路径
    Q_INVOKABLE QString dbFilePath() const;
    // 文件目录
    Q_INVOKABLE QString storageDirPath(const QString &date) const;
    // 文件路径
    Q_INVOKABLE QString storageFilePath(const QString &date, const QString &filename) const;
};
