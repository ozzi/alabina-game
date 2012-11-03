#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <memory>
#include <QAbstractListModel>
#include "descriptionmanager.h"
#include "testmanager.h"

struct Chapter
{
    std::vector<DescriptionScene> _descriptions;
    std::vector<TestScene> _tests;
    QString _title;
};

typedef std::vector<Chapter> Chapters;

struct LevelDescription
{
    unsigned _id;
    QString _name;
    QString _imagePath;
    QString _description;
    Chapters _chapters;
};

class QXmlStreamReader;

class LevelManager : public QAbstractListModel
{
    Q_OBJECT
    std::vector<std::shared_ptr<LevelDescription>> _levels;
    unsigned _currentLevel;

    std::shared_ptr<LevelDescription> parseLevel (QXmlStreamReader* aXmlStreamReader);
    Chapters parseChapters (QXmlStreamReader* aXmlStreamReader);
    Chapter parseChapter (QXmlStreamReader* aXmlStreamReader);
    std::vector<DescriptionScene> parseDescriptions (QXmlStreamReader* aXmlStreamReader);
    DescriptionScene parseDescription (QXmlStreamReader* aXmlStreamReader);
    std::vector<Image> parseImages (QXmlStreamReader* aXmlStreamReader);
    Image parseImage (QXmlStreamReader* aXmlStreamReader);
    std::vector<TestScene> parseTests (QXmlStreamReader* aXmlStreamReader);
    TestScene parseTest (QXmlStreamReader* aXmlStreamReader);
    std::vector<Variant> parseVariants (QXmlStreamReader *aXmlStreamReader);
    Variant parseVariant (QXmlStreamReader *aXmlStreamReader);

public:
    explicit LevelManager(QObject *parent = 0);
    enum LevelRoles
    {
        LevelIdRole = Qt::UserRole,
        LevelNameRole,
        LevelImageRole,
        LevelDescriptionRole
    };
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex & aIndex, int aRole) const;

    Q_INVOKABLE void setLevel (unsigned aNewLevel);

    void initFromXML (const QString & aXmlContent);
signals:
    void levelChanged(const std::shared_ptr<LevelDescription> & aLevelDescription);
public slots:
    
};

#endif // LEVELMANAGER_H