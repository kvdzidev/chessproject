#include <iostream>
#include <ncursesw/curses.h>
#include <string>
#include <algorithm>
using namespace std;
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
        board[0][4] = new Kingb();
        board[0][3] = new Queenb();
        board[0][2] = new Bishopb();
        board[0][5] = new Bishopb();
        board[0][6] = new Knightb();
        board[0][1] = new Knightb();
        board[0][0] = new Rookb();
        board[0][7] = new Rookb();
        for (int w = 0; w < 8; w++)
            board[1][w] = new Pawnb();
        // poczatkowe black
        board[7][4] = new King();
        board[7][3] = new Queen();
        board[7][2] = new Bishop();
        board[7][5] = new Bishop();
        board[7][6] = new Knight();
        board[7][1] = new Knight();
        board[7][0] = new Rook();
        board[7][7] = new Rook();
        for (int n = 0; n < 8; n++)
            board[6][n] = new Pawn();
    	//nc init
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
             mvprintw(i + 1, 17, "| %d", 8 - i);
        }
        //opisanie pol etc.
        mvprintw(10, 1, " a b c d e f g h");
        mvprintw(9, 1, "-----------------");

        refresh();
    }
//poruszanie sie pionkow, aktualnie potrafia poruszac sie z danego miejsca do miejsca, 
//natomiast nie rozpoznaje figur, nie ma bicia, i nie interesuje go to czy bialy czy czarny
    void makeMove(const std::string& move) {
    	// Nieprawidłowa notacja ruchu
        if (move.length() < 5 or move.length() > 7) {
            return;
        }
        // Pobieranie współrzędnych początkowych i końcowych
        int fromRow = 8 - (move[1] - '0');
        int fromCol = move[0] - 'a';
        int toRow = 8 - (move[4] - '0');
        int toCol = move[3] - 'a';
        // Sprawdzenie, czy współrzędne są poprawne
        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return;  // Nieprawidłowe współrzędne
        }
        // Sprawdzenie, czy istnieje figura na pozycji początkowej
        if (board[fromRow][fromCol] == nullptr) {
            return;  // Brak figury do przesunięcia
        }
        // Wykonanie ruchu - zamiana miejscami pól
        std::swap(board[fromRow][fromCol], board[toRow][toCol]);
    }
private:
    ChessPiece* board[8][8] = { nullptr };
};
int main() {
    Chessboard chessboard;
    while (true) {
        chessboard.draw();
        char move[6];  // zapisywanie(store bardziej) ruchow (np. a2-a4)
        getstr(move);

        if (move[0] == 'q') {
            break;
        }
        // Wykonywanie ruchu.
        chessboard.makeMove(move);
    }
    return 0;
}
