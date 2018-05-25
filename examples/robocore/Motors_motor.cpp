#include <hFramework.h>

void encoder()
{
	while (true)
	{
		Serial.printf("pos: %d\r\n", hMot1.getEncoderCnt()); // print the current position of Motor 1 (no. of encoder ticks)
		hLED1.toggle();
		sys.delay(100);
	}
}

void hMain()
{
	sys.taskCreate(encoder); // this creates a task that will execute `encoder` concurrently
	while (true)
	{
		hMot1.setPower(500); // set motor power to 500 (50% of max power)
		sys.delay(1000);
		hMot1.setPower(-500); // set motor power to 500 (50% of max power) in reverse direction
		sys.delay(1000);
	}
}
