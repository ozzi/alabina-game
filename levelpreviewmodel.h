#ifndef LEVELPREVIEWMODEL_H
#define LEVELPREVIEWMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "levelmodel.h"

class LevelPreviewModel : public QAbstractListModel
{
    Q_OBJECT
    std::vector<QString> _images;
    unsigned _imagesCount;
    QString _name;
    QString _description;
public:
    explicit LevelPreviewModel(QObject *parent = 0);
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex & aIndex, int aRole) const;
    Q_PROPERTY(QString currentLevelDescription READ currentLevelDescription NOTIFY levelChanged)
    Q_PROPERTY(QString currentLevelName READ currentLevelName NOTIFY levelChanged)
    const QString &currentLevelDescription () const;
    const QString &currentLevelName () const;
signals:
    void levelChanged();
public slots:
    void onLevelChanged(const std::shared_ptr<LevelDescription> & aLevelDescription);
};

#endif // LEVELPREVIEWMODEL_H
