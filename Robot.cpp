#include <iostream>
#include "Robot.h"

using namespace std;

int Robot::m_numOfCreatedRobots = 0;

/*/
 * An empty constructor for Robot. Initializes default values to all the fields
 */
Robot::Robot()
{
    m_numOfCreatedRobots++;
    m_id = m_numOfCreatedRobots;
    m_column = -1;
    m_row = -1;
    m_mapNumber = 0;
}

/*/
 * Initializes a Robot with a given location and a map
 */
Robot::Robot(int column, int row, int mapNumber)
{
    m_numOfCreatedRobots++;
    m_id = m_numOfCreatedRobots;
    m_column = column;
    m_row = row;
    m_mapNumber = mapNumber;
}

/*/
 * A default destructor for class Robot
 */
Robot::~Robot() {}

/*/
 * Returns the Robot's serial number
 */
int Robot::getId() const
{
    return m_id;
}

/*/
 * Returns the number of the map the Robot is in
 */
int Robot::getMapNumber() const
{
    return m_mapNumber;
}

/*/
 * Returns the number of row the Robot is in
 */
int Robot::getRow() const
{
    return m_row;
}

/*/
 * Return the current number of robots created
 */
int Robot::getNumOfCreatedRobots()
{
    return m_numOfCreatedRobots;
}

/*/
 * Returns the number of column the Robot is in
 */
int Robot::getColumn() const
{
    return m_column;
}

/*/
 * Sets a new map number for the Robot
 */
void Robot::setMapNumber(int mapNumber)
{
    m_mapNumber = mapNumber;
}

/*/
 * Sets a new column for the Robot
 */
void Robot::setColumn(int column)
{
    m_column = column;
}

/*/
 * Sets a new row for the Robot
 */
void Robot::setRow(int row)
{
    m_row = row;
}

/*/
 *Copying all of r1's fields into this Robot's fields.
 * r1 - the Robot whose fields are being copied from.
 */
Robot& Robot::operator=(const Robot& r1)
{
    m_id = r1.getId();
    m_row = r1.getRow();
    m_column = r1.getColumn();
    m_mapNumber = r1.getMapNumber();
    return *this;
}