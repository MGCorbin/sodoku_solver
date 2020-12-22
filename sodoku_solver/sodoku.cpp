//
//  sodoku.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#include <iostream>
#include <fstream>

#include "sodoku.hpp"
#include "conversion.hpp"


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
                m_Grid[row][col] = val;             // add the value at the row and column to the grid
            }
        }
        
        inStream.close();
        return true;
    }
    return false;
}


bool Sodoku::solve()
{
    int row, col;
    
    if(!isEmptyCell(row, col))                          // if we cant find an empty cell, we must have completed the sodoku
    {
        return true;
    }
    
    for(int i=1; i<=m_GridSize; i++)                    // start from 1 as these are the numbers we try in each space with an X
    {
        if(noConflict(row, col, hex_to_ascii(i)))       // if we can add that number without breaking the rules of sodoku, try it
        {
            m_Grid[row][col] = hex_to_ascii(i);
            if(solve())                                 // recursively solve the sodoku
            {
                return true;
            }
            m_Grid[row][col] = 'X';
        }
    }
    return false;
}

std::ostream& operator << (std::ostream& os, const Sodoku &s)
{
    std::string divider = " ------ ------ ------ ";
    
    
    for(int row=0; row<s.m_GridSize; row++)
    {
        if(!(row % s.m_MiniGridSize))
        {
            os << divider << std::endl;
        }
        
        for(int col=0; col<s.m_GridSize; col++)
        {
            if(!(col % s.m_MiniGridSize))
            {
                os << "|";
            }
            os << s.m_Grid[row][col] << " ";
        }
        os << "|" << std::endl;
    }
    os << divider << std::endl << std::endl;
    
    return os;
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

bool Sodoku::isEmptyCell(int &row, int &col)
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
    

