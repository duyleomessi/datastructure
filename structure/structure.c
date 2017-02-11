#include <stdio.h>
#include <stdlib.h>
#include "house.h"

int main(int argc, char* argv[]) {
  int i;
  struct Room room1;
  room1.width = 20;
  room1.height = 30;
  room1.name = "Room 1";

  printf("room1 has width %d\n height %d\n", room1.width, room1.height);

  struct House house;
  house.address = "Ha Noi";
  for (i = 0; i < 10; i++) {
    house.rooms[i] = NULL;
  }

  house.rooms[0] = &room1;

  for (i = 0; i < 10; i++) {
    if (house.rooms[i] != NULL) {
      printf("Room %d has name %s and width is %d", i + 1, house.rooms[i]->name ,house.rooms[i]->width);
    }
  }

  
  return 0;
}
