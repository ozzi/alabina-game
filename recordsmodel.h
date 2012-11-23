#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <map>

class RecordsModel : public QAbstractListModel
{
    Q_OBJECT
    std::multimap<unsigned, QString> _results;
    std::vector<std::pair<QString, unsigned> > _orderedResults;
    unsigned _maximumRecords;
    bool _hit;
    QString _lastUsername;
    void setHit(bool aHit);
    void setLastUsername(const QString & aUsername);
    void resetOrderedResults();
    void fillDefaultRecords();

public:
    explicit RecordsModel(QObject *parent = 0);
    enum RecordRoles
    {
        RecordNameRole = Qt::UserRole,
        RecordPointsRole
    };
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex &aIndex, int aRole) const;
    Q_PROPERTY(bool hit READ hit NOTIFY hitChanged)
    Q_PROPERTY(QString lastUsername READ lastUsername NOTIFY lastUsernameChanged)
    bool hit () const;
    const QString &lastUsername () const;
    void setMaximumRecords (unsigned aMaximumRecords);
signals:
    void hitChanged();
    void lastUsernameChanged();
public slots:
    void onAllLevelsCompleted(const QString &aUserName, unsigned aTotalPoints);
};

#endif // RECORDSMODEL_H
