/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>

#include "Debug.h"
#include "EPD_4in0e.h"
#include "EPD_DEV_Config.h"
#include "SD_Nav.h"
#include "Buttons.h"

#define SD_PIN 10
File root;

unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
Buttons currentButton = BUT_NONE;

button_t buttons[] = {
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0}
};

void setup_buttons() {
  for (int i = 1; i < (int)BUT_N; i++) {
    pinMode(buttons[i-1].pin, INPUT_PULLUP);
  }
}

void read_buttons() {
  int reading;
  button_t *current;
  
  currentButton = BUT_NONE;
  
  for (int i = 1; i < (int)BUT_N; i++) {
    //Debug("Button ");
    //Debug(i);
    current = &buttons[i-1];
    reading = digitalRead(current->pin);
    //Debug(" reading=");
    //Debug(reading);
    
    // If the switch changed, due to noise or pressing:
    if (reading != current->lastState) {
      // reset the debouncing timer
      current->lastDebounceTime = millis();
    }
    
    if ((millis() - current->lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
      if (reading != current->state) {
        current->state = reading;
  
        // only update the current button if the new button state is LOW (INPUT_PULLUP)
        if (reading == LOW) {
          currentButton = (Buttons)i;
        }
      }
    }

    current->lastState = reading;
    //Debug("\r\n");
  }
}

Buttons get_current_button() {
  return currentButton;
}

void reset_button() {
  currentButton = BUT_NONE;
}


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

#if 0
  Debug("EPD_4IN0E_test Demo\r\n");
  DEV_Module_Init();

  Debug("e-Paper Init and Clear...\r\n");
  EPD_4IN0E_Init();
  EPD_4IN0E_Clear(EPD_4IN0E_WHITE);
  DEV_Delay_ms(500);
#endif

  Debug("Initializing SD card...");

  if (!SD.begin(SD_PIN)) {
    Debug("initialization failed!\r\n");
    while (1);
  }
  Debug("initialization done.\r\n");

  nav_init();

  setup_buttons();

#if 0
  Debug("Start nav test\r\n");
  
  Debug(nav_file().name());
  Debug("\r\n");
  next_file();
  Debug(nav_file().name());
  Debug("\r\n");
  next_file();
  Debug(nav_file().name());
  Debug("\r\n");
  next_file();
  Debug(nav_file().name());
  Debug("\r\n");
  prev_file();
  Debug(nav_file().name());
  Debug("\r\n");
  prev_file();
  Debug(nav_file().name());
  Debug("\r\n");
  prev_file();
  Debug(nav_file().name());
  Debug("\r\n");
  prev_file();
  Debug(nav_file().name());
  Debug("\r\n");
  prev_file();
  Debug(nav_file().name());
  Debug("\r\n");
  next_file();
  Debug(nav_file().name());
  Debug("\r\n");
  next_file();
  Debug(nav_file().name());
  Debug("\r\n");
#endif

  Debug("done!\r\n");
}

void loop() {
  read_buttons();
  if (currentButton != BUT_NONE) {
    Debug("current button:");
    Debug(currentButton);
    Debug("\r\n");
  }

  switch (currentButton) {
    case BUT_LEFT:
      Debug("PREV > ");
      prev_file();
      Debug(nav_file().name());
      Debug("\r\n");
      break;
    
    case BUT_RIGHT:
      Debug("NEXT > ");
      next_file();
      Debug(nav_file().name());
      Debug("\r\n");
      break;
  }
}
