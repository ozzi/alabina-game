#ifndef CRASHLOGGER_H
#define CRASHLOGGER_H

#include <QString>

class CrashLogger
{
    QString _name;
public:
    CrashLogger (const QString& name);
    ~CrashLogger ();
};

#endif // CRASHLOGGER_H
