#include "descriptionmanager.h"
#include <cassert>
#include <cmath>
#include <QDebug>
#include "crashlogger.h"

DescriptionManager::DescriptionManager(QObject *parent) :
    QAbstractListModel(parent), _rowCount(0), _columnCount(0)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(ImagePathRole, "imagePath");
    role_names.insert(ImageDescriptionRole, "imageDescription");
    setRoleNames(role_names);
}

int DescriptionManager::rowCount (const QModelIndex & /*aParent*/) const
{
    return _rowCount;
}

int DescriptionManager::columnCount(const QModelIndex &parent) const
{
    int size = _images.size() - _columnCount * parent.row();
    return size >= _columnCount ? _columnCount : (size > 0 ? size : 0);
}

QVariant DescriptionManager::data (const QModelIndex & aIndex, int aRole) const
{
    QVariant result;
    if (aIndex.isValid()) {
        auto image = _images.at(aIndex.row() * _columnCount + aIndex.column());
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
    CrashLogger logger("DescriptionManager::newScene");
    _description = aDescriptionScene._description;
    emit descriptionChanged();
    beginResetModel();
    _images = aDescriptionScene._images;
    _rowCount = _columnCount = sqrt(_images.size());
    if ((_rowCount * _columnCount) < _images.size()) {
        ++_rowCount;
        ++_columnCount;
    }
    qDebug() << "DescriptionManager _images.size " << _images.size() << " columnt size " << _columnCount << " row size " << _rowCount;
    endResetModel();
}
