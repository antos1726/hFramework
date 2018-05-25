#include <hFramework.h>

void hMain()
{
	while (true)
	{
		if (Serial.available() > 0) // checking Serial availability
		{
			char c = Serial.getch(); // getting one character from Serial
			switch (c)				 // decision based on received character
			{
			case 'q': // in case of getting q
				Serial.printf("function 1\r\n"); // print "function 1" on USB-serial 
				hLED1.on();
				break;
			case 'a': // in case of getting a
				Serial.printf("function 2\r\n");
				hLED1.off();
				break;
			default: // in other case
				Serial.printf("you pulled unassigned char\r\n");
				hLED1.toggle();
				break;
			}
		}
		sys.delay(10);
	}
}