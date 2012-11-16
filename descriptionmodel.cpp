#include "descriptionmodel.h"
#include <cassert>
#include <cmath>
#include <QDebug>
#include "crashlogger.h"

DescriptionModel::DescriptionModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(ImagePathRole, "imagePath");
    role_names.insert(ImageDescriptionRole, "imageDescription");
    setRoleNames(role_names);
}

int DescriptionModel::rowCount (const QModelIndex& aParent) const
{
    return _images.size();
}

int DescriptionModel::columnCount(const QModelIndex& aParent) const
{
    return 1;
}

QVariant DescriptionModel::data (const QModelIndex & aIndex, int aRole) const
{
    QVariant result;
    if (aIndex.isValid()) {
        unsigned image_index = aIndex.row();
        auto image = _images.at(image_index);
        switch (static_cast<ImageRoles>(aRole))
        {
        case ImagePathRole:
            result = image.path;
            break;
        case ImageDescriptionRole:
            result = image.description;
            break;
        default:
            qDebug() << "DescriptionManager::data unknown role == " << aRole;
            assert(FALSE);
            break;
        }
    } else {
        qDebug() << "invalid index!!!!";
    }
    return result;
}

QString DescriptionModel::description() const
{
    return _description;
}

QString DescriptionModel::imagePath() const
{
    return _imagePath;
}

void DescriptionModel::newScene(const DescriptionScene &aDescriptionScene)
{
    beginResetModel();
    _images = aDescriptionScene._images;
    endResetModel();
    _description = aDescriptionScene._description;
    emit descriptionChanged();
    _imagePath = _images.empty() ? QString() : _images.begin()->path;
    emit imagePathChanged();
}
