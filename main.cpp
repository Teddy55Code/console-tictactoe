#include <iostream>
#include <string>

using namespace std;

namespace Field {
    enum FieldState {
        empty, player_x, player_o
    };
    static const char *FieldStrings[] = {" ", "X", "O"};
}

using namespace Field;

class Board {
    FieldState fields[3][3];

public:
    explicit operator string() const {
        string boardOut;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boardOut += "|";
                boardOut += FieldStrings[fields[i][j]];
            }
            boardOut += "|\n";
        }
        return boardOut;
    }

    bool setField(int x, int y, FieldState value) {
        if (fields[x][y] == FieldState::empty) {
            fields[x][y] = value;
            return true;
        }
        return false;
    }

    FieldState getField(int x, int y) {
        return fields[x][y];
    }

    FieldState checkWin() {
        FieldState winStates[] = {checkVerticalWin(), checkHorizontalWin(), checkDiagonalWin()};

        for (FieldState fieldState: winStates) {
            if (fieldState == FieldState::player_x) {
                return FieldState::player_x;
            } else if (fieldState == FieldState::player_o) {
                return FieldState::player_o;
            }
        }

        return FieldState::empty;
    }

    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fields[i][j] = FieldState::empty;
            }
        }
    }

private:
    FieldState checkVerticalWin() {
        for (int i = 0; i < 3; i++) {
            if (FieldState::player_x == fields[0][i] && fields[0][i] == fields[1][i] && fields[1][i] == fields[2][i]) {
                return FieldState::player_x;
            } else if (FieldState::player_o == fields[0][i] && fields[0][i] == fields[1][i] && fields[1][i] == fields[2][i]) {
                return FieldState::player_o;
            }
        }
        return FieldState::empty;
    }

    FieldState checkHorizontalWin() {
        for (int i = 0; i < 3; i++) {
            if (FieldState::player_x == fields[i][0] && fields[i][0] == fields[i][1] && fields[i][1] == fields[i][2]) {
                return FieldState::player_x;
            } else if (FieldState::player_o == fields[i][0] && fields[i][0] == fields[i][1] && fields[i][1] == fields[i][2]) {
                return FieldState::player_o;
            }
        }
        return FieldState::empty;
    }

    FieldState checkDiagonalWin() {
        if (FieldState::player_x == fields[0][0] && fields[0][0] == fields[1][1] && fields[1][1] == fields[2][2] ||
            FieldState::player_x == fields[2][0] && fields[2][0] == fields[1][1] && fields[1][1] == fields[0][2]) {
            return FieldState::player_x;
        } else if (FieldState::player_o == fields[0][0] && fields[0][0] == fields[1][1] && fields[1][1] == fields[2][2] ||
                   FieldState::player_x == fields[2][0] && fields[2][0] == fields[1][1] && fields[1][1] == fields[0][2]) {
            return FieldState::player_o;
        } else {
            return FieldState::empty;
        }
    }
};

int main() {
    Board board = *new Board;
    FieldState currentPlayer = FieldState::player_x;
    bool isGameOver = false;

    while (!isGameOver) {
        bool isValidInput = false;
        int y;
        int x;

        while (!isValidInput) {
            string currentPlayerString = FieldStrings[currentPlayer];
            cout << currentPlayerString + "'s turn\nenter column:";
            cin >> y ;
            y--;

            if (!(y <= 3 && y >= 0)){
                continue;
            }

            cout << "enter row:";
            cin >> x;
            x--;

            if (!(x <= 3 && x >= 0)){
                continue;
            }

            bool isEmpty = board.setField(x, y, currentPlayer);

            if (!isEmpty) {
                cout <<  "This field is not empty." << endl;
            }

            isValidInput = isEmpty;
        }



        if (currentPlayer == FieldState::player_x) {
            currentPlayer = FieldState::player_o;
        } else {
            currentPlayer = FieldState::player_x;
        }

        cout << "\n" + board.operator string() << endl;

        FieldState winner = board.checkWin();
        if (winner != FieldState::empty) {
            isGameOver = true;

            string output = FieldStrings[winner];
            cout <<  output + " wins" << endl;
        }
    }

    return 0;
}


