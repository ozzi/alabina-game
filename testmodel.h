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
    unsigned _correctAnswer;
};

class TestModel : public QAbstractListModel
{
    Q_OBJECT
    std::vector<Variant> _variants;
    QString _description;
    unsigned _correctAnswer;

    void setNewScene (const TestScene & aNewScene);
public:
    explicit TestModel(QObject *parent = 0);
    enum VariantRoles
    {
        VariantTitleRole = Qt::UserRole
    };
    int rowCount (const QModelIndex & aParent) const;
    QVariant data (const QModelIndex & aIndex, int aRole) const;

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    QString description () const;

signals:
    void descriptionChanged();
    void hit();
    void miss();
public slots:
    void newTest (const TestScene& aTestScene);
    void tryVariant (unsigned aVarianNumber);
};

#endif // TESTMANAGER_H
