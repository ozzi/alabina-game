#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QPair>
#include <QVector>

class SessionModel : public QAbstractListModel
{
    Q_OBJECT
    QMap<QString, unsigned> _results;
    QVector<QPair<QString, unsigned>> _orderedResults;
    QString _username;
    unsigned _totalPoints;
    unsigned _levelsNumber;
    enum ResultRoles
    {
        ResultNameRole = Qt::UserRole,
        ResultPointsRole
    };
    void buildOrderedResults();
public:
    explicit SessionModel(QObject *parent = 0);
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex &aIndex, int aRole) const;

    Q_PROPERTY (QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY (unsigned totalPoints READ totalPoints NOTIFY totalPointsChanged)
    const QString &username() const;
    void setUsername (const QString &username);
    Q_INVOKABLE void setDefaultUserName();
    unsigned totalPoints () const;
    void setLevelsInfo (unsigned aLevelsNumber);
signals:
    void usernameChanged(const QString & username);
    void totalPointsChanged(unsigned totalPoints);
    void allLevelsCompleted(const QString &aUserName, unsigned aTotalPoints);
public slots:
    void onLevelCompleted(const QString &aLevelName, unsigned aTotalPoints);
};

#endif // SESSIONMODEL_H
