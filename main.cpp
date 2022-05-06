#include "FileEventObserver.h"
#include "SourceFileEvent.h"

int main(int argc, char *argv[])
{
    FileEventObserver fileObserver;
    SourceFileEvent source;

    source.addObserver(&fileObserver);

    return 0;
}
