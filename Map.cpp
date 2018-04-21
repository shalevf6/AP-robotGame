#include "iostream"
#include "Map.h"

using namespace std;


/*
 * initializing new map with paths all over the map.
 */
Map::Map(){
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            board[i][j] = 0;
}

/*
 * initializing new map by an input.
 */
Map::Map(int newMap[7][7]){
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            board[i][j] = newMap[i][j];
}

/*
 * destroy the map;
 */
Map::~Map (){

}

/*
 * creating a new map by Or operator on the two maps.
 * m1 - the first given map.
 */
Map Map::operator+(const Map& m1)const{
    Map newBoard = Map();
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            if (board[i][j] == 1 || m1.board[i][j] == 1)
                newBoard.board[i][j] = 1;
            else
                newBoard.board[i][j] = 0;
    return newBoard;
}
/*
 * adding the walls of map m1 to the current map.
 * m1 - the map the its walls be added to the current map.
 */
Map& Map::operator+=(const Map& m1){
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            if (m1.board[i][j] == 1)
                board[i][j] = 1;
    return *this;
}
/*
 * copying the whole map m1 into the current map.
 * m1 - the map that its walls are copied to the current map.
 */
Map& Map::operator=(const Map& m1){
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            board[i][j] = m1.board[i][j];
    return *this;
}

/*
 * return true or false if the given map are identical to the current map.
 * m1 - the given map.
 */
bool Map::operator==(const Map& m1)const{
    for (int i = 0; i < 7;i++)
        for (int j = 0; j < 7;j++)
            if (board[i][j] != m1.board[i][j])
                return false;
    return true;
}

/*/
 * A private function to print the map's board
 */
ostream & Map::Show(ostream & out)const
{
    for (int i = 0; i < 7;i++) {
        cout<<'[';
        for (int j = 0; j < 7; j++){
            if (j < 6)
                cout<<board[i][j] << ' ';
            else
                cout<<board[i][j] << ']';
        }
        cout<< "\n";
    }
}

/*
 * printing a given map with the right format.
 */
ostream & operator<<(ostream& out,const Map & map)
{
    map.Show(out);
}

/*
 * return 0 if the given position is a path, 1 if it is a wall
 * column - the given column of the position.
 * row - the given row of the position.
 */
int Map::PathOrWall (int column, int row)
{
    return board[row][column];
}