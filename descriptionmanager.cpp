#include "descriptionmanager.h"
#include <cassert>
#include <cmath>
#include <QDebug>
#include "crashlogger.h"

DescriptionManager::DescriptionManager(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(ImagePathRole, "imagePath");
    role_names.insert(ImageDescriptionRole, "imageDescription");
    setRoleNames(role_names);
}

int DescriptionManager::rowCount (const QModelIndex& aParent) const
{
    return _images.size();
}

int DescriptionManager::columnCount(const QModelIndex& aParent) const
{
    return 1;
}

QVariant DescriptionManager::data (const QModelIndex & aIndex, int aRole) const
{
    CrashLogger log("DescriptionManager::data");
    QVariant result;
    if (aIndex.isValid()) {
        //unsigned image_index = aIndex.row() * _columnCount + aIndex.column();
        unsigned image_index = aIndex.row();
        qDebug() << "image index == " << image_index << " images.size" << _images.size();
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

QString DescriptionManager::description() const
{
    return _description;
}

QString DescriptionManager::imagePath() const
{
    return _images.empty() ? QString() : _images.begin()->path;
}

void DescriptionManager::newScene(const DescriptionScene &aDescriptionScene)
{
    _description = aDescriptionScene._description;
    qDebug() << "DescriptionManager::newScene " << _description.size();
    emit descriptionChanged();
    beginResetModel();
    _images = aDescriptionScene._images;
    endResetModel();
}
