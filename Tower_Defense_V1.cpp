#define MEMTRACE
#include <iostream>
#include <fstream>
#include <ctime> 
#include <cstdlib>
#include "app.h"
#include "memtrace.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    App app;
    app.run();
    return 0;
}
