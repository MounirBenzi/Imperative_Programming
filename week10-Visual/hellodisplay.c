#include "display.h"
#include <stdio.h>
#include <stdbool.h>

#define SCALE 16
typedef struct location {int x, y;} location;

bool functionToCallRepeatedly(display *d, void *data, const char pressedKey) {
  location *l = (location*) data; // cast incoming data to be location*

  colour(d, 0xFF); // set current colour to black to clear old box
  block(d, 0, 0, getWidth(d), getHeight(d)); // draw screen as black

  // change position state based on pressedKey input
  switch (pressedKey) {
    case 79: l->x += SCALE; break; // go right
    case 80: l->x -= SCALE; break; // go left
    case 81: l->y += SCALE; break; // go down
    case 82: l->y -= SCALE; // go up
  }

  // limit position state to size of the display window (wrap-around)
  *l = (location) { (l->x + getWidth(d)) % getWidth(d), (l->y + getHeight(d)) % getHeight(d)};

  colour(d, 0xFFFF); // set current colour to blue
  block(d, l->x, l->y, SCALE, SCALE); // draw a box at new position (l->x,l->y)
  show(d); // show drawn stuff on the screen

  return (pressedKey == 27);
}

int main() {
  display *d = newDisplay("Hello Display", 320, 240);
  location *l = malloc(sizeof(location));
  *l = (location) {0, 0};
  run(d, l, functionToCallRepeatedly);
  free(l);
  freeDisplay(d);
}
