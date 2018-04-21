#include <iostream>
#include <cstdio>
#include "Game.h"

using namespace std;

int main() {
    string menu = "Robot control menu:\n1. Add robot\n2. Delete robot\n3. Move robot\n4. Operator +\n5. Operator +=\n6. Operator =\n7. Operator ==\n8. Operator <<\n9. Quit\nInput your option: ";
    int map1[7][7] = {{1,1,1,1,1,1,1},
                      {1,0,0,0,1,0,1},
                      {0,0,1,1,1,0,1},
                      {1,0,0,0,0,0,1},
                      {1,1,1,0,1,0,1},
                      {1,0,0,0,0,0,1},
                      {1,0,1,1,1,1,1}};

    int map2[7][7] = {{1,1,1,0,1,1,1},
                      {1,0,0,0,0,0,1},
                      {1,0,1,0,1,0,1},
                      {0,0,0,0,0,0,0},
                      {1,0,0,0,0,0,1},
                      {1,0,0,0,0,0,1},
                      {1,1,1,1,0,1,1}};
    Game game(map1,map2);
    cout<<menu;
    int choice;
    cin>>choice;
    int mapNum = 0;
    int mapNum1 = 0;
    int mapNum2 = 0;
    int robotNum = 0;
    while(choice != 9)
    {
        switch(choice) {
            case 1:
                cout << "Enter MAP number: ";
                cin >> mapNum;
                if(mapNum != 1 && mapNum != 2)
                    cout << "Invalid input\n";
                else {
                    cout << "Enter coordinates (X,Y): ";
                    int x;
                    char c;
                    int y;
                    scanf("%d%c%d", &x ,&c, &y);
                    game.AddRobot(x, y, mapNum);
                }
                break;
            case 2:
                cout << "Enter Robot number: ";
                cin >> robotNum;
                game.DeleteRobot(robotNum);
                break;
            case 3:
                cout << "Enter Robot number: ";
                cin >> robotNum;
                cout << "Enter direction: ";
                char direction;
                cin >> direction;
                if(direction != 'U' && direction != 'D' && direction != 'R' && direction != 'L')
                    cout << "Invalid input\n";
                else
                    game.MoveRobot(robotNum, direction);
                break;
            case 4:
                game.combineMaps();
                break;
            case 5:
                cout << "Enter first map number: ";
                cin >> mapNum1;
                if(mapNum1 != 1 && mapNum1 != 2)
                    cout << "Invalid input\n";
                cout << "Enter second map number: ";
                cin >> mapNum2;
                if((mapNum1 == 1 && mapNum2 != 2) || (mapNum1 == 2 && mapNum2 != 1))
                    cout << "Invalid input\n";
                else
                    game.addToMap(mapNum1, mapNum2);
                break;
            case 6:
                cout << "Enter first map number: ";
                cin >> mapNum1;
                if(mapNum1 != 1 && mapNum1 != 2)
                    cout << "Invalid input\n";
                cout << "Enter second map number: ";
                cin >> mapNum2;
                if((mapNum1 == 1 && mapNum2 != 2) || (mapNum1 == 2 && mapNum2 != 1))
                    cout << "Invalid input\n";
                else
                    game.placementToMap(mapNum1, mapNum2);
                break;
            case 7:
                game.areMapsEqual();
                break;
            case 8:
                cout << "Enter map number: ";
                cin >> mapNum;
                if(mapNum != 1 && mapNum != 2)
                    cout << "Invalid input\n";
                else
                    game.printMap(mapNum);
                break;
            default:
                cout << "Invalid input\n";
                break;
        }
        cout<<menu;
        cin>>choice;
    }
    return 0;
}
