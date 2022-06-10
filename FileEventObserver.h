#pragma once
class FileEventObserver

{
public:
    //Состояние файла
    enum FileState{
        FILE_EXSIST,
        FILE_CHANGED,
        FILE_NOT_EXSIST
    };
    //Конструктор
    FileEventObserver(/* args */);
    //Деструктор
    ~FileEventObserver();
    //Сообщить наблюдателю об измениении состояния файла
    //state- состояние
    //size- размер файла
    void notifyObserver(FileState state, unsigned int size);
};

