

#include <iostream>
#include "LabEngine.h"


int main(int argc, char** argv)
{
    std::cout << "ICT397 Assignment 1!\n";

   // auto &app = Lab::LabEngine::getInstance();
    auto& app = LabEngine::getInstance();
    app.run();
    
    return 0;
}

