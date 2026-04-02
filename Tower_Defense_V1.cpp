#define MEMTRACE
#include <iostream>
#include <fstream>
#include "app.h"
#include "memtrace.h"

int main()
{
    std::ifstream map("palya.txt");
    App myApp(map);
    myApp.run();
    return 0;

}
