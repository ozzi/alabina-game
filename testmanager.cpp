#include "testmanager.h"
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

TestManager::TestManager(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(VariantTitleRole, "variantTitle");
    setRoleNames(role_names);
}

int TestManager::rowCount(const QModelIndex &/*aParent*/) const
{
    qDebug() << "TestManager::rowCount " << _variants.size();
    return _variants.size();
}

QVariant TestManager::data(const QModelIndex &aIndex, int aRole) const
{
    QVariant ret_value;
    qDebug() << "TestManager::data " << aIndex.row();
    if (aIndex.isValid()) {
        switch (static_cast<VariantRoles>(aRole))
        {
        case VariantTitleRole:
            ret_value = _variants.at(aIndex.row()).title;
            break;
        default:
            qDebug() << "TestManager::data unknown role == " << aRole;
            assert(FALSE);
            break;
        }
    }
    return ret_value;
}

QString TestManager::description() const
{
    return _description;
}

void TestManager::setNewScene(const TestScene &aNewScene)
{
    _description = aNewScene._description;
    emit descriptionChanged();
    beginResetModel();
    _correctAnswer = aNewScene._correctAnswer;
    _variants = aNewScene._variants;
    endResetModel();
}

void TestManager::newTest(const TestScene &aTestScene)
{
    setNewScene(aTestScene);
}

void TestManager::tryVariant(unsigned aVarianNumber)
{
    if (aVarianNumber == _correctAnswer) {
        emit hit();
    } else {
        emit miss();
    }
}
