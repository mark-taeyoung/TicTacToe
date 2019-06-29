#include <iostream>
#include <random>
#include <unordered_set>
#include <limits>

#define COL 3
#define ROW 3

struct Player{

    bool isComputer;
    char marker;

    Player(bool isComputer1, char marker1) {
        isComputer = isComputer1;
        marker = marker1;
    }

};

struct BoardIndex{
    size_t row, col;

    BoardIndex(int i) {
        row = abs((i - 1) / COL - ROW) - 1;
        col = (i - 1) % COL;
    }
};

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

    for (size_t i = 0; i < ROW; ++i) { 
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) 
            return true; 
    } 

    return false; 
} 

bool columnCrossed(const char board[ROW][COL]) {

    for (size_t i = 0; i < COL; ++i) { 
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

int minimax(char board[ROW][COL], std::unordered_set<size_t>& available_slots, bool player_turn, char marker, int depth) {

    /* assuming maximizer is computer; make computer win */
    if (checkWinner(board)) {
        if (!player_turn)
            return 10 - depth;
        else
            return -10 + depth;
    }

    if (available_slots.size() == 0) {
        // std::cout << "pass\n";
        return 0;
    }

    player_turn = !player_turn;

    std::unordered_set<size_t> temp = available_slots;

    if (!player_turn){
        int best = std::numeric_limits<int>::min();
        for (auto& target : available_slots) {
            BoardIndex x(target);

            board[x.row][x.col] = marker;   //mark
            temp.erase(target);

            char next_marker = marker == 'O' ? 'X' : 'O';
            best = std::max(best, minimax(board, temp, player_turn, next_marker, depth + 1));

            board[x.row][x.col] = 0;        // undo
            temp.insert(target);
        }
        return best;

    } else {
        int best = std::numeric_limits<int>::max();
        for (auto& target : available_slots) {
            BoardIndex x(target);

            board[x.row][x.col] = marker;   //mark
            temp.erase(target);

            char next_marker = marker == 'O' ? 'X' : 'O';
            best = std::min(best, minimax(board, temp, player_turn, next_marker, depth + 1));

            board[x.row][x.col] = 0;        // undo
            temp.insert(target);
        }
        return best;
    }
}


/* get optimal next choice with minimax algorithm */
size_t getOptimalNext (char board[ROW][COL], std::unordered_set<size_t>& available_slots, char marker) {
    int best_val = std::numeric_limits<int>::min();
    size_t optimal = 0;
    
    std::unordered_set<size_t> temp = available_slots;
    for (auto& target : available_slots) {
            BoardIndex x(target);

            board[x.row][x.col] = marker;   //mark
            temp.erase(target);
        
            char next_marker = marker == 'O' ? 'X' : 'O';
            int curr = minimax(board, temp, false, next_marker, 0);
            

            board[x.row][x.col] = 0;        // undo
            temp.insert(target);

            if (curr > best_val) {
                optimal = target;
                best_val = curr;
            }
    }
    
    return optimal;
}

/***********
board number
7 8 9
4 5 6
1 2 3
 ***********/

int main(int argc, const char* argv[]) {
    assert(COL == ROW);

    char board[ROW][COL];

    std::unordered_set<size_t> available_slots;
    for (size_t  i = 1; i <= ROW * COL; ++i) {
        available_slots.insert(i);
    }
    
    char yours;
    std::cout << "Choose O or X: ";
    std::cin >> yours;


    Player* you =  new Player(false, yours);
    Player* computer = nullptr;
    Player* curr = nullptr;
    if (yours == 'O') {
        computer =  new Player(true, 'X');
        curr = you;
        std::cout << "pass\n";
    } else {
        computer =  new Player(true, 'O');
        curr = computer;
    }

    showBoard(board);


    while(available_slots.size() > 0) {

        size_t target;

        if (!curr->isComputer) {
            char input;
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
        } else {
            // if computer is first turn, get random target
            if (available_slots.size() == ROW * COL) {
                target = randNumGenerator(1, ROW * COL);
            } else {
                target = getOptimalNext(board, available_slots, curr->marker);
            }
        }
        

        /* Calculate target index and Cross it out */
        BoardIndex x(target);

        board[x.row][x.col] = curr->marker;

        available_slots.erase(target);
        
        showBoard(board);

        if (checkWinner(board)) {
            if (!curr->isComputer) {
                std::cout << "PLAYER WIN!\n";
            } else {
                std::cout << "COMPUTER WIN!\n";
            }
            std::exit(EXIT_SUCCESS);
        }

        curr = !curr->isComputer ? computer : you;
    }

    std::cout << "GAME OVER\n";
    std::exit(EXIT_SUCCESS);
}