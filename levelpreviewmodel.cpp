#include "levelpreviewmodel.h"
#include <QDebug>

LevelPreviewModel::LevelPreviewModel(QObject *parent) :
    QAbstractListModel(parent), _imagesCount(3)
{
}

int LevelPreviewModel::rowCount (const QModelIndex & aParent) const
{
    return _images.size();
}

QVariant LevelPreviewModel::data (const QModelIndex & aIndex, int aRole) const
{
    QVariant result;
    if (aIndex.isValid()) {
        if (aRole == Qt::DisplayRole) {
            result = _images.at(aIndex.row());
        }
    }
    return result;
}

const QString &LevelPreviewModel::currentLevelDescription () const
{
    return _description;
}

const QString &LevelPreviewModel::currentLevelName () const
{
    return _name;
}

void LevelPreviewModel::onLevelChanged(const std::shared_ptr<LevelDescription> &aLevelDescription)
{
    _description = aLevelDescription->_description;
    _name = aLevelDescription->_name;
    beginResetModel();
    _images.clear();
    for (auto chapter = aLevelDescription->_chapters.begin();
         _images.size() < _imagesCount && chapter != aLevelDescription->_chapters.end();
         ++chapter) {
        for (auto description = chapter->_descriptions.begin();
             _images.size() < _imagesCount && description != chapter->_descriptions.end();
             ++description) {
            for (auto image = description->_images.begin();
                 _images.size() < _imagesCount && image != description->_images.end();
                 ++image) {
                _images.push_back(image->path);
            }
        }
    }
    endResetModel();
    emit levelChanged();
}
