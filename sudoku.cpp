#include "sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}

Sudoku::Sudoku(std::string f_name) {
    // Generate a board from the give file
    std::ifstream input_file(f_name);
    std::string row_data;

    for (int row = 0; row < 9; row++) {
        // Get next line from file to convert to row in board
        std::getline(input_file, row_data);
        std::stringstream ss(row_data);
        for(int col = 0; col < 9; col++) {
            ss >> (this->board)[row][col];
        }
    }
}

bool Sudoku::solve(unsigned int row, unsigned int col) {
    // If all cells are filled, then return true
    if (row == 9) {
        return true;
    }

    // If cell is already filled, move on to next cell
    if ((this->board)[row][col] != 0) {
        if (col == 8) {
            return(this->solve(row + 1, 0));
        } else {
            return(this->solve(row, col + 1));
        }
    }

    // For each digit 1 - 9
    for (int num = 1; num < 10; num++) {

        // Check if digit can be placed
        if (this->is_valid(row, col, num)) {
            // Place the digit
            (this->board)[row][col] = num;

            // Recurse to next empty cell
                //If next cell returns true, return true
            if (col == 8) {
                if (this->solve(row + 1, 0)) {
                    return true;
                }
            } else {
                if (this->solve(row, col + 1)) {
                    return true;
                }
            }

            (this->board)[row][col] = 0;
        }

        // Otherwise, check nect digit
    
    }
    // If no digits yield valid solution, backtrack
    return false;
}

// If this is an empty space & the given number does not exist in the same
// row, column, or box then it will return true.
bool Sudoku::is_valid(unsigned int row, unsigned int col, int num){
    return (this->board)[row][col] == 0
            && !check_row(row, num)
            && !check_col(col, num)
            && !check_box(row - row % 3, col - col % 3, num);
}

// Return true if num exists within row
bool Sudoku::check_row(unsigned int row, unsigned int num){
    // Traverse the row, checking each element for num, and returning true if found
    for (int col = 0; col < 9; col++) {
        if ((this->board)[row][col] == num) {
            return true;
        }
    }
    return false;
}

// Return true if num exists within col
bool Sudoku::check_col(unsigned int col, unsigned int num){
    // Traverse the col, checking each element for num, and returning true if found
    for (int row = 0; row < 9; row++) {
        if ((this->board)[row][col] == num) {
            return true;
        }
    }
    return false;
}

// Return true if num exists within the box to be checked
bool Sudoku::check_box(unsigned int boxStartRow, unsigned int boxStartCol, unsigned int num){
    // Traverse the box, starting at [boxStartRow][boxStartCol], searching for num and returning true if found;
    for (int row = boxStartRow; row < boxStartRow + 3; row++) {
        for (int col = boxStartCol; col < boxStartCol + 3; col++) {
            if ((this->board)[row][col] == num) {
                return true;
            }
        }
    }
    return false;
}

void Sudoku::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            std::cout << (this->board)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    std::string f_name(argv[1]);

    Sudoku s(f_name);

    s.solve(0,0);

    s.display_board();

    return 0;
}
