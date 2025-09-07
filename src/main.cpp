#define STB_IMAGE_IMPLEMENTATION
#include "main.h"
#include "imgs/logo.h"
#include "imgs/enabled.h"
#include "imgs/disabled.h"

lv_obj_t* label_text;
lv_obj_t* btn_toggle;
lv_obj_t* btn_image;
lv_obj_t* estop_overlay;

lv_image_dsc_t* logo_img{nullptr};
lv_image_dsc_t* enabled_img{nullptr};
lv_image_dsc_t* disabled_img{nullptr};

// Toggle button callback
static void btn_toggle_action(lv_event_t* e) {
    G_IS_ROBOT_ENABLED = !G_IS_ROBOT_ENABLED;

    if (G_IS_ROBOT_ENABLED) {
        lv_label_set_text(label_text, "Robot Enabled");
        lv_image_set_src(btn_image, disabled_img);
    }
	else {
        lv_label_set_text(label_text, "Robot Disabled");
        lv_image_set_src(btn_image, enabled_img);
    }
}

void initialize() {
	std::cout << "Code authored by Peter Ferranti and can be found online at: https://github.com/onthegrid007/FRCTeam987-2014-PROS-V5\n";
	std::cout << "Initalizing...\n";
	logo_img = load_png_from_array(logo_png, logo_png_len);
	std::cout << "Loaded logo png\n";
    enabled_img = load_png_from_array(enabled_png, enabled_png_len);
	std::cout << "Loaded enabled png\n";
    disabled_img = load_png_from_array(disabled_png, disabled_png_len);
	std::cout << "Loaded disabled png\n";

	lv_obj_t* logo{lv_image_create(lv_screen_active())};
	lv_image_set_src(logo, logo_img);
	lv_obj_align(logo, LV_ALIGN_TOP_LEFT, 5, 5);
    label_text = lv_label_create(lv_screen_active());
	btn_toggle_action(nullptr);
    lv_obj_align(label_text, LV_ALIGN_TOP_MID, 0, 40);
    btn_toggle = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn_toggle, 120, 80);
    lv_obj_align(btn_toggle, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(btn_toggle, btn_toggle_action, LV_EVENT_CLICKED, NULL);
    btn_image = lv_image_create(btn_toggle);
	lv_image_set_src(btn_image, enabled_img);
    lv_obj_center(btn_image);

	// ESTOP
	estop_overlay = lv_obj_create(lv_screen_active());
    lv_obj_set_size(estop_overlay, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(estop_overlay, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(estop_overlay, lv_color_make(128, 0, 128), 0);
    lv_obj_set_style_bg_opa(estop_overlay, LV_OPA_COVER, 0);
    lv_obj_t* estop_label = lv_label_create(estop_overlay);
    lv_label_set_text(estop_label, "ESTOP");
    lv_obj_set_style_text_font(estop_label, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(estop_label, lv_color_white(), 0);
    lv_obj_align(estop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_bg_opa(estop_overlay, LV_OPA_TRANSP, 0);
    lv_obj_set_style_text_opa(lv_obj_get_child(estop_overlay, 0), LV_OPA_TRANSP, 0);
	std::cout << "Initalizing done!\n";
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while (true) {
		while (!G_IS_ROBOT_ENABLED || G_ESTOP) {
			G_LEFT_DT_FRONT.set_value(0);
			G_LEFT_DT_BACK.set_value(0);
			G_RIGHT_DT_FRONT.set_value(0);
			G_RIGHT_DT_BACK.set_value(0);
			G_INTAKE_MOTOR.set_value(0);
			G_STEPH_1.set_value(0);
			G_STEPH_2.set_value(0);
			if (G_ESTOP) {
				lv_obj_set_style_bg_opa(estop_overlay, LV_OPA_COVER, 0);
				lv_obj_set_style_text_opa(lv_obj_get_child(estop_overlay, 0), LV_OPA_COVER, 0);
				while (G_ESTOP) std::cout << "ESTOP!\n";
			}
			pros::delay(G_MAIN_UPDATE_DELAY);
		}

		// if (
		// 	G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L1) &&
		// 	G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L2) &&
		// 	G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
		// 	G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
		// ) G_ESTOP = true;

		// Left Drivetrain
		const auto rawLeftY{G_MAIN_CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)};
		const auto leftY{(std::abs(rawLeftY) < G_DT_DEADBAND) ? 0 : (rawLeftY > 0 ? mapval(rawLeftY, G_DT_DEADBAND, 127, 0, 127) : -mapval(-rawLeftY, G_DT_DEADBAND, 127, 0, 127))};
		G_LEFT_DT_FRONT.set_value(leftY);
		G_LEFT_DT_BACK.set_value(leftY);

		// Right Drivetrain
		const auto rawRightY{G_MAIN_CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)};
		const auto rightY{(std::abs(rawRightY) < G_DT_DEADBAND) ? 0 : (rawRightY > 0 ? mapval(rawRightY, G_DT_DEADBAND, 127, 0, 127) : -mapval(-rawRightY, G_DT_DEADBAND, 127, 0, 127))};
		G_RIGHT_DT_FRONT.set_value(-rightY);
		G_RIGHT_DT_BACK.set_value(-rightY);

		// Intake Motor
		if (G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			G_INTAKE_MOTOR.set_value(-127);
		}
		else {
			if (G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				G_INTAKE_MOTOR.set_value(127);
			}
			else {
				G_INTAKE_MOTOR.set_value(0);
			}
		}

		// Intake Pnu
		static bool intakeFlag{false};
		if (G_MAIN_CONTROLLER.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) intakeFlag = !intakeFlag;
		if (intakeFlag) G_INTAKE_PNU.move(-127);
		else G_INTAKE_PNU.move(0);
		

		// Finger Pnu
		static bool fingerFlag{false};
		if (G_MAIN_CONTROLLER.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) fingerFlag = !fingerFlag;
		if (fingerFlag) G_FINGER_PNU.move(-127);
		else G_FINGER_PNU.move(0);

		// WheelyBar Pnu
		static bool wheelyFlag{false};
		if (G_MAIN_CONTROLLER.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) wheelyFlag = !wheelyFlag;
		if (wheelyFlag) G_WHEELY_BAR_PNU.move(-127);
		else G_WHEELY_BAR_PNU.move(0);

		// Steph
		if (G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			G_STEPH_1.set_value(-127);
			G_STEPH_2.set_value(-127);
		}
		else {
			if (G_MAIN_CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				G_STEPH_1.set_value(63);
				G_STEPH_2.set_value(63);
			}
			else {
				G_STEPH_1.set_value(0);
				G_STEPH_2.set_value(0);
			}
		}

		pros::delay(G_MAIN_UPDATE_DELAY);
	}
}