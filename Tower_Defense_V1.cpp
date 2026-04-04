#define MEMTRACE
#include <iostream>
#include <fstream>
#include "app.h"
#include "memtrace.h"

int main()
{
    std::ifstream map("palya.txt");
	std::ifstream wave("wave1.txt");
    App myApp(map, wave);
    myApp.run();
    return 0;

}
