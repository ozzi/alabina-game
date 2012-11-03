#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <memory.h>
#include <vector>
#include "descriptionmanager.h"
#include "testmanager.h"
#include "levelmanager.h"

class SceneManager : public QObject
{
    Q_OBJECT
    enum class SceneState
    {
        Description,
        Test,
        Final,
        Initial
    };

    Chapters _chapters;
    std::vector<DescriptionScene>::const_iterator _description;
    std::vector<TestScene>::const_iterator _test;
    Chapters::const_iterator _chapter;
    SceneState _state;

    void notifyCurrentScene(SceneState new_scene_state);
public:
    explicit SceneManager(QObject *parent = 0);
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    QString state () const;
    Q_INVOKABLE void reset();
signals:
    void stateChanged();
    void descriptionChanged (const DescriptionScene& aDescriptionScene);
    void testChanged (const TestScene& aTestScene);
public slots:
    void newLevel (const std::shared_ptr<LevelDescription> & aLevelDescription);
    void nextScene();
    void prevScene();
};

#endif // SCENEMANAGER_H