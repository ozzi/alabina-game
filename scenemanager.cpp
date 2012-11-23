#include "scenemanager.h"
#include <algorithm>
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

DescriptionSceneState::DescriptionSceneState(const DescriptionScene &scene, DescriptionSceneStateDelegate *aDelegate) :
    _description(scene), _delegate(aDelegate) {}

void DescriptionSceneState::emit_state()
{
    _delegate->emit_description(_description);
}

TestSceneState::TestSceneState(const TestScene &scene, TestSceneStateDelegate *aDelegate) :
    _test(scene), _delegate(aDelegate) {}

void TestSceneState::emit_state()
{
    _delegate->emit_test(_test);
}

SceneManager::SceneManager(QObject *parent) :
    QObject(parent), _currentScene(_scenes.end()), _state(SS_Initial), _maximumTestsLength(3)
{}

void SceneManager::reset()
{
    setState(SS_Initial);
    buildList();
    _currentScene = _scenes.begin();
}

void SceneManager::buildList()
{
    _scenes.clear();
    for (auto chapter = _originalChapters.begin(); chapter != _originalChapters.end(); ++chapter) {
        descriptionsWorker(chapter->_descriptions);
        shuffleTestsWorker(chapter->_tests);
        //testsWorker(chapter->_tests);
    }
}

void SceneManager::descriptionsWorker(const std::vector<DescriptionScene> &aDescriptions)
{
    for (auto description = aDescriptions.begin(); description != aDescriptions.end(); ++description) {
        _scenes.push_back(std::make_shared<DescriptionSceneState>(*description, this));
    }
}

void SceneManager::testsWorker(const std::vector<TestScene> &aTests)
{
    for (auto test = aTests.begin(); test != aTests.end(); ++test) {
        _scenes.push_back(std::make_shared<TestSceneState>(*test, this));
    }
}

void SceneManager::shuffleTestsWorker(const std::vector<TestScene> &aTests)
{
    std::vector<TestScene> shuffle_tests(aTests);
    std::random_shuffle(shuffle_tests.begin(), shuffle_tests.end());
    if (shuffle_tests.size() > _maximumTestsLength) {
        shuffle_tests.resize(_maximumTestsLength);
    }
    testsWorker(shuffle_tests);
}

void SceneManager::emit_description(const DescriptionScene &scene)
{
    setState(SS_Description);
    emit descriptionChanged(scene);
}

void SceneManager::emit_test(const TestScene &scene)
{
    setState(SS_Test);
    emit testChanged(scene);
}

void SceneManager::nextScene()
{
    if (_state != SS_Final) {
        if (_state != SS_Initial) {
            ++_currentScene;
        }
        if (_currentScene != _scenes.end()) {
            (*_currentScene)->emit_state();
        } else {
            setState(SS_Final);
        }
    }
}

void SceneManager::prevScene()
{
    if (_state != SS_Initial) {
        if (_currentScene != _scenes.begin()) {
            --_currentScene;
            (*_currentScene)->emit_state();
        } else {
            setState(SS_Initial);
        }
    }
}

QString SceneManager::state() const
{
    static const QString DescriptionState = "description";
    static const QString TestState = "test";
    static const QString FinalState = "final";
    static const QString InitialState = "initial";

    switch (_state)
    {
    case SS_Description:
        return DescriptionState;
    case SS_Test:
        return TestState;
    case SS_Final:
        return FinalState;
    case SS_Initial:
        return InitialState;
    default:
        assert(FALSE);
        return QString();
    }
}

void SceneManager::setState(SceneState aSceneState)
{
    if (aSceneState != _state) {
        _state = aSceneState;
        emit stateChanged(_state);
    }
}

void SceneManager::newLevel(const std::shared_ptr<LevelDescription> &aLevel)
{
    _originalChapters = aLevel->_chapters;
    reset();
}
