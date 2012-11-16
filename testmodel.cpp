#include "testmodel.h"
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

TestModel::TestModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(VariantTitleRole, "variantTitle");
    setRoleNames(role_names);
}

int TestModel::rowCount(const QModelIndex &/*aParent*/) const
{
    return _variants.size();
}

QVariant TestModel::data(const QModelIndex &aIndex, int aRole) const
{
    QVariant ret_value;
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

QString TestModel::description() const
{
    return _description;
}

void TestModel::setNewScene(const TestScene &aNewScene)
{
    _description = aNewScene._description;
    emit descriptionChanged();
    beginResetModel();
    _correctAnswer = aNewScene._correctAnswer;
    _variants = aNewScene._variants;
    endResetModel();
}

void TestModel::newTest(const TestScene &aTestScene)
{
    setNewScene(aTestScene);
}

void TestModel::tryVariant(unsigned aVarianNumber)
{
    if (aVarianNumber == _correctAnswer) {
        emit hit();
    } else {
        emit miss();
    }
}
