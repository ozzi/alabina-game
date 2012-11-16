#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QFile>
#include "qmlapplicationviewer.h"
#include "scenemanager.h"
#include "descriptionmodel.h"
#include "testmodel.h"
#include "levelmodel.h"
#include "resultsmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    DescriptionModel description_manager;
    TestModel test_manager;
    SceneManager scene_manager;
    LevelModel level_manager;
    ResultsModel result_model;
    QObject::connect(&test_manager, SIGNAL(hit()), &result_model, SLOT(onTestHit()));
    QObject::connect(&test_manager, SIGNAL(miss()), &result_model, SLOT(onTestMiss()));
    QObject::connect(&level_manager,
                     SIGNAL(levelChanged(std::shared_ptr<LevelDescription>)),
                     &result_model,
                     SLOT(onNewLevel(std::shared_ptr<LevelDescription>)));
    QObject::connect(&scene_manager,
                     SIGNAL(testChanged(TestScene)),
                     &result_model,
                     SLOT(onNewTest()));
    QObject::connect(&scene_manager,
                     SIGNAL(descriptionChanged(DescriptionScene)),
                     &description_manager,
                     SLOT(newScene(DescriptionScene)));
    QObject::connect(&scene_manager,
                     SIGNAL(testChanged(TestScene)),
                     &test_manager,
                     SLOT(newTest(TestScene)));
    QObject::connect(&level_manager,
                     SIGNAL(levelChanged(std::shared_ptr<LevelDescription>)),
                     &scene_manager,
                     SLOT(newLevel(std::shared_ptr<LevelDescription>)));
    QObject::connect(&test_manager, SIGNAL(hit()), &scene_manager, SLOT(nextScene()));

    QFile xml_file(":/database.xml");
    xml_file.open(QIODevice::ReadOnly);
    QString xml_content (QString::fromUtf8(xml_file.readAll(), xml_file.size()));
    level_manager.setImagesPath(QString::fromUtf8("../../../../../Dropbox/алабина игра/"));
    level_manager.initFromXML(xml_content);

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("cDescriptionModel", &description_manager);
    viewer.rootContext()->setContextProperty("cTestModel", &test_manager);
    viewer.rootContext()->setContextProperty("cSceneManager", &scene_manager);
    viewer.rootContext()->setContextProperty("cLevelModel", &level_manager);
    viewer.rootContext()->setContextProperty("cResultModel", &result_model);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/alabinagame/main.qml"));
    viewer.showExpanded();
    //viewer.setResizeMode(QmlApplicationViewer::SizeRootObjectToView);
    //viewer.showFullScreen();

    return app->exec();
}
