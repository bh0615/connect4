#include <iostream>
#include <limits>
#include <vector>

static const int HEIGHT = 7; // #rows
static const int WIDTH = 7; // #columns
static int board[HEIGHT][WIDTH];
static int reference[WIDTH];
static int available = HEIGHT;
static int count;
static std::vector<int> moves;
static unsigned int num_moves;

void initialize_board() {
    for (int i = 0; i < WIDTH; i++) {
        reference[i] = i;
    }
    for (int i = 1; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = 0;
        }
    }
    for (int j = 0; j < WIDTH; j++) {
        board[0][j] = HEIGHT - 1;
    }
}

void draw_board() {
    std::cout << "\033[2J\033[1;1H"; // Clears terminal on Linux & Windows
    for (int i = 0; i < WIDTH; i++) {
        std::cout << reference[i] + 1 << " "; // Prints column numbers above top row
    }
    std::cout << "\n";
    for (int i = 1; i < HEIGHT; i++) {
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

int get_user_selection(int user) {
    int selection;
    std::cout << "\nPlayer " << user << "'s turn!\nPlease enter the column number you wish to play: ";
    if(!(std::cin >> selection)) { // Checks if input is int
        draw_board();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nPlease enter a valid number!\n";
        selection = get_user_selection(user);
    }
    if(selection > WIDTH || selection < 1) { // Checks if input is valid column
        draw_board();
        std::cout << "\nPlease enter a valid number!\n";
        selection = get_user_selection(user);
    }
    return selection;
}

bool can_play(int col) {
    return board[0][col] != -1;
}

void place_move(int selection, int user) {
    selection--; // Corrects for zero-based index
    if(can_play(selection)) {
        if(board[0][selection] > 1) {
            board[board[0][selection]][selection] = user;
            board[0][selection]--;
        }
        else {
            board[board[0][selection]][selection] = user;
            board[0][selection] = -1;
            available--;
        }
    }
    else {
        draw_board();
        std::cout << "\nColumn is full! Please select a different column!" << std::endl;
        place_move(get_user_selection(user), user);
    }
}

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

bool check(int turn, int row, int col) {
    // Check horizontal
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

void game_end(int result) {
    std::cout << "\nGame Over!";
    switch(result){
        case 1:
            std::cout << "\nPlayer 1 wins!\n";
            break;
        case 2:
            std::cout << "\nPlayer 2 wins!\n";
            break;
        default:
            std::cout << "\nIt's a draw!\n";
            break;
    }
}

void move_history() {
    for(int i : moves) {
        std::cout << i;
    }
    std::cout << "\n";
}

int main() {
    initialize_board();
    int turn = 1, selection = 0, result = 0;
    while(true) {
        draw_board();
        if(available == 0) {
            result = 0;
            break;
        }
        if(turn == 1) {
            selection = get_user_selection(1);
            place_move(selection, 1);
        }
        else {
            selection = get_user_selection(2);
            place_move(selection, 2);
        }
        moves.push_back(selection);
        num_moves++;
        if(check(turn, board[0][selection-1]+1, selection - 1)) {
            draw_board();
            result = turn;
            break;
        }
        if(turn == 1)
            turn = 2;
        else
            turn = 1;
    }
    game_end(result);
}