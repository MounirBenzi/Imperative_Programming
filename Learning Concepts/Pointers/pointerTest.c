#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(){
  int a = 27;
  int arr[5] = {1,2,3,4,5};
  int *p;

  p = &a;
  //printf("This is my pointer location %p and val %d\n", p, *p);
  *p = 5;
  printf("Val: %d\n", *p);
  p = &arr[3];
  printf("Val: %lu\n", sizeof(arr)/sizeof(arr[0]));
  for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
    p = &arr[i];
    *p = arr[0];
  }
  for (int i = 0; i < 5; i++){
    printf("%d\n", arr[i]);
  }
  return 0;
}
