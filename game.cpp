#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

static const int y = 7; // #rows
static const int x = 7; // #columns
static int board[y][x];
static int reference[x];
static int allowed = y;

void initialize_board() {
    for (int i = 0; i < x; i++) {
        reference[i] = i;
    }
    for (int i = 1; i < y; i++) {
        for (int j = 0; j < x; j++) {
            board[i][j] = 0;
        }
    }
}

void draw_board() {
    printf("\033[2J\033[1;1H"); // Clears terminal on Linux & Windows
    for (int i = 0; i < x; i++) {
        cout << reference[i] + 1 << " ";
    }
    cout << "\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int get_user_selection(int user) {
    int selection;
    printf("\nPlayer %d's turn!\nPlease enter the column number you wish to play: " , user);
	scanf("%d" , &selection);
    if(selection > x || selection < 1) {
        draw_board();
        printf("\nPlease Enter a valid number!\n");
        selection = get_user_selection(user);
    }
    return selection;
}

int main() {
    initialize_board();
    int turn = 1, selection = 0, result = 0;
    while(true) {
        draw_board();
        if(allowed == 0) {
            result = 0;
            break;
        }
        if(turn == 1) {
         selection = get_user_selection(1);
        }
        else {
         selection = get_user_selection(2);
        }
        if(turn == 1)
            turn = 2;
        else
            turn = 1;
    }
}