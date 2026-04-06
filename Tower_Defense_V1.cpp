#define MEMTRACE
#include <iostream>
#include <fstream>
#include "app.h"
#include <ctime> 
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "memtrace.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::ifstream map("palya.txt");
	std::ifstream wave("wave1.txt");
    App myApp(map, wave);
    myApp.run();
     return 0;
}
