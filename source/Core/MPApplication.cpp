#include "MPApplication.h"
#include <QQuickWindow>
#include <QNetworkProxy>
#include <QSharedMemory>
#include <QProcess>
#include <QLocalSocket>
#include <QLocalServer>
#include <QDir>
#include <QFont>

class MPApplicationPrivate
{
public:
    explicit MPApplicationPrivate(MPApplication *app)
        : application(app)
        , serverName(QString("MPApp(%1)").arg(QCoreApplication::applicationName()))
    {

    }

    // 默认不重启，prepareRestart之后=true需要重启
    inline static bool Need_Restart = false;

    // public class
    MPApplication *application{nullptr};

    // 共享内存和localsocket的server name
    const QString serverName;

    // 是否找到了已经启动的进程
    bool exists{false};

    // 通过共享内存实现只启动单个运行实例
    QSharedMemory *memory{nullptr};

    // 通过local sokcet与已启动的进程交互
    QLocalServer *server{nullptr};

    // 初始化local server
    void initServer()
    {
        // 启动local server监听后面多次启动程序时发送来的消息
        QLocalServer::removeServer(serverName);
        server = new QLocalServer();
        server->listen(serverName);
        QObject::connect(server, &QLocalServer::newConnection,
                         [this](){
                             onNewConnection();
                         });
    }

    // 多开后连进server
    void onNewConnection()
    {
        while (server->hasPendingConnections()) {
            QLocalSocket *client = server->nextPendingConnection();
            if (!client) continue;
            QObject::connect(client, &QLocalSocket::readyRead,
                             [this, client](){
                                 emit this->application->recvMessage(client->readAll());
                             });
            QObject::connect(client, &QLocalSocket::disconnected,
                             client, &QObject::deleteLater);
        }
    }

    // 发送消息
    void sendMessage(const QString &msg)
    {
        // 建立一个短链接，发送消息给已启动的程序
        QLocalSocket *client = new QLocalSocket;
        client->connectToServer(serverName);
        if (client->state() != QLocalSocket::ConnectedState) {
            client->waitForConnected(5000);
        }
        client->write(msg.toUtf8());
        client->waitForBytesWritten(5000);
        // 发送完毕，断开
        client->disconnectFromServer();
        if (client->state() != QLocalSocket::UnconnectedState) {
            client->waitForDisconnected(5000);
        }
        delete client;
    }
};

MPApplication::MPApplication(int &argc, char **argv)
    : QGuiApplication(argc, argv)
{
    // 全局字体
    QFont font;
#if defined(Q_OS_WIN32)
    font.setFamily("Microsoft YaHei");
#elif defined(Q_OS_MACOS)
    font.setFamily("PingFang SC");
#endif
    font.setPixelSize(12);
    setFont(font);

    dptr.reset(new MPApplicationPrivate(this));
#if defined(Q_OS_UNIX)
    // 解决unix上crashed后没释放的问题
    dptr->memory = new QSharedMemory(dptr->serverName);
    dptr->memory->attach();
    delete dptr->memory;
#endif
    dptr->memory = new QSharedMemory(dptr->serverName);

    // 共享内存实现单实例启动
    if (dptr->memory->create(1)) {
        // 初次启动
        dptr->initServer();
    } else {
        if (dptr->memory->error() == QSharedMemory::AlreadyExists &&
            dptr->memory->attach()) {
            // 程序已启动
            dptr->exists = true;
            dptr->memory->detach();
        }
    }
}

MPApplication::~MPApplication()
{
    if (dptr->server) {
        delete dptr->server;
    }
    if (dptr->memory) {
        delete dptr->memory;
    }
    if (MPApplicationPrivate::Need_Restart) {
        startNew();
    }
}

void MPApplication::init(const QString &targetName)
{
    qputenv("QML2_IMPORT_PATH", "");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setOrganizationName(MP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(MP_ORG_DOMAIN);
    QCoreApplication::setApplicationName(targetName);
    QCoreApplication::setApplicationVersion(MP_APP_VERSION);
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
}

QString MPApplication::getAppName() const
{
    return MP_APP_NAME;
}

QString MPApplication::getModuleName() const
{
    return applicationName();
}

void MPApplication::restartApp()
{
    MPApplicationPrivate::Need_Restart = true;
    // 退出qapp事件循环
    QCoreApplication::exit(0);
}

void MPApplication::quitApp(int returnCode)
{
    QCoreApplication::exit(returnCode);
}

void MPApplication::startNew()
{
    const QString program = QCoreApplication::applicationFilePath();
    const QStringList arguments = QCoreApplication::arguments();
    const QString directory = QDir::currentPath();
    QProcess::startDetached(program, arguments, directory);
}

bool MPApplication::alreadyExists() const
{
    return dptr->exists;
}

void MPApplication::sendMessage(const QString &msg)
{
    dptr->sendMessage(msg);
}
