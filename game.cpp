#include <iostream>
#include <limits>

using namespace std;

static const int y = 7; // #rows
static const int x = 7; // #columns
static int board[y][x];
static int reference[x];
static int available = y;

void initialize_board() {
    for (int i = 0; i < x; i++) {
        reference[i] = i;
    }
    for (int i = 1; i < y; i++) {
        for (int j = 0; j < x; j++) {
            board[i][j] = 0;
        }
    }
    for (int j = 0; j < x; j++) {
        board[0][j] = y - 1;
    }
}

void draw_board() {
    cout << "\033[2J\033[1;1H"; // Clears terminal on Linux & Windows
    for (int i = 0; i < x; i++) {
        cout << reference[i] + 1 << " "; // Prints column numbers above top row
    }
    cout << "\n";
    for (int i = 1; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int get_user_selection(int user) {
    int selection;
    cout << "\nPlayer " << user << "'s turn!\nPlease enter the column number you wish to play: ";
    if(!(cin >> selection)) { // Checks if input is int
        draw_board();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPlease enter a valid number!\n";
        selection = get_user_selection(user);
    }
    if(selection > x || selection < 1) { // Checks if input is valid column
        draw_board();
        cout << "\nPlease enter a valid number!\n";
        selection = get_user_selection(user);
    }
    return selection;
}

void place_move(int selection, int user) {
    selection--; // Corrects for zero-based index
    if(board[0][selection] != -1) {
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
        cout << "\nColumn is full! Please select a different column!" << endl;
        place_move(get_user_selection(user), user);
    }
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
        if(turn == 1)
            turn = 2;
        else
            turn = 1;
    }
}