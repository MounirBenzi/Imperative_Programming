#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

#define SHRT_BIT sizeof(short)*CHAR_BIT
#define INT_BIT sizeof(int)*CHAR_BIT
#define LONG_BIT sizeof(long)*CHAR_BIT

/*Printing function that loops through the binary array, priting the elements*/
void printBin(char binary[], int numBits){
  for (int i = 0; i < numBits; i++){
    printf("%d", binary[i]);
  }
  printf("\n");
}

/*My implementation of Twos complement, takes in the the binary array
flips all 0s to ones, then using an if statements applies binary
arithmetic*/
void twosCompliment(char binary[], int numBits){
  int i =0, adding =1;
  //Chaning 0s to 1s
  for(i = 0; i < numBits; i++){
    if (binary[i] == 1){
      binary[i] = 0;
    }
    else {
      binary[i] = 1;
    }
  }
  //printing Onescompliment
  printf("Ones Compliment: ");
  printBin(binary, numBits);
  //Adding the 1
  for (i = numBits-1; i >= 0; i--){
    if(binary[i] == 1 && adding == 1){//if element we're adding to is 1
      binary[i] = 0;
    }
    else if (binary[i] == 0 && adding == 1){//if element we're adding to is 0
      binary[i] = 1;
      adding = 0;
    }
    else{
      binary[i] = binary[i];
    }
  }
  //printing TwosCompliment
  printf("Twos Compliment: ");
  printBin(binary, numBits);
}
/*function that cheks if number is negative -
its a function to prevent reoccurance*/
bool checkNeg(long numToCheck){
  if(numToCheck < 0){
    return true;
  }
  else{
    return false;
  }
}

/*Converting denary to binary using modulo function, finding the
remainder and adding it to an array*/
void denToBin(char buffer[], long numToConvert){
  long numTemp = numToConvert;
  char remainder = 0;
  for(int i = 0; numTemp != 0; i++){
    remainder = numTemp%2;
    numTemp = numTemp/2;
    buffer[i] = remainder;
  }
}
 /*When we convert the number to binary and save it to a list,
 its saved in reverse order so we must flip the array to stay consistent with
  our convention of elem 0 being the start of the array */
void flipArr(char buffer[], char binary[], int numBits){
  int temp = 0;
  for (int i = numBits-1; i >= 0; i--){
    binary[temp] = buffer[i];
    temp++;
  }
}

//Converting char to binary
int convertChar(const char length[]){
  char buffer[CHAR_BIT] = {0}, binary[CHAR_BIT] = {0}, inputChar = 0,
      *endptr;
  //converts strings to a long data type and checks for overflow
  long long_val = strtol(length, &endptr, 10);
  if (*endptr != '\0' || long_val < CHAR_MIN || long_val > CHAR_MAX){
      return -1;
  }
  bool isNeg = checkNeg(long_val); //checking if number is negative
  inputChar = (signed char)long_val; //changing the long to a signed char
  if (isNeg){ //making number positive, finding the binary first then twosCompliment
    long_val = long_val * -1;
  }
  denToBin(buffer, long_val);//converting to bin
  flipArr(buffer, binary, CHAR_BIT);
  if (isNeg){//if negative we have to follow twosCompliment
    twosCompliment(binary, CHAR_BIT);
  }
  else{
    printf("%d binary digits: ", inputChar);
    printBin(binary, CHAR_BIT);
  }
  return 0;
}

//dealing with type int
int convertShort(const char length[]){
  char buffer[SHRT_BIT] = {0}, binary[SHRT_BIT] = {0}, inputChar = 0,
      *endptr;
  //converts strings to a long data type and checks for overflow
  long long_val = strtol(length, &endptr, 10);
  if (*endptr != '\0' || long_val < SHRT_MIN || long_val > SHRT_MAX){
      return -1;
  }
  bool isNeg = checkNeg(long_val);
  inputChar = (short)long_val;
  if (isNeg){
    long_val = long_val * -1;
  }
  denToBin(buffer, long_val);
  flipArr(buffer, binary, SHRT_BIT);

  if (isNeg){
    twosCompliment(binary, SHRT_BIT);
  }
  else{
    printf("%d binary digits: ", inputChar);
    printBin(binary, SHRT_BIT);
  }
  return 0;
}

//dealing with type int
int convertInt(const char length[]){
  char buffer[INT_BIT] = {0}, binary[INT_BIT] = {0}, inputChar = 0,
     *endptr;
  //converts strings to a long data type and checks for overflow
  long long_val = strtol(length, &endptr, 10);
  if (*endptr != '\0' || long_val < INT_MIN || long_val > INT_MAX){
      return -1;
  }
  bool isNeg = checkNeg(long_val);
  inputChar = (int)long_val;
  if (isNeg){
    long_val = long_val * -1;
  }
  denToBin(buffer, long_val);
  flipArr(buffer, binary, INT_BIT);
  if (isNeg){
    twosCompliment(binary, INT_BIT);
  }
  else{
    printf("%d binary digits: ", inputChar);
    printBin(binary, INT_BIT);
  }
  return 0;
}

//dealing with type long
int convertLong(const char length[]){
  char buffer[LONG_BIT] = {0}, binary[LONG_BIT] = {0}, *endptr;
  long tempLong = 0;
  //converts strings to a long data type and checks for overflow
  long long_val = strtol(length, &endptr, 10);
  if (*endptr != '\0' || long_val < LONG_MIN || long_val > LONG_MAX){
      return -1;
  }
  bool isNeg = checkNeg(long_val);
  //decToHex(long_val);
  tempLong = long_val;
  if (isNeg){
    long_val = long_val * -1;
  }
  denToBin(buffer, long_val);
  flipArr(buffer, binary, LONG_BIT);
  if (isNeg){
    twosCompliment(binary, LONG_BIT);
  }
  else {
    printf("%ld binary digits: ", tempLong);
    printBin(binary, LONG_BIT);
  }
  return 0;
}

//Checking what type the user has entered
char typeToConvert(char type[], const char length[]){
  char str[10];
  memcpy(str, type, 8); //copying the entered text for comparason
  str[8] = '\0';
  if (strcmp(str, "char") == 0){
    convertChar(length);
  }
  else if (strcmp(str, "short") == 0){
    convertShort(length);
  }
  else if (strcmp(str, "int") == 0){
    convertInt(length);
  }
  else if (strcmp(str, "long") == 0){
    convertLong(length);
  }
  else {
    printf("Type is either invalid or not supported, see readme.txt\n");
    return -1;
  }
  return 0;
}

int main(int n, char *args[n]){
  if (n == 3){
    typeToConvert(args[1], args[2]);
  }
  else{
    fprintf(stderr, "Use e.g.: ./visualise char 7");
    exit(1);
  }
}
