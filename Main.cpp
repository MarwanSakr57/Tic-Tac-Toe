#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Difficulty{ 

    Easy,
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
        if(isValidMove(row,col)){
        grid[row][col]=symbol;
        return true;
        }
        return false;
    }

    bool isValidMove(int row, int col)const {
         return (grid[row][col]!=' ');

    }
    bool checkWin(char symbol)const {
         // Check if the given symbol has won the game

    }
    bool isFull()const {
        for(int i =0;i<size;i++){
            for(int j=0;j<size;j++){
                if(grid[i][j]==' ') return false;
            }
        }
        return true;
    }
    char getCell(int row,int col)const {
            return grid[row][col];

    }
    void reset(){ 
        grid.clear()
    }
    int getSize()const{
        return size;
    }
};

class Player {      //--Habiba--
protected:
    string name;  // Player's name
    char symbol;  // Player's symbol (e.g., 'X' or 'O')
public:
    Player(const string& name,char symbol){
        this->name = name;            // Initialize the player's name
        this->symbol = symbol;       // Initialize the player's symbol

    }

    virtual void getMove(Board& board,int& row,int& col)=0;   
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

    void getMove(Board& board,int& row, int& col) override {
        cout << getName() << " turn (" << getSymbol() << "). Enter row and column (0-2): ";
        cin >> row >> col;
    }
};

class AiPlayer : public Player { // --Marwan--
private:
    Difficulty difficulty; // AI difficulty level

    int evaluateBoard(const Board& board) const {
    // check rows
        for (int i = 0; i < board.getSize(); i++) {
            if (board.getCell(i,0) != ' ' &&
                board.getCell(i,0) == board.getCell(i,1) &&
                board.getCell(i,1) == board.getCell(i,2))
                return (board.getCell(i,0) == symbol) ? 10 : -10;
        }
    // check columns
        for (int j = 0; j < board.getSize(); j++) {
            if (board.getCell(0,j) != ' ' &&
                board.getCell(0,j) == board.getCell(1,j) &&
                board.getCell(1,j) == board.getCell(2,j))
                return (board.getCell(0,j) == symbol) ? 10 : -10;
        }
    // check diagonals
        if (board.getCell(0,0) != ' ' &&
            board.getCell(0,0) == board.getCell(1,1) &&
            board.getCell(1,1) == board.getCell(2,2))
            return (board.getCell(0,0) == symbol) ? 10 : -10;

        if (board.getCell(0,2) != ' ' &&
            board.getCell(0,2) == board.getCell(1,1) &&
            board.getCell(1,1) == board.getCell(2,0))
            return (board.getCell(0,2) == symbol) ? 10 : -10;

    return 0; // no winner
    }

    int minimax(Board& board, int depth, bool isMaximizing) const {
        int score = evaluateBoard(board);

        if(score==10) return score-depth;
        if(score==-10) return score+depth;

        if(board.isFull()) return 0;

        if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i,j) == ' ') {
                    board.makeMove(i,j,symbol);          //try a move
                    best = max(best, minimax(board, depth + 1, false)); //recurse while switching to minimizing
                    board.makeMove(i,j,' ');             // undo (backtracking)
                }
            }
        }   return best;
        }else{
            int best = INT_MAX;
            char opp = (symbol == 'X') ? 'O' : 'X';
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i,j) == ' ') {
                    board.makeMove(i,j,opp);             //try a move
                    best =min(best, minimax(board, depth + 1, true)); //recurse while switching to maximizing
                    board.makeMove(i,j,' ');             // undo (backtracking)
                }
            }
        }  return best;
        }
      
    }
public:
 // Constructor to initialize AI player with name, symbol, and difficulty

    AiPlayer(const string& name , char symbol ,Difficulty diffiuclty) : Player(name,symbol){ 
        this->name=name;
        this->symbol=symbol;
        this->difficulty = diffiuclty;
    }

    void getMove(Board& board,int& row,int& col) override{ 
         // Override to get AI's move based on difficulty
         if(difficulty==Easy) return getRandomMove(board,row,col);
         return getBestMove(board,row,col);

    }
    void setDifficulty(Difficulty newDifficulty){  
        // Setter for AI difficulty
        difficulty = newDifficulty;

    }
    void getRandomMove(const Board& board,int&row,int&col){
          // Get a random valid move on the board
        vector<pair<int,int>> empty;
        for (int i=0;i<board.getSize();++i){
            for (int j=0;j<board.getSize();++j){
            if (board.getCell(i,j)==' ')
                empty.push_back({i,j});
            }
        }
        if (!empty.empty()) {
            int idx = rand() % empty.size();
            row = empty[idx].first;
            col = empty[idx].second;
        }

    }
    void getBestMove(Board& board, int& row, int& col) const {
        int bestVal = INT_MIN;
        row = col = -1;

        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i,j) == ' ') {
                    board.makeMove(i,j,symbol);                  //try a move
                    int moveVal = minimax(board, 0, false);     //recurse with opponent turn
                    board.makeMove(i,j,' ');                     // undo
                    if (moveVal > bestVal) {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
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
                    currentPlayer->getMove(board,row, col);

                    while (!board.makeMove(row, col, currentPlayer->getSymbol())) {
                        cout << "Invalid move, try again ";
                        currentPlayer->getMove(board,row, col);
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

        // for (int i = 0; i < 3; i++) {
        //     for (int j = 0; j < 3; j++) {
        //         if (board[i][j] == ' ') {
        //             board[i][j] = aiSymbol;
        //             cout << "AI plays at (" << i << ", " << j << ")\n";
        //             return;
        //         }
        //     }
        // }
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
        board.reset();
        winner = ' ';
    }
};


      
int main() {
// Main function to start the game
srand((unsigned)time(nullptr));

    return 0;
}