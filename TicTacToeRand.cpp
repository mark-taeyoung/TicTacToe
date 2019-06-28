#include <iostream>
#include <random>
#include <unordered_set>

#define COL 3
#define ROW 3

int randNumGenerator(const int& lo, const int& hi) {

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(lo, hi);

    return distribution(generator);
}

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

void showBoard(char board[ROW][COL]) {

    printf("\n\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0], board[2][1], board[2][2]); 
   
    return;
}

bool rowCrossed(const char board[ROW][COL]) { 

    for (int i=0; i<ROW; i++) { 
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) 
            return true; 
    } 

    return false; 
} 

bool columnCrossed(const char board[ROW][COL]) {

    for (int i=0; i<COL; i++) { 
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&  board[0][i] != 0) 
            return true; 
    } 

    return false ; 
} 
  
bool diagonalCrossed(const char board[ROW][COL]) { 

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) 
        return true; 
          
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) 
        return true; 
  
    return false; 
} 

bool checkWinner(const char board[ROW][COL]) {

    return diagonalCrossed(board) || columnCrossed(board) || rowCrossed(board);

}

/*
board 
7 8 9
4 5 6
1 2 3
 */

int main(int argc, const char* argv[]) {

    char board[ROW][COL];
    char input = 0;

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

        char marker;
        size_t target;

        if (player_turn) {
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
            marker = player;
        } else {
            marker = computer;
            auto random_it = std::next(available_slots.begin(), randNumGenerator(0, available_slots.size() - 1));
            target = *random_it;
        }
        
        // std::cout << "target : " << target << '\n';

        /* Calculate target index and Cross it out */
        int idx = target - 1;
        int i = abs(idx / COL - ROW) - 1;
        int j = idx % COL;
        board[i][j] = marker;

        available_slots.erase(target);
        
        showBoard(board);

        if (checkWinner(board)) {
            if (player_turn) {
                std::cout << "PLAYER WIN!\n";
            } else {
                std::cout << "COMPUTER WIN!\n";
            }
            std::exit(EXIT_SUCCESS);
        }
        // for (auto& x : available_slots)
        //     std::cout << x;
        // std::cout << '\n';

        player_turn = !player_turn;
    }

    std::cout << "GAME OVER\n";
    std::exit(EXIT_SUCCESS);
}