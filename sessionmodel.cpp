#include "sessionmodel.h"
#include <QDebug>
#include <cassert>
#include <numeric>
#include "crashlogger.h"

SessionModel::SessionModel(QObject *parent) :
    QAbstractListModel(parent), _totalPoints(0), _levelsNumber(0)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(ResultNameRole, "resultLevelName");
    role_names.insert(ResultPointsRole, "resultTotalPoints");
    setRoleNames(role_names);
}

void SessionModel::setLevelsInfo (unsigned aLevelsNumber)
{
    _levelsNumber = aLevelsNumber;
}

const QString &SessionModel::username() const
{
    return _username;
}

unsigned SessionModel::totalPoints() const
{
    return _totalPoints;
}

void SessionModel::setDefaultUserName()
{
    static int number = 0;
    QString default_user_name_prefix = "User_";
    setUsername(default_user_name_prefix + QString::number(++number));
}

void SessionModel::setUsername (const QString &username)
{
    if (username != _username) {
        _username = username;
        _totalPoints = 0;
        _results.clear();
        _orderedResults.clear();
        emit usernameChanged(_username);
    }
}

int SessionModel::rowCount (const QModelIndex & aParent) const
{
    return _orderedResults.size();
}

QVariant SessionModel::data (const QModelIndex &aIndex, int aRole) const
{
    QVariant ret_value;
    if (aIndex.isValid()) {
        switch (static_cast<ResultRoles>(aRole))
        {
        case ResultNameRole:
            ret_value = _orderedResults.at(aIndex.row()).first;
            break;
        case ResultPointsRole:
            ret_value = _orderedResults.at(aIndex.row()).second;
            break;
        default:
            qDebug() << "SessionModel::data unknown role == " << aRole;
            assert(FALSE);
            break;
        }
    }
    return ret_value;
}

void SessionModel::onLevelCompleted(const QString &aLevelName, unsigned aTotalPoints)
{
    beginResetModel();
    _results[aLevelName] = aTotalPoints;
    QList<unsigned> values = _results.values();
    _totalPoints = std::accumulate(values.begin(), values.end(), 0);
    buildOrderedResults();
    endResetModel();
    if (_orderedResults.size() == _levelsNumber) {
        emit allLevelsCompleted(_username, _totalPoints);
    }
}

void SessionModel::buildOrderedResults()
{
    _orderedResults.clear();
    _orderedResults.reserve(_results.size());
    for (auto item = _results.begin(); item != _results.end(); ++item) {
        _orderedResults.push_back(qMakePair(item.key(), item.value()));
    }
}
