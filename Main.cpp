#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Difficulty{ 

    Easy,
    Hard
};
class Board{// --Abdelrahman--
private:
 // Board class to manage the game board
    vector<vector<char>> grid;
    int size;
public: // Constructor to initialize the board with a given size (default is 3x3)
    Board(int s = 3)
        : size(s), grid(s,vector<char>(s, ' ')) 
    {}

    void display()const{
        // Display the current state of the board
        cout << "\n";
        cout<<"  "<< "1"<<"   "<<"2"<<"   "<<"3"<<endl;
        for (int i = 0; i < size; ++i) {
            cout<<(i+1);
            for (int j = 0; j < size; ++j) {
                cout << " " << grid[i][j];
                if (j < size - 1) cout << " |";
            }
            cout << "\n";
            if (i < size - 1) cout <<" "<<"---+---+---\n";
        }
        cout << "\n";

    }
    
    bool makeMove(int row, int col, char symbol) { 
        if(isValidMove(row,col)){
        grid[row][col]=symbol;
        return true;
        }
        return false;
    }

    void setCell(int row,int col,char symbol){      // direct setter that doesnt check for valid move(needed in backtracking)
    grid[row][col] = symbol;
    }


    bool isValidMove(int row, int col)const {
         return (row>=0 && row<size && col>=0 && col<size && grid[row][col]==' ');

    }
    bool checkWin(char symbol)const {
    // Check if the given symbol has won the game
    // check rows
    for (int i = 0; i < size; i++) {
        if (grid[i][0] != ' ' &&
            grid[i][0] == grid[i][1] &&
            grid[i][1] == grid[i][2] &&
            grid[i][0] == symbol)
            return true;
    }

    // check columns
    for (int j = 0; j < size; j++) {
        if (grid[0][j] != ' ' &&
            grid[0][j] == grid[1][j] &&
            grid[1][j] == grid[2][j] &&
            grid[0][j] == symbol)
            return true;
    }

    // check diagonals
    if (grid[0][0] != ' ' &&
        grid[0][0] == grid[1][1] &&
        grid[1][1] == grid[2][2] &&
        grid[0][0] == symbol)
        return true;

    if (grid[0][2] != ' ' &&
        grid[0][2] == grid[1][1] &&
        grid[1][1] == grid[2][0] &&
        grid[0][2] == symbol)
        return true;

    return false;  
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
        grid.assign(size,vector<char>(size, ' '));
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
        char opp = (symbol == 'X') ? 'O' : 'X';

        if(board.checkWin(symbol)) return 10;
        if(board.checkWin(opp)) return -10;

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
                    board.setCell(i,j,' ');             // undo (backtracking)
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
                    board.setCell(i,j,' ');             // undo (backtracking)
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
                    board.setCell(i,j,' ');                     // undo
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
    string winner; 

public:
 // Constructor to initialize the game with default board size and null players
    Game(){
        board = Board(3);
        player1 = player2 = currentPlayer = nullptr;
        winner = " ";
    }

     void start() {
       while (true) {
           showMenu();

           if (player1 && player2) {
               winner = " ";
               board.reset();
               currentPlayer = player1;

               while (true) {
                   board.display();

                   // Use handleHumanMove or handleAiMove depending on the current player type
                   if (dynamic_cast<HumanPlayer*>(currentPlayer)) {
                       handleHumanMove(*dynamic_cast<HumanPlayer*>(currentPlayer));
                   }
                   else {
                       handleAiMove();
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
            setupPvC(Hard);
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
        // Setup Player vs Player mode
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
        char symbol;
        cout << "Your name: "<<endl;
        cin >> name;
        while(true){
        cout <<"choose symbol(X or O):"<<endl;
        cin>>symbol;
        if(symbol!='X'&&symbol!='O') {
            cout << "Invalid Symbol. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            break;
        }
    }
        player1 = new HumanPlayer(name, symbol);
        player2 = new AiPlayer("Computer", symbol=='X'? 'O':'X', difficulty);
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
    void handleHumanMove(HumanPlayer& player) {
        int row, col;
        while (true) {
            cout << "Enter row number (1-3): ";
            cin >> row;
            row--;
            if (cin.fail()) {
                cout << "Invalid move. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << "Enter column number (1-3): ";
            cin >> col;
            col--;
            if (cin.fail() || !board.isValidMove(row,col)) {
                cout << "Invalid move. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                board.makeMove(row,col,player.getSymbol()) ;
                break;
            }
        }
    }
    void handleAiMove() {
    int row, col;
    player2->getMove(board, row, col);  
    board.setCell(row, col, player2->getSymbol());
    cout << "AI plays at (" << row+1 << ", " << col+1 << ")\n";
    }

    bool checkgameEnd() {
    if (board.checkWin('X')) { 
        if (player1->getSymbol() == 'X') {
        winner = player1->getName();
    } else {
        winner = player2->getName();
        }
        return true;
    }
    if (board.checkWin('O')) { 
        if (player1->getSymbol() == 'O') {
        winner = player1->getName();
    } else {
        winner = player2->getName();
        }
        return true;
    }

    if(board.isFull()){
        winner = "Draw"; 
        return true;
    }
    return false;
    }

    void displayResult() const {
        if (winner == "Draw") {
            cout << "It's a draw!\n";
        }
        else {
            cout << "Winner is: " << winner << "\n";
        }
    }

    void reset() {
        board.reset();
        winner = " ";
    }
};


      
int main() {
// Main function to start the game
srand((unsigned)time(nullptr));         //generate seed for rand()

Game game;
game.start();

    return 0;
}
