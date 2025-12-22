#include "MPConfig.h"
#include <QCoreApplication>
#include <QFileInfo>

MPConfig::MPConfig(QObject *parent)
    : QObject{parent}
    , mCommon{new CommonConfigGroup{this, this}}
{
    mAppDirPath = qApp->applicationDirPath();
}

MPConfig::~MPConfig()
{

}

MPConfig *MPConfig::instance()
{
    static MPConfig obj;
    return &obj;
}

QString MPConfig::appDirPath() const
{
    return mAppDirPath;
}

void MPConfig::setAppDirPath(const QString &path)
{
    // 设置 appPath 后根据预设的目录结构就能找到其他的路径
    mAppDirPath = QFileInfo(path).absoluteFilePath();
}

QString MPConfig::configDirPath() const
{
    return QString("%1/../Config").arg(appDirPath());
}

QString MPConfig::configFilePath(int module) const
{
    switch (module)
    {
    default: return QString("%1/settings.ini").arg(configDirPath());
    }
}

QSettings *MPConfig::configSettings(int module) const
{
    switch (module)
    {
    default: {
        thread_local QSettings settings{configFilePath(module), QSettings::IniFormat};
        return &settings;
    }
    }
}

QString CommonConfigGroup::dataDirPath() const
{
    if (dataPathExists()) {
        return dataPath();
    }
    return QString("%1/../Data").arg(config->appDirPath());
}

QString CommonConfigGroup::dbDirPath() const
{
    return QString("%1/Db").arg(dataDirPath());
}

QString CommonConfigGroup::dbFilePath() const
{
    return QString("%1/fileinfo.db").arg(dbDirPath());
}

QString CommonConfigGroup::storageDirPath(const QString &date) const
{
    return QString("%1/Files/%2").arg(dataDirPath(), date);
}

QString CommonConfigGroup::storageFilePath(const QString &date, const QString &filename) const
{
    return QString("%1/%2").arg(storageDirPath(date), filename);
}
