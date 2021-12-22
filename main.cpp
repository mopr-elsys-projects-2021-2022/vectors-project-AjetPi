#include "Field.h"

int main()
{
	Field field;
	bool gameLoopRunning = true;
	char command; // the value of command describes which option of the menu of the game is going to be used
	
	while(gameLoopRunning)
	{
		cout << "Enter a command (c - change parameters, h - hit ball, f - show field specs or q - quit): ";
		cin >> command;
		switch(command)
		{
			case 'c': // 'c' stands for "change" - it's for changing the parameters of the field or the ball
				cout << "Enter a command (s - simple field, c - complex field or b - ball): ";
				cin >> command;
				switch(command)
				{
					case 's': // 's' stands for "simple case" - the horizontal side of the field is parallel to the x-axis, while the other one - to the y-axis
						cout << endl;
						Field::simpleCase(field);
						break; 
					case 'c': // 'c' stands for "complex case" - it is not nessecary for the sides of the field to be perpendicular to any axis
						cout << endl;
						Field::complexCase(field);
						break;
					case 'b': // 'b' stands for "ball case" - keeps the same field and only changes the ball position
						cout << endl;
						Field::ballCase(field);
						break;
					default:
						cout << "Invalid command. Try again." << endl;
				}
				break;
			case 'h': // 'h' stands for "hit" - it's the option for defining in which direction and how strongly the ball is going to be hit
			{
				cout << endl;
				Point targetPoint;
				double power;
				cout << "Input coordinates of target point: ";
				cin >> targetPoint;
				cout << "Input power: ";
				cin >> power;
				field.hit(targetPoint, power);
				break;
			}
			case 'f': // 'f' stands for "field" - it's used to show the specifications of the current field and ball
				cout << endl;
				cout << field;
				break;
			case 'q': // 'q' stands for "quit" - it stops the game loop
				gameLoopRunning = false;
				break;
			default:
				cout << "Invalid command. Try again." << endl;
		}
	}

	return 0;
}
