#include "sujiko.h"
#include <sstream>
#include <fstream>
#include <iostream>

Sujiko::Sujiko() {

}

Sujiko::Sujiko(std::string fname) {
    // Read 4 sum values from file
    // Read file & create board
    std::ifstream input_file(fname);
    std::string line;

    // Read first 4 numbers to populate nums
    std::getline(input_file, line);
    std::stringstream ss(line);
    for (int nums_row = 0; nums_row < BOARD_SIZE - 1; nums_row++) {
        for (int nums_col = 0; nums_col < BOARD_SIZE - 1; nums_col++) {
            ss >> nums[nums_row][nums_col];
        }
    }

    // Read Sujiko starting input and populate board
    for (int row = 0; row < BOARD_SIZE; row++) {
        // Get next line from file to convert to row in board
        std::getline(input_file, line);
        std::stringstream ss(line);
        for(int col = 0; col < BOARD_SIZE; col++) {
            ss >> (this->board)[row][col];
        }
    }
}

Sujiko::~Sujiko() {

}

bool Sujiko::solve(unsigned int row, unsigned int col){
    // Evaluate if the board has been solved
    if (row == this->BOARD_SIZE) {
        return this->evaluate();
    }

    // If cell is already filled, move on to next cell
    if ((this->board)[row][col] != this->EMPTY) {
        if (col == this->BOARD_SIZE - 1) {
            return(this->solve(row + 1, 0));
        } else {
            return(this->solve(row, col + 1));
        }
    }

    // Iterate for each missing value
    for (int num = 1; num <= this->BOARD_SIZE * this->BOARD_SIZE; num++) {
        if (this->is_valid(num)) {

            // For current cell, place first missing value
            // Place the digit
            (this->board)[row][col] = num;

            // Recurse to next empty cell
                //If next cell returns true, return true
            if (col == this->BOARD_SIZE - 1) {
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

    }
    // Return false if no value yields a solution
        // This implies a previous cell is incorrect and we must backtrack
    return false;
}

bool Sujiko::is_valid(int num) {
    for (int row = 0; row < this->BOARD_SIZE; row++) {
        for (int col = 0; col < this->BOARD_SIZE; col++) {
            if ((this->board)[row][col] == num) {
                return false;
            }
        }
    }
    return true;
}

bool Sujiko::evaluate() {
    unsigned int sum_upper_left;
    unsigned int sum_upper_right;
    unsigned int sum_lower_left;
    unsigned int sum_lower_right;
    bool is_valid_solution = false;

    sum_upper_left = this->board[0][0] + this->board[0][1]
                    + this->board[1][0] + this->board[1][1];

    sum_upper_right = this->board[0][1] + this->board[0][2]
                    + this->board[1][1] + this->board[1][2];

    sum_lower_left = this->board[1][0] + this->board[1][1]
                    + this->board[2][0] + this->board[2][1];

    sum_lower_right = this->board[1][1] + this->board[1][2]
                    + this->board[2][1] + this->board[2][2];
    if (sum_upper_left == this->nums[0][0] &&
        sum_upper_right == this->nums[0][1] &&
        sum_lower_left == this->nums[1][0] &&
        sum_lower_right == this->nums[1][1]) {

            is_valid_solution = true;
    }

    return is_valid_solution;
}

void Sujiko::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    Sujiko s(argv[1]);

    s.solve(0,0);

    s.display_board();

    return 0;
}
