#include "scenemanager.h"
#include <cassert>
#include <QDebug>
#include "crashlogger.h"

SceneManager::SceneManager(QObject *parent) :
    QObject(parent), _state(SS_Final)
{
    ;
}

void SceneManager::reset()
{
    _chapter = _chapters.begin();
    _state = SS_Initial;
    nextScene();
}

void SceneManager::nextScene()
{
    SceneState new_scene_state = _state;
    do {
        if (new_scene_state == SS_Initial) {
            if (_chapter == _chapters.end()) {
                new_scene_state = SS_Final;
            } else {
                new_scene_state = SS_Description;
                _description = _chapter->_descriptions.begin();
                _test = _chapter->_tests.begin();
            }
        } else if (new_scene_state == SS_Description) {
            ++_description;
        } else if (new_scene_state == SS_Test) {
            ++_test;
        }
        if (new_scene_state == SS_Description && _description == _chapter->_descriptions.end()) {
            new_scene_state = SS_Test;
        }
        if (new_scene_state == SS_Test && _test == _chapter->_tests.end()) {
            new_scene_state = SS_Initial;
            ++_chapter;
        }
    } while (new_scene_state == SS_Initial);
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
    case SS_Description:
        return DescriptionState;
    case SS_Test:
        return TestState;
    case SS_Final:
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
    case SS_Description:
        emit descriptionChanged(*_description);
        break;
    case SS_Test:
        emit testChanged(*_test);
        break;
    case SS_Final:
    default:
        break;
    }
}
