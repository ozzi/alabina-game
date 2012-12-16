#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QFile>
#include "qmlapplicationviewer.h"
#include "scenemanager.h"
#include "descriptionmodel.h"
#include "testmodel.h"
#include "levelmodel.h"
#include "resultsmodel.h"
#include "sessionmodel.h"
#include "levelpreviewmodel.h"
#include "recordsmodel.h"
#include "soundmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    DescriptionModel description_model;
    TestModel test_model;
    SceneManager scene_manager;
    LevelModel level_model;
    ResultsModel result_model;
    SessionModel session_model;
    LevelPreviewModel preview_model;
    RecordsModel records_model;
    SoundModel sound_model;
    sound_model.setSuccessPath("");
    sound_model.setFailPath("");

    QObject::connect(&test_model, SIGNAL(hit()), &result_model, SLOT(onTestHit()));
    QObject::connect(&test_model, SIGNAL(miss()), &result_model, SLOT(onTestMiss()));
    QObject::connect(&test_model, SIGNAL(hit()), &sound_model, SLOT(onTestHit()));
    QObject::connect(&test_model, SIGNAL(miss()), &sound_model, SLOT(onTestMiss()));
    QObject::connect(&level_model,
                     SIGNAL(levelChanged(std::shared_ptr<LevelDescription>)),
                     &result_model,
                     SLOT(onNewLevel(std::shared_ptr<LevelDescription>)));
    QObject::connect(&scene_manager,
                     SIGNAL(testChanged(TestScene)),
                     &result_model,
                     SLOT(onNewTest()));
    QObject::connect(&scene_manager,
                     SIGNAL(stateChanged(SceneState)),
                     &result_model,
                     SLOT(onStateChanged(SceneState)));
    QObject::connect(&scene_manager,
                     SIGNAL(descriptionChanged(DescriptionScene)),
                     &description_model,
                     SLOT(newScene(DescriptionScene)));
    QObject::connect(&scene_manager,
                     SIGNAL(testChanged(TestScene)),
                     &test_model,
                     SLOT(newTest(TestScene)));
    QObject::connect(&level_model,
                     SIGNAL(levelChanged(std::shared_ptr<LevelDescription>)),
                     &scene_manager,
                     SLOT(newLevel(std::shared_ptr<LevelDescription>)));
    QObject::connect(&test_model, SIGNAL(hit()), &scene_manager, SLOT(nextScene()));
    QObject::connect(&result_model,
                     SIGNAL(levelPoints(QString,uint)),
                     &session_model,
                     SLOT(onLevelCompleted(QString,uint)));
    QObject::connect(&level_model,
                     SIGNAL(levelChanged(std::shared_ptr<LevelDescription>)),
                     &preview_model,
                     SLOT(onLevelChanged(std::shared_ptr<LevelDescription>)));
    QObject::connect(&session_model,
                     SIGNAL(allLevelsCompleted(QString,uint)),
                     &records_model,
                     SLOT(onAllLevelsCompleted(QString,uint)));

    QFile xml_file(":/database.xml");
    xml_file.open(QIODevice::ReadOnly);
    QString xml_content (QString::fromUtf8(xml_file.readAll(), xml_file.size()));
    //const char *image_path = "../../../../../Dropbox/алабина игра/";
    const char *image_path = "../../";
    level_model.setImagesPath(QString::fromUtf8(image_path));
    level_model.initFromXML(xml_content);

    session_model.setLevelsInfo(level_model.rowCount(QModelIndex()));

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("cDescriptionModel", &description_model);
    viewer.rootContext()->setContextProperty("cTestModel", &test_model);
    viewer.rootContext()->setContextProperty("cSceneManager", &scene_manager);
    viewer.rootContext()->setContextProperty("cLevelModel", &level_model);
    viewer.rootContext()->setContextProperty("cResultModel", &result_model);
    viewer.rootContext()->setContextProperty("cSessionModel", &session_model);
    viewer.rootContext()->setContextProperty("cPreviewModel", &preview_model);
    viewer.rootContext()->setContextProperty("cRecordsModel", &records_model);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/alabinagame/main.qml"));
    //viewer.showExpanded();
    viewer.setResizeMode(QmlApplicationViewer::SizeRootObjectToView);
    viewer.showFullScreen();

    return app->exec();
}
