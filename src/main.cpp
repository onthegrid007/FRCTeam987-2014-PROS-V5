#include "main.h"

void initialize() {
	std::cout << "Initalizing...\n";
	pros::lcd::initialize();
	pros::lcd::set_text(1, "FRC Team 987 - 2014");
	// pros::lcd::set_text(2, "ROBOT: Disabled");
	std::cout << "Initalizing done!\n";
}

void disabled() {
	std::cout << "Robot Disabled!\n";
	pros::lcd::set_text(2, "ROBOT: Disabled");
}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	std::cout << "Robot Enabled!\n";
	pros::lcd::set_text(2, "ROBOT: Enabled");

	while (true) {
		pros::delay(G_MAIN_UPDATE_DELAY);
	}

	// pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	// pros::MotorGroup right_mg({-4, 5, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


	// while (true) {
	// 	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

	// 	// Arcade control scheme
	// 	int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
	// 	int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
	// 	left_mg.move(dir - turn);                      // Sets left motor voltage
	// 	right_mg.move(dir + turn);                     // Sets right motor voltage
	// 	pros::delay(20);                               // Run for 20 ms then update
	// }
}