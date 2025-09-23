#include <iostream>
#include <vector>

using namespace std;

enum Difficulty{
    Easy,
    medium,
    hard
};
class Board{// --Abdelrahman--
private:
    vector<vector<char>> grid;
    int size;
public:
    Board(int s=3){
        size=s;
        grid=vector<vector<char>>(s,vector<char>(s));
    }
    void display()const{

    }
    
    bool makeMove(int row,int col,char symbol){

    }

    bool isValidMove(int row,int col)const{

    }
    bool checkWin(char symbol)const{

    }
    bool isFull()const{

    }
    char getCell(int row,int col)const{

    }
    void reset(){

    }
    int getSize()const{

    }
};

class Player {//--Habiba--
public:
    Player(const string& name,char symbol){

    }

    virtual void getMove(int& row,int& col)=0;

    
    string getName()const{

    }
    char getSymbol()const{

    }

    void setName(const string& name){

    }

};
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getMove(int& row, int& col) override {
        cout << getName() << " turn (" << getSymbol() << "). Enter row and column (0-2): ";
        cin >> row >> col;
    }
};

class AiPlayer:public Player{// --Marwan--
public:
    AiPlayer(const string& name , char symbol ,Difficulty diffiuclty){

    }

    void getMove(int& row,int& col)override{

    }
    void setDifficulty(Difficulty newDifficulty){

    }
    void getRandomMove(const Board& board,int&row,int&col){

    }
    void getBestMove( Board& board ,int& row,int& col)const{

    }
    int evaluateBoard(const Board& board)const{

    }
};


class Game {//-- Ziad & Jana --
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool gameOver;
    char winner;

public:
    Game(){
        board = Board(3);
        player1 = player2 = currentPlayer = nullptr;
        gameOver = false;
        winner = ' ';
    }

    void start() {
        while (true) {
            showMenu();

            if (player1 && player2) {
                gameOver = false;
                winner = ' ';
                board.reset();
                currentPlayer = player1;

                while (!gameOver) {
                    board.display();

                    int row, col;
                    currentPlayer->getMove(row, col);

                    while (!board.makeMove(row, col, currentPlayer->getSymbol())) {
                        cout << "Invalid move, try again ";
                        currentPlayer->getMove(row, col);
                    }

                    if (checkgameEnd()) {
                        board.display();
                        displayResult();
                        break;
                    }

                    switchPlayer();
                }
                delete player1;
                delete player2;
                player1 = player2 = currentPlayer = nullptr;
            }
        }
    }

    void showMenu(){
        int choice;

        cout << "======================" << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs Computer (Easy)" << endl;
        cout << "3. Player vs Computer (Hard)" << endl;
        cout << "4. Exit" << endl;
        cout << "Select game mode (1-4): ";
        cin >> choice;

        if (choice == 1) {
            setupPvP();
        } else if (choice == 2) {
            setupPvC(Easy);
        } else if (choice == 3) {
            setupPvC(hard);
        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
            exit(0);
        } else {
            cout << "Invalid choice! Please try again." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }


    void setupPvP(){
        string name1, name2;
        cout << "Player 1 name (x): ";
        cin >> name1;
        cout << "Player 2 name (o): ";
        cin >> name2;

        player1 = new HumanPlayer(name1, 'X');
        player2 = new HumanPlayer(name2, 'O');
        currentPlayer = player1;
    }

    void setupPvC(Difficulty difficulty){
        string name;
        cout << "Your name: ";
        cin >> name;

        player1 = new HumanPlayer(name, 'X');
        player2 = new AiPlayer("Computer", 'O', difficulty);
        currentPlayer = player1;
    }
    void switchPlayer(){
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    void handleHumanMove(HumanPlayer player){

    }
    void handleAiMove(AiPlayer aiplayer){

    }
    bool checkgameEnd(){

    }
    void displayResult()const{

    }
    void reset(){

    }
};



int main() {



    return 0;
}