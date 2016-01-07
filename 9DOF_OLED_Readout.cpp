#include "mraa.hpp"

#include "sparkfun/oled/Edison_OLED.h"
#include "sparkfun/gpio/gpio.h"
#include "math.h"

#include <iostream>
#include <unistd.h>
#include "sparkfun/SFE_LSM9DS0.h"
using namespace std;

edOLED oled;

void SetupOLED();
void DrawOLED();

LSM9DS0 *imu;

int main() {
	imu = new LSM9DS0(0x6B, 0x1D);
	uint16_t imuResult = imu->begin();
	cout << hex << "Chip ID: 0x" << imuResult << dec << " (should be 0x49d4)"
			<< endl;

	SetupOLED();

	for (;;) {
		DrawOLED();
		sleep(1);
	}

	oled.clear(PAGE);
	oled.display();
	sleep(1);
	return 0;
}

void SetupOLED() {
	oled.begin();
	oled.clear(PAGE);
	oled.setFontType(0);
	oled.display();
}

void DrawOLED() {
	imu->readAccel();
	imu->readGyro();

	oled.clear(PAGE);
	oled.setCursor(0, 0);

	oled.print("GX:");
	oled.print(imu->calcGyro(imu->gx));

	oled.setCursor(0, 7);
	oled.print("GY:");
	oled.print(imu->calcGyro(imu->gy));

	oled.setCursor(0, 14);
	oled.print("GZ:");
	oled.print(imu->calcGyro(imu->gz));

	oled.setCursor(0, 21);
	oled.print("AX:");
	oled.print(imu->calcAccel(imu->ax));

	oled.setCursor(0, 28);
	oled.print("AY:");
	oled.print(imu->calcAccel(imu->ay));

	oled.setCursor(0, 35);
	oled.print("AZ:");
	oled.print(imu->calcAccel(imu->az));

	oled.display();
}
