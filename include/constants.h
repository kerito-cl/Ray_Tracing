#ifndef CONSTANTS_H
# define CONSTANTS_H

# define S (float)1e-8
# define PI (float)3.14159265358979323846
# define MAX_DEPTH 10
# define IMG_WIDTH 1020
# define IMG_HEIGHT 1980
# define DTR(degrees) (degrees * PI / 180.0)
# define RANDOM_FLOAT (float)rand() / (float)(RAND_MAX + 1.0)
# define RANDOM_FLOAT_RANGE(min, max) (float)(min + (max - min) * RANDOM_FLOAT)

#endif