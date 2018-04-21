/*/
 * A class that represents a Robot with the following fields:
 * - The number of the map its in.
 * - The number of the row its in.
 * - The number of the column its in.
 * - Its serial number.
 * - A static field which counts how many Robots were created.
 */
#ifndef ASS_3_ROBOT_H
#define ASS_3_ROBOT_H


#include <string>

using namespace std;

class Robot {
private:
    static int m_numOfCreatedRobots;
    int m_column;
    int m_row;
    int m_id;
    int m_mapNumber;
public:
    Robot();
    Robot(int column,int row,int mapNumber);
    ~Robot();

    Robot& operator=(const Robot& r1);

    int getId() const;
    int getMapNumber() const;
    int getColumn() const;
    int getRow() const;
    static int getNumOfCreatedRobots();

    void setMapNumber(int mapNumber);
    void setColumn(int column);
    void setRow(int row);
};


#endif //ASS_3_ROBOT_H
