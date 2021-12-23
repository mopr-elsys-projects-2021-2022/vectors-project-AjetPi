#include "Field.h"

int main()
{
	Field field;
	bool gameLoopRunning = true;
	char command; // Game menu option
	
	while(gameLoopRunning)
	{
		cout << "Enter a command (c - change parameters, h - hit ball, f - show field specs or q - quit): ";
		cin >> command;
		switch(command)
		{
			case 'c': // Change parameters
			{
				cout << "Enter a command (s - simple field, c - complex field or b - ball): ";
				cin >> command;
				switch(command)
				{
					case 's': // Simple field
					{
						cout << endl;
						Field::simpleCase(field);
						break;
					}
					case 'c': // Complex field
					{
						cout << endl;
						Field::complexCase(field);
						break;
					}
					case 'b': // Ball
					{
						cout << endl;
						Field::ballCase(field);
						break;
					}
					default:
					{
						cout << "Invalid command. Try again." << endl;
					}
				}
				break;
			}
			case 'h': // Hit ball
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
			case 'f': // Field specs
			{
				cout << endl;
				cout << field;
				break;
			}
			case 'q': // Quit
			{
				gameLoopRunning = false;
				break;
			}
			default:
			{
				cout << "Invalid command. Try again." << endl;
			}
		}
	}
	
	return 0;
}
