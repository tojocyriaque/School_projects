#include <QWidget>
#include <iostream>

typedef struct
{
    QString chain;
    QString protocol;
    QStringList destPorts;
    QStringList srcPorts;
    QString policy;
    QString mac;
    QString srcAddr;
    QString destAddr;
    QString srcIface;
    QString destIface;
} Rule;

bool isValid(Rule rule);

QString ruleToCommand(Rule rule);
