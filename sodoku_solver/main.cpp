//
//  main.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#include <iostream>

#include "sodoku.hpp"

int main(void)
{
    Sodoku mySodoku;
    if(mySodoku.load("input.txt"))
    {
        std::cout << mySodoku;
        mySodoku.solve();
        std::cout << mySodoku;
    }
    else
    {
        std::cout << "Failed to open sodoku!" << std::endl;
    }
}
