typedef struct Room {
  int width;
  int height;
  char *name;
} room;

typedef struct House {
  char *address;
  struct Room *rooms[10];
} house;

 
