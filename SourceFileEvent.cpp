#include "SourceFileEvent.h"

    //Конструктор
SourceFileEvent::SourceFileEvent()
{
    _fileInfo = new QFileInfo("observiable.txt");
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

