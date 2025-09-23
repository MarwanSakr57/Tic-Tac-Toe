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
public: 
 // Constructor to initialize the game with default board size and null players
    Game(){

    }

    void start(){
         // Start the game loop

    }
    void showMenu(){
         // Display the main menu and get user choice

    }
    void setupPvP(){
         // Setup Player vs Player mode

    }
    void setupPvC(Difficulty difficulty){
         // Setup Player vs AI mode

    }
    void switchPlayer(){ 
         // Switch the current player

    }
    void handleHumanMove(Player player){
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