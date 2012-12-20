#include "scenemanager.h"
#include <algorithm>
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

DescriptionSceneExt::DescriptionSceneExt(const DescriptionScene &aScene, unsigned aChapterNumber) :
    DescriptionScene(aScene), _chapterNumber(aChapterNumber) {}

TestSceneExt::TestSceneExt(const TestScene &aScene, unsigned aChapterNumber) :
    TestScene(aScene), _chapterNumber(aChapterNumber) {}

DescriptionSceneState::DescriptionSceneState(const DescriptionSceneExt &scene, DescriptionSceneStateDelegate *aDelegate) :
    _description(scene), _delegate(aDelegate) {}

void DescriptionSceneState::emit_state()
{
    _delegate->emit_description(_description);
}

TestSceneState::TestSceneState(const TestSceneExt &scene, TestSceneStateDelegate *aDelegate) :
    _test(scene), _delegate(aDelegate) {}

void TestSceneState::emit_state()
{
    _delegate->emit_test(_test);
}

SceneManager::SceneManager(QObject *parent) :
    QObject(parent), _currentScene(_scenes.end()), _state(SS_Initial), _maximumTestsLength(6)
{}

void SceneManager::reset()
{
    setState(SS_Initial);
    setChapter(0);
    buildList();
    _currentScene = _scenes.begin();
}

void SceneManager::buildList()
{
    _scenes.clear();
    for (auto chapter = _originalChapters.begin(); chapter != _originalChapters.end(); ++chapter) {
        descriptionsWorker(chapter->_descriptions, chapter - _originalChapters.begin());
        shuffleTestsWorker(chapter->_tests, chapter - _originalChapters.begin());
        //testsWorker(chapter->_tests, chapter - _originalChapters.begin());
    }
}

void SceneManager::descriptionsWorker(const std::vector<DescriptionScene> &aDescriptions, unsigned aChapterNumber)
{
    for (auto description = aDescriptions.begin(); description != aDescriptions.end(); ++description) {
        _scenes.push_back(std::make_shared<DescriptionSceneState>(DescriptionSceneExt(*description, aChapterNumber), this));
    }
}

void SceneManager::testsWorker(const std::vector<TestScene> &aTests, unsigned aChapterNumber)
{
    for (auto test = aTests.begin(); test != aTests.end(); ++test) {
        _scenes.push_back(std::make_shared<TestSceneState>(TestSceneExt(*test, aChapterNumber), this));
    }
}

void SceneManager::shuffleTestsWorker(const std::vector<TestScene> &aTests, unsigned aChapterNumber)
{
    std::vector<TestScene> shuffle_tests(aTests);
    std::random_shuffle(shuffle_tests.begin(), shuffle_tests.end());
    if (shuffle_tests.size() > _maximumTestsLength) {
        shuffle_tests.resize(_maximumTestsLength);
    }
    testsWorker(shuffle_tests, aChapterNumber);
}

void SceneManager::emit_description(const DescriptionSceneExt &scene)
{
    setState(SS_Description);
    setChapter(scene._chapterNumber);
    emit descriptionChanged(scene);
}

void SceneManager::emit_test(const TestSceneExt &scene)
{
    setState(SS_Test);
    setChapter(scene._chapterNumber);
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

QString SceneManager::chapter() const
{
    QString chapter_title;
    if (_chapterNumber < _originalChapters.size()) {
        chapter_title = _originalChapters.at(_chapterNumber)._title;
    }
    return chapter_title;
}

void SceneManager::setState(SceneState aSceneState)
{
    if (aSceneState != _state) {
        _state = aSceneState;
        emit stateChanged(_state);
    }
}

void SceneManager::setChapter(unsigned aChapterNumber)
{
    if (aChapterNumber != _chapterNumber) {
        _chapterNumber = aChapterNumber;
        emit chapterChanged();
    }
}

void SceneManager::newLevel(const std::shared_ptr<LevelDescription> &aLevel)
{
    _originalChapters = aLevel->_chapters;
    emit chapterChanged();
    reset();
}
