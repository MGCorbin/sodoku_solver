//
//  sodoku.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#include <iostream>
#include <fstream>

#include "sodoku.hpp"

char hex_to_ascii(uint8_t d)
{
    if(d < 10)
        d += '0';
    else
        d += ('A' - 10);
    return d;
}

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
    int row, col;
    
    if(!findEmptyCell(row, col))        // if we cant find an empty cell, we must have completed the sodoku
    {
        return true;
    }
    
    for(int i=1; i<=m_GridSize; i++)
    {
        if(noConflict(row, col, hex_to_ascii(i)))
        {
            m_Grid[row][col] = hex_to_ascii(i);
            if(solve())
            {
                return true;
            }
            m_Grid[row][col] = 'X';
        }
    }
    return false;
}

bool Sodoku::noConflict(int row, int col, char val)
{
    return  !checkMiniGrid(row - (row % m_MiniGridSize), col - (col % m_MiniGridSize), val) &&
            !checkRow(row, val) &&
            !checkCol(col, val) &&
            m_Grid[row][col] == 'X';
}

bool Sodoku::checkMiniGrid(int startRow, int startCol, char val)
{
    for(int row=0; row<m_MiniGridSize; row++)
    {
        for(int col=0; col<m_MiniGridSize; col++)
        {
            if(m_Grid[row + startRow][col + startCol] == val)       // offset depending on which mini grid we are working in
            {
                return true;
            }
        }
    }
    
    return false;
}

bool Sodoku::checkRow(int row, char val)
{
    for(int col=0; col<m_GridSize; col++)
    {
        if(m_Grid[row][col] == val)
        {
            return true;
        }
    }
    return false;
}

bool Sodoku::checkCol(int col, char val)
{
    for(int row=0; row<m_GridSize; row++)
    {
        if(m_Grid[row][col] == val)
        {
            return true;
        }
    }
    return false;
}

bool Sodoku::findEmptyCell(int &row, int &col)
{
    for(row=0; row<m_GridSize; row++)
    {
        for(col=0; col<m_GridSize; col++)
        {
            if(m_Grid[row][col] == 'X')
            {
                return true;
            }
        }
    }
    return false;
}
    

