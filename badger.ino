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

File root;

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

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  nav_init();
  
  Serial.println("Start nav test");
  
  Serial.println(nav_file().name());
  next_file();
  Serial.println(nav_file().name());
  next_file();
  Serial.println(nav_file().name());
  next_file();
  Serial.println(nav_file().name());
  prev_file();
  Serial.println(nav_file().name());
  prev_file();
  Serial.println(nav_file().name());
  prev_file();
  Serial.println(nav_file().name());
  prev_file();
  Serial.println(nav_file().name());
  prev_file();
  Serial.println(nav_file().name());
  next_file();
  Serial.println(nav_file().name());
  next_file();
  Serial.println(nav_file().name());

  Serial.println("done!");
}

void loop() {
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
