#include <iostream>
#include "Game.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

/*
 * Initializing 2 Maps and an array of Robots.
 */
Game::Game(int board1[7][7],int board2[7][7]):
        m_map1(board1), m_map2(board2)
{
    m_robotArray = (Robot**) std::malloc (2* sizeof(Robot));
    m_robotArrayLength = 2;
}


/*
 * Destroys the game
 */
Game::~Game()
{
    int robotsNum = Robot::getNumOfCreatedRobots();
    for (int i = 0 ;i < robotsNum; i++)
        delete(m_robotArray[i]);
    std::free(m_robotArray);
}

/*
 * Increases the maximum length of the Robot array times 2
 */
void Game::increaseArraySize()
{
    m_robotArrayLength = m_robotArrayLength * 2;
    m_robotArray = (Robot**) std::realloc(m_robotArray, sizeof(Robot) * m_robotArrayLength);
}

bool Game::compareRobots(const void* r1,const void* r2)
{
    if(((Robot*)r1)->getColumn() < ((Robot*)r2)->getColumn())
        return true;
    else {
        if (((Robot*)r1)->getColumn() == ((Robot*)r2)->getColumn()) {
            if (((Robot*)r1)->getRow() < ((Robot*)r2)->getRow())
                return true;
            else {
                if (((Robot*)r1)->getRow() == ((Robot*)r2)->getRow()) {
                    return ((Robot*)r1)->getId() < ((Robot*)r2)->getId();
                }
                else
                    return false;
            }
        } else
            return false;
    }
}

/*
 * Add a new robot to the array
 * column - the given column of the new Robot.
 * row - the given row of the new Robot.
 * mapNumber - the number of the map that the Robot will be added to.
 */
void Game::AddRobot(int column,int row,int mapNumber)
{
    int wall = wallOrPath(mapNumber,column,row);
    if(wall == 1)
        cout << "Invalid Location\n";
    else {
        if (m_robotArrayLength == Robot::getNumOfCreatedRobots())   //reallocs the robot array
            increaseArraySize();
        int newRobotId = Robot::getNumOfCreatedRobots();
        Robot* robot = new Robot(column, row, mapNumber);
        m_robotArray[newRobotId] = robot;
        cout << "New Robot: " << newRobotId + 1 << " Map: " << mapNumber << " GPS: " << column << "," << row << endl;
    }
}

/*
 * Deletes a Robot by given id, deleting the Robot by putting the value 0 in his map number
 * robotId - the given id of the robot that should be deleted.
 */
void Game::DeleteRobot(int robotId)
{
    int length = Robot::getNumOfCreatedRobots();
    bool done = false;
    for(int i = 0;i < length && !done; i++)
        if(m_robotArray[i]->getId() == robotId) {
            if(m_robotArray[i]->getColumn() != -1) {
                cout << "Robot deleted" << robotId << " Map: " << m_robotArray[i]->getMapNumber() << " GPS: "
                     << m_robotArray[i]->getColumn() << "," << m_robotArray[i]->getRow()
                     << endl;
                m_robotArray[i]->setMapNumber(0);
            }
            done = true;
        }
}

/*
 * Moves the robot of the given ID to the given direction.
 * If the robot was deleted no change.
 * If the robot is going out of the map then changes its placement to (-1,-1).
 * If the robot wants to move to a wall, his position stays the same as before.
 * Prints the new location of the robot.
 * robotId - the ID of the given robot who should be moved.
 * direction - given direction (U,R,D,L) for the robot.
 */
void Game::MoveRobot(int robotId,char direction)
{
    int length = Robot::getNumOfCreatedRobots();
    bool done = false;
    int i = 0;
    for(i = 0;i < length && !done; i++)
        if(m_robotArray[i]->getId() == robotId) {
            done = true;
        }
    i = i - 1;
    if (m_robotArray[i]->getMapNumber() == 0)  //check if the robot was deleted already.
        return;
    int Xcoordenate = m_robotArray[i]->getColumn();
    int Ycoordenate = m_robotArray[i]->getRow();
    if (Xcoordenate == -1 && Ycoordenate == -1)   //check if the robot is out of the map.
        return;

    int mapOfRobot = m_robotArray[i]->getMapNumber();

    //check direction for all 4 cases
    if (direction == 'U')
        Ycoordenate = Ycoordenate - 1;
    if (direction == 'D')
        Ycoordenate = Ycoordenate + 1;
    if (direction == 'R')
        Xcoordenate = Xcoordenate + 1;
    if (direction == 'L')
        Xcoordenate = Xcoordenate - 1;

    //check if the new position of the robot is on the map
    if (robotInTheMap(Xcoordenate,Ycoordenate)) {
        //check if the position is a wall or path
        int temp = wallOrPath(mapOfRobot, Xcoordenate, Ycoordenate);
        if (wallOrPath(mapOfRobot, Xcoordenate, Ycoordenate) == 0) {
            m_robotArray[i]->setColumn(Xcoordenate);
            m_robotArray[i]->setRow(Ycoordenate);
        }
    }
    else{
        m_robotArray[i]->setColumn(-1);
        m_robotArray[i]->setRow(-1);
    }
    if (!(m_robotArray[i]->getRow() == -1 && m_robotArray[i]->getColumn() == -1))
        cout<< "Robot: " << robotId << " MAP: " << mapOfRobot << " GPS: " << m_robotArray[i]->getColumn() << "," << m_robotArray[i]->getRow() << endl;
}

/*/
 * Combines the maps' boards into one map and prints the new board
 */
void Game::combineMaps()
{
    Map temp = m_map1+m_map2;
    cout<<temp;
    sort(m_robotArray,m_robotArray + Robot::getNumOfCreatedRobots(),compareRobots);
    int robotsNum = Robot::getNumOfCreatedRobots();
    for(int i = 0; i < robotsNum; i++) {
        int wall = temp.PathOrWall(m_robotArray[i]->getColumn(),m_robotArray[i]->getRow());
        if (m_robotArray[i]->getMapNumber() != 0 && m_robotArray[i]->getColumn() != -1 && wall != 1)
            cout << "Robot: " << m_robotArray[i]->getId() << " GPS: " << m_robotArray[i]->getColumn() << "," << m_robotArray[i]->getRow() << "\n";
    }
}

/*/
 * Adds all the walls from one map's board to another and removes any Robots that are now in a wall
 * - mapToAddTo - the map whose board is being changed.
 * - mapToAdd - the map whose walls are added to the other map.
 */
void Game::addToMap(int mapToAddTo,int mapToAdd)
{
    if(mapToAddTo == 1)
        m_map1+=m_map2;
    else
        m_map2+=m_map1;
    int numOfRobot = Robot::getNumOfCreatedRobots();
    for (int i = 0; i < numOfRobot;i++)
    {
        int mapNumberOfRobot = m_robotArray[i]->getMapNumber();
        if (mapNumberOfRobot != 0 && mapNumberOfRobot == mapToAddTo) {
            int columnC = m_robotArray[i]->getColumn();
            int rowC = m_robotArray[i]->getRow();
            if (wallOrPath(mapNumberOfRobot, columnC, rowC) == 1)
                DeleteRobot(m_robotArray[i]->getId());
        }
    }
}

/*/
 * Copies one map's board to another and removes any Robots that are now in a wall
 * - mapToBePlaced - the map who gets the copy of the board from the other map
 * - mapToPlace - the map whose board is copied into the other map
 */
void Game::placementToMap(int mapToBePlaced,int mapToPlace)
{
    if (mapToBePlaced == 1 && mapToPlace == 2)
        m_map1=m_map2;
    else
        m_map2=m_map2;
    int numOfRobot = Robot::getNumOfCreatedRobots();
    for (int i = 0; i < numOfRobot;i++)
    {
        int mapNumberOfRobot = m_robotArray[i]->getMapNumber();
        if (mapNumberOfRobot != 0 && mapNumberOfRobot == mapToBePlaced) {
            int columnC = m_robotArray[i]->getColumn();
            int rowC = m_robotArray[i]->getRow();
            if (wallOrPath(mapNumberOfRobot, columnC, rowC) == 1)
                DeleteRobot(m_robotArray[i]->getId());
        }
    }
}

/*/
 * Checks if the 2 maps' boards are equal. Prints True if they are and False if they aren't
 */
void Game::areMapsEqual()
{
    if (m_map1==m_map2)
        cout<<"True\n";
    else
        cout<<"False\n";
}

/*/
 * Prints a given map's board and the Robots that are currently in it
 * - mapToPrint - the map whose board and Robots are printed.
 */
void Game::printMap(int mapToPrint)
{
    sort(m_robotArray,m_robotArray + Robot::getNumOfCreatedRobots(),compareRobots);
    if (mapToPrint == 1)
        cout<<m_map1;
    else
        cout<<m_map2;
    int robotsNum = Robot::getNumOfCreatedRobots();
    for(int i = 0; i < robotsNum; i++)
        if(m_robotArray[i]->getMapNumber() != 0 && m_robotArray[i]->getMapNumber() == mapToPrint)
            cout << "Robot: " << m_robotArray[i]->getId() << " MAP: " << m_robotArray[i]->getMapNumber() << " GPS: " << m_robotArray[i]->getColumn() << "," << m_robotArray[i]->getRow() << "\n";
}

/*
 * return true if the column and the row are in the board else false.
 * column - the given column to be checked.
 * row - the given row to be checked.
 */
bool Game::robotInTheMap(int column,int row)
{
    return !(column > 6 || column < 0 || row > 6 || row < 0);
}

/*
 * check if a given column and row are wall or path, return 1 for path, 0 for wall.
 * mapOfRobot - the given map needed to be checked.
 * column - the given column to be checked
 * row - the given row to be checked.
 */
int Game::wallOrPath(int mapOfRobot,int column,int row)
{
    if (mapOfRobot == 1)
    {
        return m_map1.PathOrWall(column,row);
    }
    else
    {
        return m_map2.PathOrWall(column,row);
    }
}