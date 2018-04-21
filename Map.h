/*/
 * A class that represents a Map with a 7X7 board
 */
#ifndef UNTITLED1_MAP_H
#define UNTITLED1_MAP_H

#include "Robot.h"
#include "iostream"
#include <string>

using namespace std;

/*
 * class Map represents a Map of 7X7 for the Game with the following fields :
 * map - a two dimension array for the map.
 *
 */
class Map {
private :   //X for column and Y for rows.
    int board[7][7];
    ostream & Show(ostream & out)const;

public :
    Map();
    Map(int newMap[7][7]);
    ~Map ();
    Map operator+(const Map& m1)const;
    Map& operator+=(const Map& m1);
    Map& operator=(const Map& m1);
    bool operator==(const Map& m1)const;
    friend ostream & operator<<(ostream& out,const Map& map);

    int PathOrWall (int column, int row);

};


#endif //UNTITLED1_MAP_H