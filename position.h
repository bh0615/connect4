#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <string>

class Position {
    public:
        static const int HEIGHT = 6;
        static const int WIDTH = 7;
        bool can_play(int col) {
            return height[col] < HEIGHT;
        }
        void place(int col) {
            board[height[col]][col] = 1 + moves%2;
            height[col]++;
            moves++;
        }
        void draw_board() {
            // std::cout << "\033[2J\033[1;1H"; // Clears terminal on Linux & Windows
            for (int i = 0; i < WIDTH; i++) {
                std::cout << reference[i] + 1 << " "; // Prints column numbers above top row
            }
            std::cout << "\n";
            for (int i = 0; i < HEIGHT; i++) {
                if(WIDTH > 9) {
                    for (int j = 0; j < 9; j++) {
                        std::cout << board[i][j] << " ";
                    }
                    for (int j = 9; j < WIDTH; j++) {
                        std::cout << board[i][j] << "  ";
                    }
                    std::cout << std::endl;
                }
                else {
                    for (int j = 0; j < WIDTH; j++) {
                        std::cout << board[i][j] << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
        unsigned int place(std::string seq) {
        for(unsigned int i = 0; i < seq.size(); i++) {
          int col = seq[i] - '1'; 
          if(col < 0 || col >= Position::WIDTH || !can_play(col) || check(col)) return i; // invalid move
          place(col);
        }
        return seq.size();
      }
        bool check(int col) {
            // Check horizontal
            int row = height[col];
            count = 0;
            count = check_right(turn, row, col+1);
            count = check_left(turn, row, col-1);
            if(count == 3) return 1;

            // Check upper-right and lower-left diagonal
            count = 0;
            count = check_upper_right(turn, row-1, col+1);
            count = check_lower_left(turn, row+1, col-1);
            if(count == 3) return 1;

            // Check upper-left and lower-right diagonal
            count = 0;
            count = check_upper_left(turn, row-1, col-1);
            count = check_lower_right(turn, row+1, col+1);
            if(count == 3) return 1;

            // Check vertical
            if(row + 3 <= HEIGHT-1 && board[row+1][col] == turn && board[row+2][col] == turn && board[row+3][col] == turn) {
                return 1;
            }
            return 0;
        }
        Position() : board{0}, height{0}, moves{0} {}
    private:
        int board[HEIGHT][WIDTH];
        int height[WIDTH];
        int reference[WIDTH];
        unsigned int moves;
        int turn = 1 + moves%2;
        int count = 0;
        int check_right(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_right(turn, row, col+1);
        }
        int check_left(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_left(turn, row, col-1);
        }
        int check_upper_right(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_upper_right(turn, row-1, col+1);
        }
        int check_lower_left(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_lower_left(turn, row+1, col-1);
        }
        int check_upper_left(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_upper_left(turn, row-1, col-1);
        }
        int check_lower_right(int turn, int row, int col) {
            if(board[row][col] != turn) return count;
            else count++; return check_lower_right(turn, row+1, col+1);
        }
};






#endif