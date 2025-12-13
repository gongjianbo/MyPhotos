#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MPCore.h"
#include "CoreRegister.h"
#include "ManagerRegister.h"

int main(int argc, char *argv[])
{
    MPApplication::init(MP_APP_NAME);
    MPApplication app(argc, argv);
    // 单实例启动
    if (app.alreadyExists()) {
        app.sendMessage("Popup");
        return 0;
    }

    MPCore::hello();

    QQmlApplicationEngine engine;
    MyPhotos::Core::registerType(&engine);
    MyPhotos::Manager::registerType(&engine);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("MyPhotosQml", "Main");

    int ret = app.exec();
    return ret;
}
