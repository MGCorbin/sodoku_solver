//
//  conversion.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#include "conversion.hpp"


char hex_to_ascii(int d)
{
    if(d < 10)
        d += '0';
    else
        d += ('A' - 10);
    return d;
}
