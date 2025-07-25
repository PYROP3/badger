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
  File next = dir.openNextFile();
  File prev;
  bool hasPrev2 = false;
  if (selected_file_index == 0) {
    // If we are at the start of the list, we go to the last one (a.k.a. when the next one is null)
    if (!next) {
      // This is the only file
      return;
    }
    prev = selected_file;
    while (next) {
      prev.close();
      prev = selected_file;
      selected_file = next;
      selected_file_index++;
      next = dir.openNextFile();
    }
    prev.close();
  } else {
    // Otherwise we rewind and open (selected_file_index - 1) files
    selected_file.close();
    dir.rewindDirectory();
    for (int i = 0; i < selected_file_index - 1; i++) {
      next.close();
      next = dir.openNextFile();
    }
    selected_file = next;
    selected_file_index--;
  }
}
