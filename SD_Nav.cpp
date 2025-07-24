#include "SD_Nav.h"

File selected_file;
File dir;
int selected_file_index = 0;

void nav_init() {
  dir = SD.open("/");
  selected_file = dir.openNextFile();
}

File nav_file() {
  return selected_file;
}

void next_file() {
  selected_file.close();
  File next = dir.openNextFile();
  if (!next) {
    dir.rewindDirectory();
    selected_file = dir.openNextFile();
    selected_file_index = 0;
  } else {
    selected_file = next;
    selected_file_index++;
  }
}

void prev_file() {
  File prev = dir.openNextFile();
  File prev2;
  bool hasPrev2 = false;
  if (!selected_file_index) {
    // If we are at the start of the list, we go to the last one (a.k.a. when the next one is null)
    while (prev) {
      if (hasPrev2) {
        prev2.close();
      }
      hasPrev2 = true;
      prev2 = selected_file;
      selected_file = prev;
      selected_file_index++;
      prev = dir.openNextFile();
    }
  } else {
    // Otherwise we rewind and open (selected_file_index - 1) files
    dir.rewindDirectory();
    for (int i = 0; i < selected_file_index; i++) {
      prev.close();
      prev = dir.openNextFile();
    }
    selected_file = prev;
    selected_file_index--;
  }
}
