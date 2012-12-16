#include "testmodel.h"
#include <algorithm>
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

QString TestModel::imagepath() const
{
    return _imagepath;
}

void TestModel::setNewScene(const TestScene &aNewScene)
{
    _description = aNewScene._description;
    _imagepath = aNewScene._imagepath;
    emit testChanged();
    beginResetModel();
    _correctAnswer = aNewScene._correctAnswer;
    _variants = aNewScene._variants;
    shuffleVariants();
    endResetModel();
}

void TestModel::shuffleVariants()
{
    auto correct_answer_title = _variants.at(_correctAnswer).title;
    std::random_shuffle(_variants.begin(), _variants.end());
    for (auto variant = _variants.begin();
         variant != _variants.end();
         ++variant) {
        if (variant->title == correct_answer_title) {
            _correctAnswer = variant - _variants.begin();
            break;
        }
    }
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
        //removeIncorrectVariant(aVarianNumber);
    }
}

void TestModel::removeIncorrectVariant(unsigned aVariantNumber)
{
    if (aVariantNumber < _variants.size()) {
        beginResetModel();
        if (aVariantNumber < _correctAnswer) {
            --_correctAnswer;
        }
        _variants.erase(_variants.begin() + aVariantNumber);
        endResetModel();
    }
}
