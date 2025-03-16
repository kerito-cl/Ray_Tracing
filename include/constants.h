#ifndef CONSTANTS_H
# define CONSTANTS_H

# define LIGHT_VISIBLE 0
# define LIGHT_RADIUS 1
# define METAL_FUZZ 0.05f
# define METAL_BR_RATIO 0.5f
# define GLASS_REF_IDX 0.5f
# define S (float)1e-8
# define PI (float)3.14159265358979323846
# define SHININESS 30
# define MAX_DEPTH 10
# define IMG_WIDTH 1920
# define IMG_HEIGHT 1080
# define DTR(degrees) (degrees * PI / 180.0)
# define RANDOM_FLOAT (float)rand() / (float)(RAND_MAX + 1.0)
# define RANDOM_FLOAT_RANGE(min, max) (float)(min + (max - min) * RANDOM_FLOAT)

#endif