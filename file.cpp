#include <iostream>
#include <vector>

using namespace std;

enum Difficulty {
    Easy,
    medium,
    hard
};
class Board {// --Abdelrahman--
private:
    vector<vector<char>> grid;
    int size;
public:
    Board(int s = 3) {
        size = s;
        grid = vector<vector<char>>(s, vector<char>(s));
    }
    void display()const {

    }

    bool makeMove(int row, int col, char symbol) {

    }

    bool isValidMove(int row, int col)const {

    }
    bool checkWin(char symbol)const {

    }
    bool isFull()const {

    }
    char getCell(int row, int col)const {

    }
    void reset() {

    }
    int getSize()const {

    }
};

class Player {//--Habiba--
public:
    Player(const string& name, char symbol) {

    }

    virtual void getMove(int& row, int& col) = 0;


    string getName()const {

    }
    char getSymbol()const {

    }
    char getSymbol()const {

    }
    void setName(const string& name) {

    }

};

class AiPlayer :public Player {// --Marwan--
public:
    AiPlayer(const string& name, char symbol, Difficulty diffiuclty) {

    }

    void getMove(int& row, int& col)override {

    }
    void setDifficulty(Difficulty newDifficulty) {

    }
    void getRandomMove(const Board& board, int& row, int& col) {

    }
    void getBestMove(Board& board, int& row, int& col)const {

    }
    int evaluateBoard(const Board& board)const {

    }
};

class Game {//-- Ziad & Jana --\

	    private:
        vector<vector<char>> board;
        char winner;
    Game() {

    }

    void start() {

    }
    void showMenu() {

    }
    void setupPvP() {

    }
    void setupPvC(Difficulty difficulty) {

    }
    void switchPlayer() {

    }
    void handleHumanMove(Player player) {
        int row, col;
        while (true) {
            cout << "Enter row and column (0-2 0-2): ";
            cin >> row >> col;
            if (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                cout << "Invalid move. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                board[row][col] = player.getSymbol(); 
                break;
            }
        }
    }

    void handleAiMove() {
     
        char aiSymbol = 'O';

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = aiSymbol;
                    cout << "AI plays at (" << i << ", " << j << ")\n";
                    return;
                }
            }
        }
    }

    bool checkgameEnd() {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                winner = board[i][0];
                return true;
            }
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                winner = board[0][i];
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            winner = board[0][0];
            return true;
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            winner = board[0][2];
            return true;
        }

        // Check for draw
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false; 
            }
        }

        winner = 'D'; 
        return true;
    }

    void displayResult() const {
        if (winner == 'D') {
            cout << "It's a draw!\n";
        }
        else {
            cout << "Winner is: " << winner << "\n";
        }
    }

    void reset() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        winner = ' ';
    }
};



int main() {



    return 0;
}