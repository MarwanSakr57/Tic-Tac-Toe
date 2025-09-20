#include <iostream>
#include <vector>

using namespace std;

enum Difficulty{
    Easy,
    medium,
    hard
};
class Board{
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

class Player {
public:
    Player(const string& name,char symbol){

    }

    virtual void getMove(int& row,int& col)=0;

    
    string getName()const{

    }
    char getSymbol()const{

    }
    char getSymbol()const{

    }
    void setName(const string& name){

    }

};

class AiPlayer:public Player{
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

class Game {
    Game(){

    }

    void start(){

    }
    void showMenu(){

    }
    void setupPvP(){

    }
    void setupPvC(Difficulty difficulty){

    }
    void switchPlayer(){

    }
    void handleHumanMove(Player player){

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