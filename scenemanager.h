#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <memory.h>
#include <vector>
#include <map>
#include "descriptionmodel.h"
#include "testmodel.h"
#include "levelmodel.h"

class CommonSceneState
{
public:
    virtual void emit_state() = 0;
};

struct DescriptionSceneExt : public DescriptionScene
{
    unsigned _chapterNumber;
    DescriptionSceneExt(const DescriptionScene & aScene, unsigned aChapterNumber);
};

struct TestSceneExt : public TestScene
{
    unsigned _chapterNumber;
    TestSceneExt(const TestScene & aScene, unsigned aChapterNumber);
};

class DescriptionSceneStateDelegate
{
public:
    virtual void emit_description (const DescriptionSceneExt & scene) = 0;
};

class TestSceneStateDelegate
{
public:
    virtual void emit_test (const TestSceneExt & scene) = 0;
};

class DescriptionSceneState : public CommonSceneState
{
    DescriptionSceneExt _description;
    DescriptionSceneStateDelegate *_delegate;
public:
    DescriptionSceneState (const DescriptionSceneExt &scene, DescriptionSceneStateDelegate *aDelegate);
    void emit_state();
};

class TestSceneState : public CommonSceneState
{
    TestSceneExt _test;
    TestSceneStateDelegate *_delegate;
public:
    TestSceneState (const TestSceneExt & scene, TestSceneStateDelegate *aDelegate);
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
    unsigned _chapterNumber;
    SceneState _state;
    unsigned _maximumTestsLength;

    void buildList();
    void descriptionsWorker(const std::vector<DescriptionScene> &aDescriptions, unsigned aChapterNumber);
    void testsWorker(const std::vector<TestScene> &aTests, unsigned aChapterNumber);
    void shuffleTestsWorker(const std::vector<TestScene> &aTests, unsigned aChapterNumber);
    void setState (SceneState aSceneState);
    void setChapter (unsigned aChapterNumber);
public:
    explicit SceneManager(QObject *parent = 0);
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    QString state () const;
    Q_PROPERTY(QString chapter READ chapter NOTIFY chapterChanged)
    QString chapter () const;
    Q_INVOKABLE void reset();
    void emit_description(const DescriptionSceneExt &scene);
    void emit_test(const TestSceneExt &scene);
signals:
    void stateChanged(SceneState aNewState);
    void descriptionChanged (const DescriptionScene& aDescriptionScene) const;
    void testChanged (const TestScene& aTestScene) const;
    void chapterChanged () const;
public slots:
    void newLevel (const std::shared_ptr<LevelDescription> & aLevelDescription);
    void nextScene();
    void prevScene();
};

#endif // SCENEMANAGER_H
