#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> 

#define NUM_ITERATIONS 32000000

// No Optimization.

typedef struct {
    float x;
    float y;
    float z;
    float r;
} t_vec3;

t_vec3 vec3_new(float x, float y, float z) {
    return (t_vec3){ x, y, z, 0 };
}

float vec3_dot(t_vec3 vec1, t_vec3 vec2) {
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.r * vec2.r);
}

t_vec3 vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2) {
    return (t_vec3){ vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.r * vec2.r };
}

// AVX2

typedef struct __attribute__((aligned(32))) {
    __m256 x;
    __m256 y;
    __m256 z;
} t_vec8;

void vec8_new(float x[8], float y[8], float z[8], t_vec8 *vec) {
    vec->x = _mm256_load_ps(x);
    vec->y = _mm256_load_ps(y);
    vec->z = _mm256_load_ps(z);
}

void vec8_dot(t_vec8 vec1, t_vec8 vec2, float res[8]) {
    __m256 x_prod = _mm256_mul_ps(vec1.x, vec2.x);
    __m256 y_prod = _mm256_mul_ps(vec1.y, vec2.y);
    __m256 z_prod = _mm256_mul_ps(vec1.z, vec2.z);
    __m256 result = _mm256_add_ps(_mm256_add_ps(x_prod, y_prod), z_prod);
    _mm256_store_ps(res, result);
}

void vec8_mul_vecs(t_vec8 vec1, t_vec8 vec2, t_vec8 *res) {
    res->x = _mm256_mul_ps(vec1.x, vec2.x);
    res->y = _mm256_mul_ps(vec1.y, vec2.y);
    res->z = _mm256_mul_ps(vec1.z, vec2.z);
}

// SSE

typedef struct {
    __m128 data;
} t_vec4;

t_vec4 vec4_new(float x, float y, float z) {
    return (t_vec4){ _mm_set_ps(0, z, y, x) };
}

float vec4_dot(t_vec4 vec1, t_vec4 vec2) {
    __m128 mul = _mm_mul_ps(vec1.data, vec2.data);
    __m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(mul, shuf);
    shuf = _mm_movehl_ps(shuf, sums);
    sums = _mm_add_ss(sums, shuf);
    return _mm_cvtss_f32(sums);
}

t_vec4 vec4_mul_vecs(t_vec4 vec1, t_vec4 vec2) {
    return (t_vec4){ _mm_mul_ps(vec1.data, vec2.data) };
}

// Build test


float *rand_x1, *rand_y1, *rand_z1, *rand_x2, *rand_y2, *rand_z2;


void generate_random_data(int size) {
    for (int i = 0; i < size; i++) {
        rand_x1[i] = (double)rand() / RAND_MAX * 100.0;
        rand_y1[i] = (double)rand() / RAND_MAX * 100.0;
        rand_z1[i] = (double)rand() / RAND_MAX * 100.0;
        rand_x2[i] = (double)rand() / RAND_MAX * 100.0;
        rand_y2[i] = (double)rand() / RAND_MAX * 100.0;
        rand_z2[i] = (double)rand() / RAND_MAX * 100.0;
    }
}

void benchmark_vec3() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    float dot = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        t_vec3 v1 = {rand_x1[i], rand_y1[i], rand_z1[i]};
        t_vec3 v2 = {rand_x2[i], rand_y2[i], rand_z2[i]};
        t_vec3 mul = vec3_mul_vecs(v1, v2);
        dot *= vec3_dot(v1, v2);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("t_vec3 operations took %f, %f seconds\n", cpu_time_used, dot);
}

void benchmark_vec8() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    float res_dots[8]= {};
    float res = 0;
    for (int i = 0; i < (NUM_ITERATIONS / 8); i++) {
        t_vec8 v1, v2, res_mul;
        vec8_new(&rand_x1[i * 8], &rand_y1[i * 8], &rand_z1[i * 8], &v1);
        vec8_new(&rand_x2[i * 8], &rand_y2[i * 8], &rand_z2[i * 8], &v2);
        vec8_mul_vecs(v1, v2, &res_mul);
        vec8_dot(v1, v2, res_dots);
        res *= res_dots[0];
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("t_vec8 (AVX2) operations took %f, %f seconds\n", cpu_time_used, res);
}

void benchmark_vec4() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    float dot = 0;
    for (int i = 0; i < (NUM_ITERATIONS / 4); i++) {
        t_vec4 v1 = vec4_new(rand_x1[i * 4], rand_y1[i * 4], rand_z1[i * 4]);
        t_vec4 v2 = vec4_new(rand_x2[i * 4], rand_y2[i * 4], rand_z2[i * 4]);

        t_vec4 mul = vec4_mul_vecs(v1, v2);
        dot *= vec4_dot(v1, v2);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("t_vec4 (SSE) operations took %f seconds %f\n", cpu_time_used, dot);
}

int main() {
    srand(time(NULL));

    if (posix_memalign((void**)&rand_x1, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);
    if (posix_memalign((void**)&rand_y1, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);
    if (posix_memalign((void**)&rand_z1, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);
    if (posix_memalign((void**)&rand_x2, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);
    if (posix_memalign((void**)&rand_y2, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);
    if (posix_memalign((void**)&rand_z2, 32, sizeof(float) * NUM_ITERATIONS) != 0)
        exit(EXIT_FAILURE);

    generate_random_data(NUM_ITERATIONS);

    benchmark_vec3();
    benchmark_vec8();
    benchmark_vec4();

    free(rand_x1);
    free(rand_y1);
    free(rand_z1);
    free(rand_x2);
    free(rand_y2);
    free(rand_z2);

    return 0;
}
