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
    // Zwalnianie pamieci
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
    	// Nieprawidlowa notacja ruchu check
        if (move.length() < 5 or move.length() > 7) {
            return;
        }
        // poczatkowe i koncowe wspolrzedne
        int fromRow = 8 - (move[1] - '0');
        int fromCol = move[0] - 'a';
        int toRow = 8 - (move[4] - '0');
        int toCol = move[3] - 'a';
        // Sprawdzenie, czy wspolrzednie są poprawne
        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return;  // Nieprawidlowe współrzędne
        }
        // czy jest figura na poczatku
        if (board[fromRow][fromCol] == nullptr) {
            return;  // Brak figury do przesuniecia
        }
        if (dynamic_cast<Bishop*>(board[fromRow][fromCol])) {
            if (!isValidBishopMove(fromRow, fromCol, toRow, toCol)) {
                return;
            }
        } else if (dynamic_cast<Rook*>(board[fromRow][fromCol])) {
            if (!isValidRookMove(fromRow, fromCol, toRow, toCol)) {
                return;
            }
        }
        //wait nie dziala bicie
        if(board[toRow][toCol] == nullptr){
        	std::swap(board[fromRow][fromCol], board[toRow][toCol]);
		}else{
			board[toRow][toCol] == nullptr;
			std::swap(board[fromRow][fromCol], board[toRow][toCol]);
		}
        
    }
private:
    ChessPiece* board[8][8] = { nullptr };
    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) const {
        if (abs(toRow - fromRow) != abs(toCol - fromCol)) {
            return false;
        }
        int rowDir = (toRow > fromRow) ? 1 : -1;
        int colDir = (toCol > fromCol) ? 1 : -1;    
        for (int i = 1; i < abs(toRow - fromRow); ++i) {
            if (board[fromRow + i * rowDir][fromCol + i * colDir] != nullptr) {
                return false;
            }
        }
        return true;
    }
    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol) const {
        if (fromRow != toRow && fromCol != toCol) {
            return false;
        }

        if (fromRow == toRow) {
            int colDir = (toCol > fromCol) ? 1 : -1;
            for (int i = 1; i < abs(toCol - fromCol); ++i) {
                if (board[fromRow][fromCol + i * colDir] != nullptr) {
                    return false;
                }
            }
        } else {
            int rowDir = (toRow > fromRow) ? 1 : -1;
            for (int i = 1; i < abs(toRow - fromRow); ++i) {
                if (board[fromRow + i * rowDir][fromCol] != nullptr) {
                    return false;
                }
            }
        }
        return true;
    }
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
        chessboard.makeMove(move);
    }
    return 0;
}
