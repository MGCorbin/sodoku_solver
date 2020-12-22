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
    Sodoku mySodoku(9, 3);
    if(mySodoku.load("input.txt"))
    {
        mySodoku.print();
    }
    else
    {
        std::cout << "Failed to open sodoku!" << std::endl;
    }
}
