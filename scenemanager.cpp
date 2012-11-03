#include "scenemanager.h"
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

SceneManager::SceneManager(QObject *parent) :
    QObject(parent), _state(SceneState::Final)
{
    ;
}

void SceneManager::reset()
{
    _chapter = _chapters.begin();
    _state = SceneState::Initial;
    nextScene();
}

void SceneManager::nextScene()
{
    CrashLogger logger("nextscene");
    SceneState new_scene_state = _state;
    do {
        if (new_scene_state == SceneState::Initial) {
            if (_chapter == _chapters.end()) {
                new_scene_state = SceneState::Final;
            } else {
                new_scene_state = SceneState::Description;
                _description = _chapter->_descriptions.begin();
                _test = _chapter->_tests.begin();
            }
        } else if (new_scene_state == SceneState::Description) {
            ++_description;
        } else if (new_scene_state == SceneState::Test) {
            ++_test;
        }
        if (new_scene_state == SceneState::Description && _description == _chapter->_descriptions.end()) {
            new_scene_state = SceneState::Test;
        }
        if (new_scene_state == SceneState::Test && _test == _chapter->_tests.end()) {
            new_scene_state = SceneState::Initial;
            ++_chapter;
        }
    } while (new_scene_state == SceneState::Initial);
    notifyCurrentScene(new_scene_state);
}

void SceneManager::prevScene()
{
    ;
}

QString SceneManager::state() const
{
    static const QString DescriptionState = "description";
    static const QString TestState = "test";
    static const QString FinalState = "final";

    switch (_state)
    {
    case SceneState::Description:
        return DescriptionState;
    case SceneState::Test:
        return TestState;
    case SceneState::Final:
    default:
        return FinalState;
    }
}

void SceneManager::newLevel(const std::shared_ptr<LevelDescription> &aLevel)
{
    _chapters = aLevel->_chapters;
    reset();
}

void SceneManager::notifyCurrentScene (SceneState new_scene_state)
{
    if (new_scene_state != _state) {
        _state = new_scene_state;
        emit stateChanged();
    }
    switch (_state)
    {
    case SceneState::Description:
        emit descriptionChanged(*_description);
        break;
    case SceneState::Test:
        emit testChanged(*_test);
        break;
    case SceneState::Final:
    default:
        qDebug() << "FINAL scene";
        break;
    }
}
