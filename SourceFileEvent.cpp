#include "SourceFileEvent.h"
#include <thread>
#include <chrono>
#include <iostream>

    //Конструктор
SourceFileEvent::SourceFileEvent()
{
    _fileInfo = new QFileInfo("C:\\Users\\Ксения\\Documents\\build-lab_2-Desktop_Qt_6_2_3_MinGW_64_bit-Debug\\debug\\observiable.txt");
}
     //Деструктор
SourceFileEvent::~SourceFileEvent()
{
    _observers.clear();
    delete _fileInfo;
}

//Добавить наблюдателя
void SourceFileEvent::addObserver(FileEventObserver* observer)
{
    _observers.push_back(observer);
}
//Удалить наблюдателя
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

    unsigned int fileSize = 0;
    FileEventObserver::FileState fileState;

    if(_fileInfo->exists()) {
        if (_fileInfo->birthTime() != _fileInfo->lastModified()) {
            fileState = FileEventObserver::FileState::FILE_CHANGED;
        } else {
            fileState = FileEventObserver::FileState::FILE_EXSIST;
        }
        fileSize = _fileInfo->size();
    } else {
        fileState = FileEventObserver::FileState::FILE_NOT_EXSIST;
    }

    for(auto obs: _observers) {
        obs->notifyObserver(fileState, fileSize);
    }

    FileEventObserver::FileState newFileState = fileState;
    while (true) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if(_fileInfo->exists()) {
            if (_fileInfo->birthTime() != _fileInfo->lastModified()) {
                newFileState = FileEventObserver::FileState::FILE_CHANGED;
            } else {
                newFileState = FileEventObserver::FileState::FILE_EXSIST;
            }
            fileSize = _fileInfo->size();
        } else {
            newFileState = FileEventObserver::FileState::FILE_NOT_EXSIST;
        }

        if(newFileState != fileState) {
            for(auto obs: _observers) {
                obs->notifyObserver(newFileState, fileSize);
            }
            fileState = newFileState;
        }
    }

}
