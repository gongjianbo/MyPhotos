#pragma once
#include <memory>
#include <QGuiApplication>
#include <QUrl>
#include "MPCoreDef.h"

class MPApplicationPrivate;

/**
 * @brief QApplication功能扩展
 * @author 龚建波
 * @date 2025-12-10
 * @details
 * 1.支持单实例运行
 * 2.支持程序重启
 */
class MPApplication : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ getAppName CONSTANT)
    Q_PROPERTY(QString moduleName READ getModuleName CONSTANT)
public:
    MPApplication(int &argc, char **argv);
    // 析构的时候执行重启动作
    ~MPApplication();

    // 构造qApp前的全局设置
    static void init(const QString &targetName);

    // 主程序名
    QString getAppName() const;

    // 子程序模块名
    QString getModuleName() const;

    // 退出qApp，并标记为重启
    Q_INVOKABLE static void restartApp();

    // 退出qApp
    Q_INVOKABLE static void quitApp(int returnCode = 0);

    // 启动新的进程
    void startNew();

    // 判断app是否有已存在的实例
    bool alreadyExists() const;

    // 给已启动的app实例发送消息
    void sendMessage(const QString &msg);

signals:
    // 接收到的消息
    void recvMessage(const QString &msg);

private:
    std::unique_ptr<MPApplicationPrivate> dptr;
};
