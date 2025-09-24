#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

enum Difficulty{ 
    Easy,
    medium,
    hard
};

class Board{// --Abdelrahman--
private:
 // Board class to manage the game board
    vector<vector<char>> grid;
    int size;
public: // Constructor to initialize the board with a given size (default is 3x3)
    Board(int s = 3){
        size = s;
        grid = vector<vector<char>>(s,vector<char>(s,' '));
    }
    void display()const{
         // Display the current state of the board

    }
    
    bool makeMove(int row, int col, char symbol) { 
         // Place a symbol on the board at the specified position if valid

    }

    bool isValidMove(int row, int col)const {
         // Check if a move is valid (within bounds and on an empty cell)

    }
    bool checkWin(char symbol)const {
         // Check if the given symbol has won the game

    }
    bool isFull()const {
         // Check if the board is full (no empty cells)

    }
    char getCell(int row,int col)const {
         // Get the symbol at a specific cell

    }
    void reset(){ 
        // Reset the board to its intial empty state
    }
    int getSize()const{
         // Getter for board size
        

    }
};

class Player {      //--Habiba--
private:
    string name;  // Player's name
    char symbol;  // Player's symbol (e.g., 'X' or 'O')
public:
    Player(const string& name,char symbol){
        this->name = name;            // Initialize the player's name
        this->symbol = symbol;       // Initialize the player's symbol

    }

    virtual void getMove(int& row,int& col)=0;   
    // Pure virtual function to get the player's move
    string getName()const{                    
         // Getter for player's name
        return name;

    }

   
    char getSymbol()const{                   
         // Getter for player's symbol
        return symbol;

    }
    void setName(const string& newName){   
         // Setter for player's name
        name = newName;

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

class HumanPlayer : public Player {
    public:     
     // Constructor to initialize human player with name and symbol
    HumanPlayer(const string& name , char symbol) : Player(name, symbol){}
        // Call base class constructor
        
    void getMove(int& row,int& col) override{ 
         // Override to get human player's move from input
        row = -1;
        col = -1;
    }
  };

class AiPlayer : public Player { // --Marwan--
private:
    Difficulty difficulty; // AI difficulty level
public:
 // Constructor to initialize AI player with name, symbol, and difficulty

    AiPlayer(const string& name , char symbol ,Difficulty diffiuclty) : Player(name,symbol){ 
         // Call base class constructor
        this->difficulty = diffiuclty;

    }

    void getMove(int& row,int& col) override{ 
         // Override to get AI's move based on difficulty

    }
    void setDifficulty(Difficulty newDifficulty){  
        // Setter for AI difficulty
        difficulty = newDifficulty;

    }
    void getRandomMove(const Board& board,int&row,int&col){
          // Get a random valid move on the board

    }
    void getBestMove( Board& board ,int& row,int& col)const{ 
         // Get the best move using minimax algorithm

    }
    int evaluateBoard(const Board& board)const{
        // Evaluate the board state and return a score
        return 0;
    }
};


class Game {//-- Ziad & Jana --
private: 
 // Game class to manage the overall game flow
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool gameOver;
    char winner; 

public:
 // Constructor to initialize the game with default board size and null players
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
       // Setup Player vs AI mode
        string name;
        cout << "Your name: ";
        cin >> name;
        player1 = new HumanPlayer(name, 'X');
        player2 = new AiPlayer("Computer", 'O', difficulty);
        currentPlayer = player1;
    }

    void switchPlayer(){
      // Switch the current player
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    void handleHumanMove(HumanPlayer player){
        // Handle move input for human player


    }
    void handleAiMove(AiPlayer aiplayer){ 
         // Handle move for AI player

    }
    bool checkgameEnd(){ 
          // Check if the game has ended (win or draw)

    }
    void displayResult()const{ 
         // Display the result of the game (win or draw)

    }
    void reset(){ 
         // Reset the game state for a new game

    }
};



int main() {  
      // Main function to start the game



    return 0;
}