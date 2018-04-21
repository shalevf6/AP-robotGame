/*/
 * A class that represents a Game with the following fields:
 * - A Robot array.
 * - 2 Maps.
 * - The maximum length of the Robot Array
 */
#ifndef ASS_3_GAME_H
#define ASS_3_GAME_H

#include "Robot.h"
#include "Map.h"

class Game {

private:
    int m_robotArrayLength;
    Robot** m_robotArray;
    Map m_map1;
    Map m_map2;

    void increaseArraySize();
    bool robotInTheMap(int Column,int row);
    int wallOrPath(int mapOfRobot,int column,int row);

public:
    Game(int board1[7][7], int board2[7][7]);
    ~Game();
    static bool compareRobots(const void* r1,const void* r2);

    void AddRobot(int column,int row,int mapNumber);
    void DeleteRobot(int robotId);
    void MoveRobot(int robotId,char direction);
    void combineMaps();
    void addToMap(int mapToAddTo,int mapToAdd);
    void placementToMap(int mapToBePlaced,int mapToPlace);
    void areMapsEqual();
    void printMap(int mapToPrint);


};


#endif //ASS_3_GAME_H