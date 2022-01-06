#include "Rosemount_0118MF.hpp"
#include <cstdio>

/*
 * Lagrangian interpolation for the 0118MF100 RTD temperature sensor
 */
int main() {
    double res;
    unsigned bigO_counter = 0;
    const int NUM_TERMS = 10;
    double term = 0.0, sum = 0.0;

    printf("\n\nEnter Rosemount 0118MF100 resistance (Ohms) to find\n"
        "temperature as a function of resistance: ");
    scanf("%lf", &res);
    for (int i = 0; i < NUM_TERMS; i++) {
        term = 1.0;
        for (int j = 0; j < NUM_TERMS; j++) {
            if (i != j) {
                term = term * ((res - RTD_Res_Temperature10[j][1]) /
                    (RTD_Res_Temperature10[i][1] -
                    RTD_Res_Temperature10[j][1]));
                bigO_counter++;
            }
        }
        sum = sum + RTD_Res_Temperature10[i][0] * term;
    }
    printf("\n f(%.2f) = %f C\n", res, sum);
    printf("Big O Counter = %d\n", bigO_counter);
}
