#include <cstdio>

/*
 * Code for modified Lagrange formula
 * From https://www.math.umd.edu/~petersd/666/BarycentricLagrange1.pdf
 * Data for the 0118MF100 RTD temperature sensor
 */
int main() {
    const int NUM_TERMS = 10;

    /* Resistances */
    const double x[] = { 25.90, 34.54, 59.69, 67.89, 92.06, 100.00, 107.87,
                         131.21, 138.90, 146.55 };
    /* Temperatures at those resistances */
    const double y[] = { -180.0, -160.0, -100.0, -80.0, -20.0, 0.0, 20.0, 80.0,
                         100.0, 120.0 };
    /* Resistances that interploated temperatures are wanted for */
    const double xe[] = { 25.0, 34.0, 59.69, 67.0, 92.0, 101.0, 107.0, 131.0,
                          138.0, 146.0 };
    double d[NUM_TERMS];
    double ye[NUM_TERMS];
    double w[NUM_TERMS];
    double s[NUM_TERMS];
    double P[NUM_TERMS];
    int equalnode[NUM_TERMS];
    unsigned bigO_counter = 0;

    for (int i = 0; i < NUM_TERMS; ++i) {
        w[i] = 0.0;
        s[i] = 0.0;
        P[i] = 1.0;
        equalnode[i] = 0;
        bigO_counter++;
    }
    for (int j = 0; j < NUM_TERMS; j++) {
        w[j] = 1.0;
        for (int k = 0; k < j; k++) {
            w[k] = w[k] / (x[k] - x[j]);
            w[j] = w[j] / (x[j] - x[k]);
            bigO_counter++;
        }
    }
    for (int i = 0; i < NUM_TERMS; ++i) {
        printf("w[%d]=%g ", i, w[i]);
    }
    printf("\n");
    for (int j = 0; j < NUM_TERMS; j++) {
        for (int k = 0; k < NUM_TERMS; k++) {
            d[k] = xe[k] - x[j];
            if (d[k] == 0.0) {
                /*
                 * Avoid division by zero which would happen if xe coincides
                 * with a node. Store the node number for later substitution
                 * of y node for ye.
                 */
                equalnode[j] = 1;
            } else {
                s[k] = s[k] + y[j] * w[j] / d[k];
            }
            P[k] = P[k] * d[k];
            bigO_counter++;
        }
    }
    for (int j = 0; j < NUM_TERMS; j++) {
        ye[j] = P[j] * s[j];
        if (equalnode[j] != 1) {
            printf("ye[%d]=%g ", j, ye[j]);
        } else {
            /* Substitute y for ye when xe coincides with a node */
            printf("ye[%d]=%g ", j, y[j]);
        }
    }
    printf("\n");
    printf("Big O Counter = %d\n", bigO_counter);
}
