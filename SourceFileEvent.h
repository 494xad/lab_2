#pragma once

#include <vector>
#include "FileEventObserver.h"
#include "qfileinfo.h"

class SourceFileEvent
{
public:
    SourceFileEvent();

    ~SourceFileEvent();

    void addObserver(FileEventObserver* observer);

    void removeObserver(FileEventObserver* observer);

    void task();

private:

    /// Получить информацию о состоянии файла
    /// fileSize - ссылка для записи размера файла при его наличии
    FileEventObserver::FileState getFileState(qint64 &fileSize);

    std::vector<FileEventObserver*>     _observers;

};




