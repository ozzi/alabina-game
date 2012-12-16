#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QAbstractListModel>
#include <vector>

struct Variant
{
    QString title;
};

struct TestScene
{
    std::vector<Variant> _variants;
    QString _description;
    QString _imagepath;
    unsigned _correctAnswer;
};

class TestModel : public QAbstractListModel
{
    Q_OBJECT
    std::vector<Variant> _variants;
    QString _description;
    QString _imagepath;
    unsigned _correctAnswer;

    void setNewScene (const TestScene & aNewScene);
    void shuffleVariants();
    void removeIncorrectVariant (unsigned aVariantNumber);
public:
    explicit TestModel(QObject *parent = 0);
    enum VariantRoles
    {
        VariantTitleRole = Qt::UserRole
    };
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex & aIndex, int aRole) const;

    Q_PROPERTY(QString description READ description NOTIFY testChanged)
    QString description () const;
    Q_PROPERTY(QString imagepath READ imagepath NOTIFY testChanged)
    QString imagepath () const;

signals:
    void testChanged();
    void hit();
    void miss();
public slots:
    void newTest (const TestScene& aTestScene);
    void tryVariant (unsigned aVarianNumber);
};

#endif // TESTMANAGER_H
