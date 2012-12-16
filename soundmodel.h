#ifndef SOUNDMODEL_H
#define SOUNDMODEL_H

#include <QObject>

class SoundModel : public QObject
{
    Q_OBJECT
    QString _successPath;
    QString _failPath;
public:
    explicit SoundModel(QObject *parent = 0);
    void setSuccessPath(const QString& path);
    void setFailPath(const QString& path);
signals:
    
public slots:
    void onTestHit();
    void onTestMiss();
};

#endif // SOUNDMODEL_H
