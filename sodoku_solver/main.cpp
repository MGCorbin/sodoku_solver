//
//  main.cpp
//  sodoku_solver
//
//  Created by Marcus Corbin on 22/12/2020.
//


/*
 * main.cpp
 *
 *  Created on: 28 Jan 2020
 *      Author: marcus
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ARR_SIZE        9
#define MINI_GRID_SIZE    3

#define CLEAR_TERMINAL        "\033[2J"        //taken from: https://stackoverflow.com/questions/37774983/clearing-the-screen-by-printing-a-character/37778152
#define MOVE_CURSOR_TO_HOME    "\033[H"


/* LOCAL FUNCTIONS */
bool load_sudoku(char arr[ARR_SIZE][ARR_SIZE]);
void init_usr_sudoku(char arr[ARR_SIZE][ARR_SIZE]);
void usr_enter_sudoku(char arr[ARR_SIZE][ARR_SIZE]);
bool solve_sudoku(char arr[ARR_SIZE][ARR_SIZE]);
bool no_conflict(char arr[ARR_SIZE][ARR_SIZE], int row, int col, char val);
bool check_mini_grid(char arr[ARR_SIZE][ARR_SIZE], int grid_start_row, int grid_start_col, char val);
bool check_row(char arr[ARR_SIZE][ARR_SIZE], int row, int col, int val);
bool check_col(char arr[ARR_SIZE][ARR_SIZE], int row, int col, int val);
bool find_empty_location(char arr[ARR_SIZE][ARR_SIZE], int &row, int &col);
void display_board(char arr[ARR_SIZE][ARR_SIZE]);
char hex_to_ascii(uint8_t d);
/* --------------- */

int main(void)
{
    char soduku_arr[ARR_SIZE][ARR_SIZE];
    int selection;

    cout << "Enter '1' to load soduku from .txt file, enter '2' to load soduku from terminal:";
    cin >> selection;

    switch(selection)
    {
    case 1:
        if(!load_sudoku(soduku_arr))
            {
                cout << "Error - Unable to open Soduku" << endl;
            }
            else
            {
                display_board(soduku_arr);
                if(solve_sudoku(soduku_arr))
                {
                    display_board(soduku_arr);
                    cout << soduku_arr;
                }
                else
                {
                    cout << "Unable to Solve" << endl;
                }
            }
        break;
    case 2:
        init_usr_sudoku(soduku_arr);
        usr_enter_sudoku(soduku_arr);
        break;
    }


    return 0;
}

bool load_sudoku(char arr[ARR_SIZE][ARR_SIZE])
{
    fstream inputStream;
    char c;
    int row,col;

    inputStream.open("input.txt");

    if(inputStream.is_open())
    {
        for(row=0; row<ARR_SIZE; row++)
        {
            for(col=0; col<ARR_SIZE; col++)
            {
                inputStream >> c;
                if(c == 'X')
                    c = '_';
                arr[row][col] = c;
            }
        }
        inputStream.close();
        return true;
    }
    else
    {
        return false;
    }
}

void init_usr_sudoku(char arr[ARR_SIZE][ARR_SIZE])
{
    int row, col;

    for(row=0; row<ARR_SIZE; row++)
    {
        for(col=0; col<ARR_SIZE; col++)
        {
            arr[row][col] = 'X';
        }
    }

}

void usr_enter_sudoku(char arr[ARR_SIZE][ARR_SIZE])
{
    int row, col;
    char val;

    for(row=0; row<ARR_SIZE; row++)
    {
        for(col=0; col<ARR_SIZE; col++)
        {
            cout << "Row:" << row << " Col: " << col << " Value:";
            cin >> val;
            cout << CLEAR_TERMINAL;
            arr[row][col] = val;
            display_board(arr);
        }
    }
}

bool solve_sudoku(char arr[ARR_SIZE][ARR_SIZE])
{
    int row, col, i;

    if(!find_empty_location(arr, row, col))
        return true;

    for(i=1; i<=ARR_SIZE; i++)
    {
        if(no_conflict(arr, row, col, hex_to_ascii(i)))
        {
            arr[row][col] = hex_to_ascii(i);                //assign the value
            if(solve_sudoku(arr))
                return true;
            arr[row][col] = '_';            //if we could not solve it
        }
    }
    return false;                                //we backtrack

}

bool no_conflict(char arr[ARR_SIZE][ARR_SIZE], int row, int col, char val)    //returns 1 if there is conflict
{
    return !check_mini_grid(arr, row - (row%MINI_GRID_SIZE), col - (col%MINI_GRID_SIZE), val) && !check_row(arr, row, col, val)
            && !check_col(arr, row, col, val) && arr[row][col] == '_';

}

bool check_mini_grid(char arr[ARR_SIZE][ARR_SIZE], int grid_start_row, int grid_start_col, char val)
{
    int row, col;

    for(row=0; row<MINI_GRID_SIZE; row++)
    {
        for(col=0; col<MINI_GRID_SIZE; col++)
        {
            if(arr[row + grid_start_row][col + grid_start_col] == val)    //apply the grid offset
                return true;
        }
    }
    return false;    //if we don't find val in the grid return 0
}

bool check_row(char arr[ARR_SIZE][ARR_SIZE], int row, int col, int val)
{
    for(col=0; col<ARR_SIZE; col++)
    {
        if(arr[row][col] == val)
            return true;
    }
    return false;
}

bool check_col(char arr[ARR_SIZE][ARR_SIZE], int row, int col, int val)
{
    for(row=0; row<ARR_SIZE; row++)
    {
        if(arr[row][col] == val)
            return true;
    }
    return false;
}

bool find_empty_location(char arr[ARR_SIZE][ARR_SIZE], int &row, int &col)    //finds the nearest empty cell
{
    for(row = 0; row<ARR_SIZE; row++)
    {
        for(col=0; col<ARR_SIZE; col++)
        {
            if(arr[row][col] == '_')
            {
                return true;
            }

        }
    }
    return false;
}


void display_board(char arr[ARR_SIZE][ARR_SIZE])
{
    int row, col;
    string divider = " ------ ------ ------ ";


    for(row=0; row<ARR_SIZE; row++)
    {
        if(!(row % MINI_GRID_SIZE))
            cout << divider << endl;
        for(col=0; col<ARR_SIZE; col++)
        {
            if(!(col % MINI_GRID_SIZE))
                cout << "|";
            cout << arr[row][col] << " ";

        }
        cout << "|" << endl;
    }
    cout << divider << endl << endl;
}

char hex_to_ascii(uint8_t d)
{
    if(d < 10)
        d += '0';
    else
        d += ('A' - 10);
    return d;
}

