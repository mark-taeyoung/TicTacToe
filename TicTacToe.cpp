#include <iostream>
#include <random>
#include <unordered_set>

#define COL 3
#define ROW 3


bool checkInput (const char& input, const char board[ROW][COL]) {

    if (!isdigit(input)) {
        std::cout << "ERROR: input is NOT digit" << '\n';
        return false;
    }

    int temp = input - '0';

    if (temp < 1 || temp > COL*ROW) {
        std::cout << "ERROR: input is NOT range 1-9" << '\n';
        return false;
    }

    return true;
}


void moveTurn (char board[ROW][COL], const int& goTo, const char& marker) {

    int i = abs(goTo / COL - ROW) - 1;
    int j = goTo % COL;

    board[i][j] = marker;
}

void showBoard(char board[ROW][COL]) {

    printf("\n\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0], board[2][1], board[2][2]); 
   
    return;
}


int randNumGenerator(const int& lo, const int& hi) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(lo, hi);

    return distribution(generator);
}
/*
board 
7 8 9
4 5 6
1 2 3
 */

int main(int argc, const char* argv[]) {

    char board[ROW][COL];
    char input = ' ';

    char player;
    char computer;
    bool player_turn = true;

    std::unordered_set<size_t> available_slots;
    for (size_t  i = 1; i <= ROW * COL; ++i) {
        available_slots.insert(i);
    }

    std::cout << "Choose O or X: ";
    std::cin >> player;

    if (player == 'O') {
        computer = 'X';
    } else {
        computer = 'O';
        player_turn = false;
    }

    showBoard(board);
    while(available_slots.size() > 0) {

        char curr;
        size_t target;

        if(player_turn) {
            std::cout << "Enter your move: ";
            std::cin >> input;

            if (!checkInput(input, board)) {
                continue;
            }
            target = input - '0';
            if (available_slots.find(target) == available_slots.end()) {
                std::cout << "already filled\n";
                continue;
            }
            curr = player;
        } else {
            curr = computer;
            auto random_it = std::next(available_slots.begin(), randNumGenerator(0, available_slots.size() - 1));
            target = *random_it;
        }
        
        std::cout << "target : " << target << '\n';

        moveTurn(board, target - 1, curr);
        available_slots.erase(target);

        player_turn = !player_turn;
        
        showBoard(board);
        for (auto& x : available_slots)
            std::cout << x;
        std::cout << '\n';
    }

    std::cout << "GAME OVER\n";
    std::exit(EXIT_SUCCESS);
}