#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

void seed_random_number_generator_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open seed file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int seed;
    if (fscanf(file, "%d", &seed) != 1) {
        fprintf(stderr, "Could not read seed from file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    srand(seed);
}

int generate_random_number(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}