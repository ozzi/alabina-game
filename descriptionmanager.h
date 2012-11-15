#ifndef DESCRIPTIONMANAGER_H
#define DESCRIPTIONMANAGER_H

#include <QAbstractTableModel>
#include <vector>

struct Image
{
    QString path;
    QString description;
};

struct DescriptionScene
{
    QString _description;
    std::vector<Image> _images;
};

class DescriptionManager : public QAbstractListModel
{
    Q_OBJECT
    std::vector<Image> _images;
    QString _description;
    void setMaxColumn (int aMaxColumn);
    void setMaxRow (int aMaxRow);
public:
    explicit DescriptionManager(QObject *parent = 0);

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged)
    QString description () const;
    QString imagePath () const;

    enum ImageRoles
    {
      ImagePathRole = Qt::UserRole,
      ImageDescriptionRole
    };
    int rowCount (const QModelIndex & aParent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data (const QModelIndex & aIndex, int aRole) const;
    
signals:
    void descriptionChanged ();
    void imagePathChanged ();
public slots:
    void newScene (const DescriptionScene & aDescriptionScene);
};

#endif // DESCRIPTIONMANAGER_H
