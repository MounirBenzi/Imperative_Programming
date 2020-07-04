// Basic program skeleton for a Sketch File (.sk) Viewer
#include "displayfull.h"
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Allocate memory for a drawing state and initialise it
state *newState() {
  state *s = malloc(sizeof(state));
  s->x = 0;
  s->y = 0;
  s->tx = 0;
  s->ty = 0;
  s->tool = LINE;
  s->start = 0;
  s->data = 0;
  s->end = false;
  return s; // this is a placeholder only
}

// Release all memory associated with the drawing state
void freeState(state *s) {
  free(s);
}

// Extract an opcode from a byte (two most significant bits).
int getOpcode(byte b) {
  int opcode = b >> 6; //all but the last 6 bits
  return opcode; // this is a placeholder only
}

// Extract an operand (-32..31) from the rightmost 6 bits of a byte.
int getOperand(byte b){
  if (b & 0x20){ //100000 - check if start of 6 bits is negative
    return (b | ~0x3F);
  }
  else{
    return (b & 0x3f);
  }
}

void dyHelper(display *d, state *s, int operand){
  s -> ty += operand;
  if(s->tool == LINE){
    line(d,s->x,s->y,s->tx,s->ty);
  }
  else if(s->tool == BLOCK){
    block(d,s->x,s->y,(s->tx) - (s->x),(s->ty) - (s->y));
}
  s->x=s->tx;
  s->y=s->ty;
}

void toolHelper(display *d, state *s, int operand){
  if (operand == NONE){//comvert to none
    s -> tool = NONE;
  }
  else if (operand == LINE) {//covert to line
    s -> tool = LINE;
  }
  else if (operand == BLOCK) {//Draw block
    s -> tool = BLOCK;
  }
  else if (operand == COLOUR) {//Colour
    colour(d, s->data);
  }
  else if (operand == TARGETX) {//TARGETX
    s -> tx = s -> data;
  }
  else if (operand == TARGETY) {//TARGETY
    s -> ty = s -> data;
  }
  else if(operand == SHOW){//show
    show(d);
  }
  else if(operand == PAUSE){//PAUSE
    pause(d, s->data);
  }
  else if(operand == NEXTFRAME){//NEXTFRAME
    s->end =1;
  }
  s->data = 0;
}

// Execute the next byte of the command sequence.
void obey(display *d, state *s, byte op) {
  int opcode = getOpcode(op);
  int operand = getOperand(op);
  if (opcode == DX){ //Call to DX
    s -> tx += operand;
  }
  else if (opcode == DY){//Call to DY
    dyHelper(d, s, operand);
  }
  else if (opcode == TOOL){//Call to TOOL
    toolHelper(d, s, operand);
  }
  else if(opcode == DATA){//Call to DATA
   s->data = (s->data << 6) | (operand & 0x3f); //shifting 6 to left
  }
}

// Draw a frame of the sketch file. For basic and intermediate sketch files
// this means drawing the full sketch whenever this function is called.
// For advanced sketch files this means drawing the current frame whenever
// this function is called.
bool processSketch(display *d, void *data, const char pressedKey) {
  if (data == NULL){
      return pressedKey == 27;
  }
  state *s = (state *)data;
  char *filename = getName(d);
  FILE *in = fopen(filename, "rb");
  if (s->start != 0){ //checking if we need to start in specific location
    fseek(in, s->start, SEEK_SET); //setting start location
  }
  byte op = fgetc(in); //getting next char
  obey(d,s,op);
  while(!feof(in) & (s->end != 1)){
    op = fgetc(in);
    obey(d,s,op);
    }
  if (feof(in)){
    s->start = 0; //resetting state at the end of the file
  }
  else if (s->end == 1){
    s -> start = ftell(in);
    }
  show(d);
  fclose(in);
  *s = (state){0,0,0,0, LINE, s->start, 0, 0};
  return (pressedKey == 27);
}

// View a sketch file in a 200x200 pixel window given the filename
void view(char *filename) {
  display *d = newDisplay(filename, 200, 200);
  state *s = newState();
  run(d, s, processSketch);
  freeState(s);
  freeDisplay(d);
}

// Include a main function only if we are not testing (make sketch),
// otherwise use the main function of the test.c file (make test).
#ifndef TESTING
int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./sketch file\n");
    exit(1);
  } else view(args[1]); // otherwise view sketch file in argument
  return 0;
}
#endif
