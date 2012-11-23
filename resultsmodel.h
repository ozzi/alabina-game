#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "levelmodel.h"
#include "scenemanager.h"

class ResultsModel : public QAbstractListModel
{
    Q_OBJECT
    unsigned _pointsTotal;
    unsigned _maximumFailCount;
    unsigned _failCount;
    QString _levelName;
    QVector<unsigned> _results;
    void reset();
public:
    explicit ResultsModel(QObject *parent = 0);
    enum ResultRoles
    {
      ResultPointsRole = Qt::UserRole
    };
    Q_PROPERTY(unsigned pointsTotal READ pointsTotal NOTIFY pointsTotalChanged)
    unsigned pointsTotal () const;
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex &aIndex, int aRole) const;
signals:
    void pointsTotalChanged(unsigned aPointsTotal);
    void levelPoints(const QString & aLevelName, unsigned aPoints);
public slots:
    void onTestHit();
    void onTestMiss();
    void onNewTest();
    void onNewLevel(const std::shared_ptr<LevelDescription> & aLevelDescription);
    void onStateChanged(SceneState aNewState);
};

#endif // RESULTSMODEL_H
