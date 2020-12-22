//
//  sodoku.hpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//

#ifndef sodoku_hpp
#define sodoku_hpp

#include <string>
#include <vector>
#include <iostream>

class Sodoku
{
public:
    explicit Sodoku(const int gridSize = 9, const int miniGridSize = 3);
    bool load(const char *inFile);
    bool solve();
    friend std::ostream& operator << (std::ostream& os, const Sodoku &s);
    
private:
    bool noConflict(int row, int col, char val);
    bool checkMiniGrid(int startRow, int startCol, char val);
    bool checkRow(int row, char val);
    bool checkCol(int col, char val);
    bool isEmptyCell(int &row, int &col);
    
private:
    const int m_MiniGridSize;
    const int m_GridSize;
    std::vector<std::vector<char>> m_Grid;
};

#endif /* sodoku_hpp */
