#include <iostream>
#include <ncursesw/curses.h>
#include <string>
#include <algorithm>
//klasy figur
class ChessPiece {
public:
    virtual char getSymbol() const = 0;
};

class King : public ChessPiece {
public:
    char getSymbol() const override {
        return 'K';
    }
};

class Queen : public ChessPiece {
public:
    char getSymbol() const override {
        return 'Q';
    }
};

class Bishop : public ChessPiece {
public:
    char getSymbol() const override {
        return 'B';
    }
};
class Knight : public ChessPiece {
public:
    char getSymbol() const override {
        return 'N';
    }
};
class Rook : public ChessPiece {
public:
    char getSymbol() const override {
        return 'R';
    }
};
class Pawn : public ChessPiece {
public:
    char getSymbol() const override {
        return 'P';
    }
};
//klasy czarnych figur
class Kingb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'k';
    }
};
class Queenb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'q';
    }
};
class Bishopb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'b';
    }
};
class Knightb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'n';
    }
};
class Rookb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'r';
    }
};
class Pawnb : public ChessPiece {
public:
    char getSymbol() const override {
        return 'p';
    }
};
//szachownica - poczatkowe ustawienie figur
class Chessboard {
public:
    Chessboard() {
        // poczatkowe biale
        board[0][4] = new King();
        board[0][3] = new Queen();
        board[0][2] = new Bishop();
        board[0][5] = new Bishop();
        board[0][6] = new Knight();
        board[0][1] = new Knight();
        board[0][0] = new Rook();
        board[0][7] = new Rook();
        for(int w = 0; w < 8; w++)
        	board[1][w] = new Pawn();
        
        // poczatkowe black
        board[7][4] = new Kingb();
        board[7][3] = new Queenb();
        board[7][2] = new Bishopb();
        board[7][5] = new Bishopb();
        board[7][6] = new Knightb();
        board[7][1] = new Knightb();
        board[7][0] = new Rookb();
        board[7][7] = new Rookb();
        for(int n = 0; n < 8; n++)
        	board[6][n] = new Pawn();

        // Inicjalizacja ncurses
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
    }
// Zwalnianie pamięci
    ~Chessboard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
            }
        }
        endwin();
    }

    void draw() const {
        clear();

        // Rysowanie szachownicy
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                mvprintw(i + 1, j * 2 + 1, "|");
                if (board[i][j] != nullptr) {
                    mvprintw(i + 1, j * 2 + 2, "%c", board[i][j]->getSymbol());
                }
            }
            mvprintw(i + 1, 17, "| %d", i + 1);
        }
        //opisanie pol etc.
        mvprintw(0, 1, " a b c d e f g h");
        mvprintw(9, 1, "-------------------");

        refresh();
    }

private:
    ChessPiece* board[8][8] = {nullptr};
};

int main() {
    Chessboard chessboard;

    while (true) {
        chessboard.draw();

        int ch = getch();
        if (ch == 'q') {
            break;
        }
    }

    return 0;
}