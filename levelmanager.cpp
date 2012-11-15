#include "levelmanager.h"
#include <cassert>
#include <QXmlStreamReader>
#include <QDebug>
#include "crashlogger.h"

LevelManager::LevelManager(QObject *parent) :
    QAbstractListModel(parent), _currentLevel(0)
{
    QHash<int, QByteArray> role_names;
    role_names.insert(LevelIdRole, "levelId");
    role_names.insert(LevelNameRole, "levelName");
    role_names.insert(LevelImageRole, "levelImage");
    role_names.insert(LevelDescriptionRole, "levelDescription");
    setRoleNames(role_names);
}

void LevelManager::setImagesPath (const QString & aImagesPath)
{
    _imagesPath = aImagesPath;
}

int LevelManager::rowCount (const QModelIndex & aParent) const
{
    return _levels.size();
}

QVariant LevelManager::data (const QModelIndex & aIndex, int aRole) const
{
    QVariant result;
    if (aIndex.isValid()) {
        switch (static_cast<LevelRoles>(aRole))
        {
        case LevelIdRole:
            result = _levels.at(aIndex.row())->_id;
            break;
        case LevelNameRole:
            result = _levels.at(aIndex.row())->_name;
            break;
        case LevelImageRole:
            result = _levels.at(aIndex.row())->_imagePath;
            break;
        case LevelDescriptionRole:
            result = _levels.at(aIndex.row())->_description;
            break;
        default:
            break;
        }
    }
    return result;
}

void LevelManager::setLevel (unsigned aNewLevel)
{
    emit levelChanged(_levels.at(_currentLevel));
}

void LevelManager::initFromXML (const QString & aXmlContent)
{
    QXmlStreamReader reader(aXmlContent);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartDocument()) {
            continue;
        } else if (reader.isStartElement()) {
            if (reader.name() == "database") {
                continue;
            } else if (reader.name() == "game") {
                continue;
            } else if (reader.name() == "level") {
                _levels.push_back(parseLevel(&reader));
            }
        }
    }
    if (reader.hasError()) {
        qDebug() << "LevelManager::initFromXML error " << reader.error();
    } else {
        emit levelChanged(_levels.at(_currentLevel));
    }
}

std::shared_ptr<LevelDescription> LevelManager::parseLevel(QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseLevel");
    auto result = std::make_shared<LevelDescription>();
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "level")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "name") {
                result->_name = aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "description") {
                result->_description = aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "image") {
                result->_imagePath = _imagesPath + aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "chapters") {
                result->_chapters = parseChapters(aXmlStreamReader);
            }
        }
    }
    return result;
}

Chapters LevelManager::parseChapters(QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseChapters");
    Chapters result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "chapters")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "chapter") {
                result.push_back(parseChapter(aXmlStreamReader));
            }
        }
    }
    return result;
}

Chapter LevelManager::parseChapter(QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseChapter");
    Chapter result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "chapter")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "title") {
                result._title = aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "descriptions") {
                result._descriptions = parseDescriptions(aXmlStreamReader);
            } else if (aXmlStreamReader->name() == "tests") {
                result._tests = parseTests(aXmlStreamReader);
            }
        }
    }
    return result;
}

std::vector<DescriptionScene> LevelManager::parseDescriptions(QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseDescriptions");
    std::vector<DescriptionScene> result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "descriptions")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "description") {
                result.push_back(parseDescription(aXmlStreamReader));
            }
        }
    }
    return result;
}

DescriptionScene LevelManager::parseDescription (QXmlStreamReader *aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseDescription");
    DescriptionScene result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "description")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "content") {
                result._description = aXmlStreamReader->readElementText();
                qDebug() << "LevelManager::parseDescription " << result._description.size();
            } else if (aXmlStreamReader->name() == "images") {
                result._images = parseImages(aXmlStreamReader);
            }
        }
    }
    return result;
}

std::vector<Image> LevelManager::parseImages (QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseImages");
    std::vector<Image> result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "images")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "imagedesc") {
                result.push_back(parseImage(aXmlStreamReader));
            }
        }
    }
    return result;
}

Image LevelManager::parseImage (QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseImage");
    Image result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "imagedesc")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "title") {
                result.description = aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "path") {
                result.path = _imagesPath + aXmlStreamReader->readElementText();
            }
        }
    }
    return result;
}

std::vector<TestScene> LevelManager::parseTests(QXmlStreamReader* aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseTests");
    std::vector<TestScene> result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "tests")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "test") {
                result.push_back(parseTest(aXmlStreamReader));
            }
        }
    }
    return result;
}

TestScene LevelManager::parseTest(QXmlStreamReader *aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseTest");
    TestScene result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "test")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "title") {
                result._description = aXmlStreamReader->readElementText();
            } else if (aXmlStreamReader->name() == "correctanswer") {
                QString correct_answer = aXmlStreamReader->readElementText();
                result._correctAnswer = correct_answer.toUInt();
            } else if (aXmlStreamReader->name() == "variants") {
                result._variants = parseVariants(aXmlStreamReader);
            }
        }
    }
    return result;
}

std::vector<Variant> LevelManager::parseVariants(QXmlStreamReader *aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseVariants");
    std::vector<Variant> result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "variants")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "variant") {
                result.push_back(parseVariant(aXmlStreamReader));
            }
        }
    }
    return result;
}

Variant LevelManager::parseVariant(QXmlStreamReader *aXmlStreamReader)
{
    assert(aXmlStreamReader);
    CrashLogger logger("LevelManager::parseVariant");
    Variant result;
    while (!aXmlStreamReader->atEnd() &&
           !(aXmlStreamReader->isEndElement() && aXmlStreamReader->name() == "variant")) {
        aXmlStreamReader->readNext();
        if (aXmlStreamReader->isStartElement()) {
            if (aXmlStreamReader->name() == "text") {
                result.title = aXmlStreamReader->readElementText();
            }
        }
    }
    return result;
}
