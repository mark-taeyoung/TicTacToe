#include <iostream>
#include <vector>

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


int main(int argc, const char* argv[]) {

    char board[ROW][COL] = {' '};
    int count = 0;
    char input = ' ';


    while(1) {
        while(1) {
            std::cout << "Enter your move: ";
            std::cin >> input;
            if (checkInput(input, board)) {
                break;
            }
        }
        int move = input - '0' - 1;
        
        int i = (ROW - 1) + move / COL;
        int j = 
        if (board[move / COL])



    }

    return 0;
}