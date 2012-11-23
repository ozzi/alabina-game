#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <memory.h>
#include <vector>
#include "descriptionmodel.h"
#include "testmodel.h"
#include "levelmodel.h"

class CommonSceneState
{
public:
    virtual void emit_state() = 0;
};

class DescriptionSceneStateDelegate
{
public:
    virtual void emit_description (const DescriptionScene & scene) = 0;
};

class TestSceneStateDelegate
{
public:
    virtual void emit_test (const TestScene & scene) = 0;
};

class DescriptionSceneState : public CommonSceneState
{
    DescriptionScene _description;
    DescriptionSceneStateDelegate *_delegate;
public:
    DescriptionSceneState (const DescriptionScene &scene, DescriptionSceneStateDelegate *aDelegate);
    void emit_state();
};

class TestSceneState : public CommonSceneState
{
    TestScene _test;
    TestSceneStateDelegate *_delegate;
public:
    TestSceneState (const TestScene & scene, TestSceneStateDelegate *aDelegate);
    void emit_state();
};

enum SceneState
{
    SS_Description,
    SS_Test,
    SS_Final,
    SS_Initial
};

class SceneManager : public QObject, public DescriptionSceneStateDelegate, public TestSceneStateDelegate
{
    Q_OBJECT
    Chapters _originalChapters;
    std::vector<std::shared_ptr<CommonSceneState>> _scenes;
    std::vector<std::shared_ptr<CommonSceneState>>::const_iterator _currentScene;
    SceneState _state;
    unsigned _maximumTestsLength;

    void buildList();
    void descriptionsWorker(const std::vector<DescriptionScene> &aDescriptions);
    void testsWorker(const std::vector<TestScene> &aTests);
    void shuffleTestsWorker(const std::vector<TestScene> &aTests);
    void setState (SceneState aSceneState);
public:
    explicit SceneManager(QObject *parent = 0);
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    QString state () const;
    Q_INVOKABLE void reset();
    void emit_description(const DescriptionScene &scene);
    void emit_test(const TestScene &scene);
signals:
    void stateChanged(SceneState aNewState);
    void descriptionChanged (const DescriptionScene& aDescriptionScene) const;
    void testChanged (const TestScene& aTestScene) const;
public slots:
    void newLevel (const std::shared_ptr<LevelDescription> & aLevelDescription);
    void nextScene();
    void prevScene();
};

#endif // SCENEMANAGER_H
