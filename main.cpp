#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>

using namespace std;

const int ROW = 30;
const int COL = 50;
const int CELL_SIZE = 30;
const int TEXT_SIZE = 80;
char X[] = "X";
char O[] = "O";
int board[ROW][COL];
const int EMPTY = 0;
const int PLAYER_X = 1;
const int PLAYER_O = 2;
const int WIN_LENGTH = 5;
int turn = 1;

class Board {
    public:
        // ve ban co
        void draw_board() {
        // ve nen ban co
        setfillstyle(SOLID_FILL, WHITE);
        bar(0, 0, COL * CELL_SIZE, ROW * CELL_SIZE);
        // ve cot 
        setlinestyle(SOLID_LINE, 1, 1);
        setcolor(BLACK);
        for (int i = 0; i < COL; i++) {
            for (int j = 0; j < ROW; j++) {
                rectangle(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            }
        }
        // ve hang
        for (int i = 0; i <= COL; i++) {
            line(i * CELL_SIZE, 0, i * CELL_SIZE, ROW * CELL_SIZE);
            line(0, i * CELL_SIZE, COL * CELL_SIZE, i * CELL_SIZE);
        // khoi tao cac o co trong 
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                board[i][j] = EMPTY;
                }
            }
        }
    }
};

class Player {
private:
    string name;
    int symbol;
public:
    Player(string _name, int _symbol) {
        name = _name;
        symbol = _symbol;
    }
    string getName() {
        return name;
    }
    int getSymbol() {
        return symbol;
    }

    void drawSymbol(int row, int col, char symbol) {
    // Tính toạ độ pixel của ô cờ tại vị trí (row, col)
    int x = col * CELL_SIZE - 25;
    int y = row * CELL_SIZE - 25;

    // Thiết lập màu vẽ và độ dày đường viền
    settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);

    // Vẽ ký hiệu của người chơi vào ô cờ
    if (turn % 2 == 1) {
        // Vẽ chữ X
        symbol = 1;
        setbkcolor(WHITE);
        setcolor(RED);
        outtextxy(x, y, X);
        setbkcolor(getbkcolor());
    } else if (turn % 2 == 0) {
        // Vẽ hình tròn
        symbol = 2;
        setcolor(BLUE);
        outtextxy(x, y, O);
        setbkcolor(getbkcolor());
    }
}

    void play(Player &player, int board[ROW][COL]) {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            int row = y / CELL_SIZE + 1;
            int col = x / CELL_SIZE + 1;
            if (board[row][col] == EMPTY) {
                board[row][col] = player.getSymbol();
                drawSymbol(row, col, player.getSymbol());
                turn++;
                break;
            }
        }
    }
}
};

class Check {
    public:
    bool checkWin(int board[][COL], int player) {
    // Kiểm tra hàng ngang
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW - WIN_LENGTH + 1; j++) {
            bool win = true;
            for (int k = 0; k < WIN_LENGTH; k++) {
                if (board[i][j+k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Kiểm tra cột dọc
    for (int i = 0; i < ROW - WIN_LENGTH + 1; i++) {
        for (int j = 0; j < COL; j++) {
            bool win = true;
            for (int k = 0; k < WIN_LENGTH; k++) {
                if (board[i+k][j] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo chính
    for (int i = 0; i < ROW - WIN_LENGTH + 1; i++) {
        for (int j = 0; j < COL - WIN_LENGTH + 1; j++) {
            bool win = true;
            for (int k = 0; k < WIN_LENGTH; k++) {
                if (board[i+k][j+k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo phụ
    for (int i = 0; i < ROW - WIN_LENGTH + 1; i++) {
        for (int j = WIN_LENGTH - 1; j < COL; j++) {
            bool win = true;
            for (int k = 0; k < WIN_LENGTH; k++) {
                if (board[i+k][j-k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }
    // Nếu không tìm thấy chiến thắng, trả về false
    return false;
}

    bool checkDraw() {
        for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
        if (board[row][col] == 0) {
        return false;
      }
    }
  }
  return true;
}

    void showWinner(int current_Player) {
        char GAME[] = "GAME WINNER";
        char Player1[] = "Player 1";
        char Player2[] = "Player 2";
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(GREEN);
        outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 30, GAME);
        if(current_Player == 1) {
            outtextxy(getmaxx() / 2 - 40, getmaxy() / 2 + 10, Player1);
        } 
        if (current_Player == 2) {
            outtextxy(getmaxx() / 2 - 40, getmaxy() / 2 + 10, Player2);
        }
    }
};

int main() {
    Board obj;
    Player p1("Player 1", PLAYER_X);
    Player p2("Player 2", PLAYER_O);
    Check check;
    int currentPlayer = PLAYER_X;
    bool gameOver = false;
    char GD[] = "GAME DRAW";

    initwindow(CELL_SIZE * COL, CELL_SIZE * ROW, "Caro Game");
    obj.draw_board();

    while(!gameOver) {
        p1.play(p1, board);
        if(check.checkWin(board, currentPlayer)) {
            check.showWinner(currentPlayer);
            gameOver = true;
            break;
    } else if(check.checkDraw()) {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(GREEN);
        outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 30, GD);
        gameOver = true;
        break;
    }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        p2.play(p2, board);
        if(check.checkWin(board, currentPlayer)) {
            check.showWinner(currentPlayer);
            gameOver = true;
            break;
    } else if(check.checkDraw()) {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        setcolor(GREEN);
        outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 30, GD);
        gameOver = true;
        break;
    }
}
    getch();

    closegraph();
    
    return 0;
}
