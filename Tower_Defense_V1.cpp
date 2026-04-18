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
    App app;
    app.run();
     return 0;
}
