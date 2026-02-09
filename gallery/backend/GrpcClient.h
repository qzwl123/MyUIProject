#ifndef GRPCCLIENT_H
#define GRPCCLIENT_H

#include <QObject>
#include <QQmlEngine>

class GrpcClient : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    GrpcClient();
};

#endif // GRPCCLIENT_H
