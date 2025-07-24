#ifndef _BUTTONS_H_
#define _BUTTONS_H_

enum Buttons {
  BUT_NONE, // First!!!
  BUT_A,
  BUT_B,
  BUT_UP,
  BUT_DOWN,
  BUT_LEFT,
  BUT_RIGHT,
  BUT_N // Last!!!
};

typedef struct {
  int pin;                         // which pin the button is connected
  int state;                       // the current reading from the input pin
  int lastState;                   // the previous reading from the input pin
  unsigned long lastDebounceTime;  // the last time the output pin was toggled
} button_t;

void setup_buttons();
void read_buttons();
Buttons get_current_button();
void reset_button();

#endif
