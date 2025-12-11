#pragma once
#include <QObject>

class MPCore : public QObject
{
    Q_OBJECT
public:
    static void hello();
};
