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

class Sodoku
{
public:
    explicit Sodoku(const int gridSize = 9, const int miniGridSize = 3);
    bool load(const char *inFile);
    void print();
    bool solve();
    
private:
    bool noConflict(int row, int col, int val);
    bool checkMiniGrid(int startRow, int startCol, int val);
    bool checkRow(int row, int col, int val);
    bool checkCol(int row, int col, int val);
    bool findEmptyCell(int &row, int &col);
    
private:
    const int m_MiniGridSize;
    const int m_GridSize;
    std::vector<std::vector<char>> m_Grid;

    
};

#endif /* sodoku_hpp */
