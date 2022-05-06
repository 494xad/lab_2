#include "FileEventObserver.h"
#include <iostream>
//Конструктор
FileEventObserver::FileEventObserver()
{
}
//Деструктор
FileEventObserver::~FileEventObserver()
{
}

//Сообщить наблюдателю об измениении состояния файла
//state- состояние
//size- размер файла
void FileEventObserver::notifyObserver(FileState state, unsigned int size)
{
    switch (state)
    {
    case FileState::FILE_CHANGED:
        std::cout << "File changed, size:" << size << '\n'; 
        break;
    case FileState::FILE_EXSIST:
        std::cout << "File exsist, size:" << size << '\n';
        break;
    case FileState::FILE_NOT_EXSIST:
        std::cout << "File doesn't exsist\n";
        break;    
    default:
        break;
    }
}
