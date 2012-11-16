#include "resultsmodel.h"
#include <QDebug>
#include <cassert>

ResultsModel::ResultsModel(QObject *parent) :
    QAbstractListModel(parent), _pointsTotal(0), _maximumFailCount(3), _results(_maximumFailCount + 1, 0)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(ResultPointsRole, "resultPoints");
    setRoleNames(role_names);
}

int ResultsModel::rowCount(const QModelIndex &/*aParent*/) const
{
    return _results.size();
}

QVariant ResultsModel::data(const QModelIndex &aIndex, int aRole) const
{
    QVariant ret_value;
    if (aIndex.isValid()) {
        switch (static_cast<ResultRoles>(aRole))
        {
        case ResultPointsRole:
            ret_value = _results.at(aIndex.row());
            break;
        default:
            qDebug() << "ResultsModel::data unknown role == " << aRole;
            assert(FALSE);
            break;
        }
    }
    return ret_value;
}

unsigned ResultsModel::pointsTotal() const
{
    return _pointsTotal;
}

void ResultsModel::onNewTest()
{
    _failCount = 0;
}

void ResultsModel::onTestHit()
{
    if (_failCount > _maximumFailCount) {
        _failCount = _maximumFailCount;
    }
    beginResetModel();
    ++_results[_failCount];
    endResetModel();
    unsigned points = (1 << (_maximumFailCount - _failCount)) >> 1;
    _pointsTotal += points;
    emit pointsTotalChanged();
}

void ResultsModel::onTestMiss()
{
    ++_failCount;
}

void ResultsModel::onNewLevel(const std::shared_ptr<LevelDescription> & aLevelDescription)
{
    beginResetModel();
    _results.fill(0);
    endResetModel();
    _pointsTotal = 0;
    emit pointsTotalChanged();
}
