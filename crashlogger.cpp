#include "crashlogger.h"
#include <QDebug>

CrashLogger::CrashLogger (const QString& name) : _name(name)
{
    qDebug() << _name << " start";
}
CrashLogger::~CrashLogger ()
{
    qDebug() << _name << " end";
}
