#include <vector>
#include "FileEventObserver.h"
#include "qfileinfo.h"

class SourceFileEvent
{

public:
    //Конструктор
    SourceFileEvent();
    //Деструктор
    ~SourceFileEvent();
    //Добавить наблюдателя
    void addObserver(FileEventObserver* observer);
    //Удалить наблюдателя
    void removeObserver(FileEventObserver* observer);



private:
    //Вектор указателей на наблюдателей
    std::vector<FileEventObserver*>     _observers;
    //Указатель на объект для получения информации о файле
    QFileInfo*                          _fileInfo;

};

