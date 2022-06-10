#include "FileEventObserver.h"
#include "SourceFileEvent.h"
#include <iostream>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileEventObserver fileObserver;
    SourceFileEvent* source = new SourceFileEvent();

    source->addObserver(&fileObserver);
    source->task();
    return a.exec();
}
