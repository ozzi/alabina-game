#include "soundmodel.h"
#include <QSound>
#include <QDebug>

SoundModel::SoundModel(QObject *parent) :
    QObject(parent)
{
}

void SoundModel::setSuccessPath(const QString &path)
{
    _successPath = path;
}

void SoundModel::setFailPath(const QString &path)
{
    _failPath = path;
}

void SoundModel::onTestHit()
{
    if (_successPath.length()) {
        QSound::play(_successPath);
    } else {
        qDebug() << "SoundModel::onTestHit no path to success sound";
    }
}

void SoundModel::onTestMiss()
{
    if (_failPath.length()) {
        QSound::play(_failPath);
    } else {
        qDebug() << "SoundModel::onTestHit no path to fail sound";
    }
}
