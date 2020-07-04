#include "displayfull.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Data structure holding information from the pgm
typedef struct pgm{
  int w, h, maxVal;
  int data;
} pgm;

pgm *newPGM() {
  pgm *p = malloc(sizeof(pgm));
  p -> w = 0;
  p -> h = 0;
  p -> data = 0;
  return p; // this is a placeholder only
}
void freePGM(pgm *p){
  free(p);
}

int getOperand(int b){
  if (b & 0x20){ //100000 - check if start of 6 bits is negative
    return (b | ~0x3F);
  }
  else{
    return (b & 0x3f);
  }
}

void processPGM(char *filename){
  pgm *p = newPGM();
  char ch;
  char line[1000];
  char magicnumb[2];
  FILE *pgmImage = fopen(filename, "rb");
  fgets(line,100,pgmImage);
  sscanf(line, "%s %d %d %d", magicnumb, &(p -> w), &(p -> h), &(p -> maxVal)); //assigning the width, height and maxval
  /*printf("width is %d\n", p->w);
  printf("h is %d\n", p->h);
  printf("m is %d\n", p->maxVal);*/
  while(!feof(pgmImage)){
    for(int i =0; i < p->h; i++){
      for(int j =0; j < p->w; j++){
        printf("%d %d\n",i, j);
        p->data = fgetc(pgmImage);
        printf("%08x\n", p->data);
        for(int k = 0; k < 2; k++){
          printf("%d\n", k);
          p->data = (p->data << 2) | (p->data);
          p->data = (p->data <<6)|(p->data);
          printf("%32x\n", p->data);
          //call DATA
        }
        //p-> data = (p->data << 8) | 0xff;
        p->data = (p->data) & 0x3f;
        printf("COLOUR %16x\n", p->data);
      }
    }
  }
}




/*
Each PGM image consists of the following:
A "magic number" for identifying the file type. A pgm image's magic number is the two characters "P5".
Whitespace (blanks, TABs, CRs, LFs).
A width, formatted as ASCII characters in decimal.
Whitespace.
A height, again in ASCII decimal.
Whitespace.
The maximum gray value (Maxval), again in ASCII decimal. Must be less than 65536, and more than zero.
A single whitespace character (usually a newline).
A raster of Height rows, in order from top to bottom. Each row consists of Width gray values,
in order from left to right. Each gray value is a number from 0 through Maxval,
with 0 being black and Maxval being white.
Each gray value is represented in pure binary by either 1 or 2 bytes.
If the Maxval is less than 256, it is 1 byte. Otherwise, it is 2 bytes. The most significant byte is first.
*/



int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./converter file\n");
    exit(1);
  } else processPGM(args[1]); // otherwise view sketch file in argument
  return 0;
}
