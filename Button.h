#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>

class Button
{
private:
	uint8_t pin_;	
	uint32_t last_debounce_time_, last_press_time_;
	// debounce_time_ thoi gian xu ly debounce nut nhan
	// scan_press_time_ thoi gian chay lap lai ham nhan giu
	// press_time_ la tong thoi gian da nhan nut
	uint16_t debounce_time_, scan_press_time_;
	uint32_t press_time_;
	bool btn_state_;
	bool read_, last_read_;
	// is_pullup_ = true khi button mac kieu pullup
	bool is_pullup_;
	void (*func_down_)();
	void (*func_up_)(uint32_t time);
	void (*func_press_)(uint32_t time);
public:
	// is_pull = true dat pinMode la INPUT_PULLUP
	Button(uint8_t pin, uint16_t scan_press_time = 50, uint16_t debounce_time = 50, bool is_pull = true, bool is_pullup = true);
	void setOnDown(void(*func)());
	void setOnUp(void (*func)(uint32_t time));
	void setOnPress(void(*func)(uint32_t time));
	void loop();
};


#endif // !BUTTON_H_


