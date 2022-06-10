#include "SourceFileEvent.h"
#include <QDateTime>
#include <QThread>


SourceFileEvent::SourceFileEvent()
{

}

SourceFileEvent::~SourceFileEvent()
{
    _observers.clear();
}


void SourceFileEvent::addObserver(FileEventObserver* observer)
{
    _observers.push_back(observer);
}

void SourceFileEvent::removeObserver(FileEventObserver* observer)
{
    unsigned int obsCount = _observers.size();
    for (unsigned int i = 0; i < obsCount; i++) {
        if(_observers[i] == observer){
            _observers.erase(_observers.begin() + i);
        }
    }
}

void SourceFileEvent::task()
{
    qint64 fileSize = 0;
    FileEventObserver::FileState fileState = getFileState(fileSize);

    // Оповещение наблюдателей о состоянии файла
    for(auto obs: _observers) {
        obs->notifyObserver(fileState, fileSize);
    }

    FileEventObserver::FileState newFileState = fileState;
    while (true) {

        QThread::msleep(100);

        newFileState = getFileState(fileSize);

        if(newFileState != fileState) { // Если состояние файла поменялось, производится оповещение наблюдателей
            for(auto obs: _observers) {
                obs->notifyObserver(newFileState, fileSize);
            }
            fileState = newFileState;
        }
    }

}

/// Получить информацию о состоянии файла
/// fileSize - ссылка для записи размера файла при его наличии
FileEventObserver::FileState SourceFileEvent::getFileState(qint64 &fileSize)
{
    FileEventObserver::FileState fileState;
    //Создание объекта для чтения инфоррмации о файле
    QFileInfo fileInfo("observiable.txt");

    if(fileInfo.exists()) { //Если файл существует
        if (fileInfo.birthTime() != fileInfo.lastModified()) { // Если файл был модифицирован
            fileState = FileEventObserver::FileState::FILE_CHANGED;
        } else {
            fileState = FileEventObserver::FileState::FILE_EXSIST;
        }
        fileSize = fileInfo.size();
    } else {
        fileState = FileEventObserver::FileState::FILE_NOT_EXSIST;
    }
    return fileState;
}
