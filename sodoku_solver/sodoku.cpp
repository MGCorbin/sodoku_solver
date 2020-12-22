//
//  sodoku.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#include <iostream>
#include <fstream>

#include "sodoku.hpp"

Sodoku::Sodoku(const int gridSize, const int miniGridSize)
    : m_GridSize(gridSize), m_MiniGridSize(miniGridSize)
{
    m_Grid.resize(m_GridSize, std::vector<char>(m_GridSize, 0));
}

bool Sodoku::load(const char* inFile)
{
    std::fstream inStream;
    
    inStream.open(inFile);
    
    if(inStream.is_open())
    {
        for(int row=0; row<m_GridSize; row++)
        {
            for(int col=0; col<m_GridSize; col++)
            {
                char val;
                inStream >> val;
                m_Grid[row][col] = val;
            }
        }
        
        inStream.close();
        return true;
    }
    return false;
}

void Sodoku::print()
{
    std::string divider = " ------ ------ ------ ";
    
    for(int row=0; row<m_Grid.size(); row++)
    {
        if(!(row % m_MiniGridSize))
        {
            std::cout << divider << std::endl;
        }
        
        for(int col=0; col<m_Grid[0].size(); col++)
        {
            if(!(col % m_MiniGridSize))
            {
                std::cout << "|";
            }
            std::cout << m_Grid.at(row).at(col) << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << divider << std::endl << std::endl;
}

bool Sodoku::solve()
{
    return false;
}

bool Sodoku::noConflict(int row, int col, int val)
{
    return false;
}

bool Sodoku::checkMiniGrid(int startRow, int startCol, int val)
{
    return false;
}

bool Sodoku::checkRow(int row, int col, int val)
{
    return false;
}

bool Sodoku::checkCol(int row, int col, int val)
{
    return false;
}

bool Sodoku::findEmptyCell(int &row, int &col)
{
    return false;
}
