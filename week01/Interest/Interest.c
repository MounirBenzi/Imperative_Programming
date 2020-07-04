
#include <stdio.h>

double add(double amount, double interestRate){
  return amount *(1+interestRate/100);
}

int main(void){
  double amount, ir;
  printf("How much do you have in savings?\n");
  scanf("%lf", &amount);
  printf("What is the interest rate per year?\n");
  scanf("%lf", &ir);

  printf("Adding %1f%% interest gives to %lf gives you £%lf\n",ir, amount, add(amount,ir) );
}
