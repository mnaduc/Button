#include "Button.h"

Button::Button(uint8_t pin, uint16_t scan_press_time = 50, uint16_t debounce_time = 50, bool is_pull = true, bool is_pullup = true)
{
	pin_ = pin;
	pinMode(pin, INPUT);
	if (is_pull)
	{
		digitalWrite(pin, HIGH);
		is_pullup_ = true;
	}
	else
	{
		is_pullup_ = is_pullup;
	}
	last_debounce_time_ = millis();
	last_press_time_ = millis();
	debounce_time_ = debounce_time;
	scan_press_time_ = scan_press_time;
	btn_state_ = false;
	read_ = false; last_read_ = false;
	func_down_ = NULL;
	func_up_ = NULL;
	func_press_ = NULL;
}

void Button::setOnDown(void(*func)())
{
	func_down_ = func;
}

void Button::setOnUp(void(*func)(uint32_t time))
{
	func_up_ = func;
}

void Button::setOnPress(void(*func)(uint32_t time))
{
	func_press_ = func;
}

void Button::loop()
{
	read_ = is_pullup_ ? !digitalRead(pin_) : digitalRead(pin_);
	if (read_ != last_read_) 
	{
		last_debounce_time_ = millis();
		last_read_ = read_;
	}
	if (millis() - last_debounce_time_ > debounce_time_)
	{
		if (read_ != btn_state_)
		{
			btn_state_ = read_;
			if (btn_state_ == 1)
			{
				if (func_down_ != NULL) func_down_();
				press_time_ = debounce_time_;
				last_press_time_ = millis();				
			}
			else
			{
				if (func_up_ != NULL) func_up_(press_time_);
				press_time_ = 0;
			}
		}
		else
		{
			if (read_ == 1)
			{
				if (millis() - last_press_time_ > scan_press_time_)
				{
					last_press_time_ = millis();
					press_time_ += scan_press_time_;
					if (func_press_ != NULL) func_press_(press_time_);
				}
			}
		}
	}
}