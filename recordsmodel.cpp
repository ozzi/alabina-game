#include "recordsmodel.h"
#include <QDebug>
#include <cassert>

RecordsModel::RecordsModel(QObject *parent) :
    QAbstractListModel(parent), _maximumRecords(10), _hit(false)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(RecordNameRole, "recordName");
    role_names.insert(RecordPointsRole, "recordPoints");
    fillDefaultRecords();
    setRoleNames(role_names);
}

void RecordsModel::resetOrderedResults()
{
    _orderedResults.clear();
    for (auto result = _results.rbegin();
         result != _results.rend();
         ++result) {
        _orderedResults.push_back(std::make_pair(result->second, result->first));
    }
}

void RecordsModel::fillDefaultRecords()
{
    _results.insert(std::make_pair(50, QString::fromUtf8("Минотаурус")));
    _results.insert(std::make_pair(28, QString::fromUtf8("Миша888")));
    _results.insert(std::make_pair(26, QString::fromUtf8("Григорий Распутин")));
    _results.insert(std::make_pair(25, QString::fromUtf8("Алиса Долина")));
    _results.insert(std::make_pair(21, QString::fromUtf8("Ира Масалитина")));
    _results.insert(std::make_pair(19, QString::fromUtf8("Саша Травкин")));
    _results.insert(std::make_pair(18, QString::fromUtf8("Валя Лекалова")));
    _results.insert(std::make_pair(15, QString::fromUtf8("Оля Самсонова")));
    _results.insert(std::make_pair(12, QString::fromUtf8("Петя Сидоров")));
    _results.insert(std::make_pair(10, QString::fromUtf8("Вася Иванов")));
    resetOrderedResults();
}

int RecordsModel::rowCount(const QModelIndex &/*aParent*/) const
{
    return _orderedResults.size();
}

QVariant RecordsModel::data(const QModelIndex &aIndex, int aRole) const
{
    QVariant ret_value;
    if (aIndex.isValid()) {
        switch (static_cast<RecordRoles>(aRole))
        {
        case RecordNameRole:
            ret_value = _orderedResults.at(aIndex.row()).first;
            break;
        case RecordPointsRole:
            ret_value = _orderedResults.at(aIndex.row()).second;
            break;
        default:
            qDebug() << "RecordsModel::data unknown role == " << aRole;
            assert(FALSE);
            break;
        }
    }
    return ret_value;
}

void RecordsModel::setMaximumRecords(unsigned aMaximumRecords)
{
    _maximumRecords = aMaximumRecords;
}

bool RecordsModel::hit () const
{
    return _hit;
}
const QString &RecordsModel::lastUsername () const
{
    return _lastUsername;
}

void RecordsModel::setHit(bool aHit)
{
    if (_hit != aHit) {
        _hit = aHit;
        emit hitChanged();
    }
}

void RecordsModel::setLastUsername(const QString & aUsername)
{
    if (_lastUsername != aUsername) {
        _lastUsername = aUsername;
        emit lastUsernameChanged();
    }
}

void RecordsModel::onAllLevelsCompleted(const QString &aUserName, unsigned aTotalPoints)
{
    if (_results.size() < _maximumRecords || aTotalPoints > _results.begin()->first) {
        while (_results.size() >= _maximumRecords) {
            _results.erase(_results.begin());
        }
        _results.insert(std::make_pair(aTotalPoints, aUserName));
        setLastUsername(aUserName);
        setHit(true);
    } else {
        setLastUsername(QString());
        setHit(false);
    }
    beginResetModel();
    resetOrderedResults();
    endResetModel();
}
