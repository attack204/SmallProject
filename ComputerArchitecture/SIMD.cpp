#include <stdio.h>
#include <emmintrin.h>
#include <iostream>
#include <ctime>
#define N 100000000
int a[N], b[N], c[N];

void add_sse2(int size, int *a, int *b, int *c) {
    int i = 0;
    for (; i + 4 < size; i += 4) {
        /* 加载 a, b 数组的 128 位块 */
        __m128i ma = _mm_loadu_si128((__m128i*) &a[i]);
        __m128i mb = _mm_loadu_si128((__m128i*) &b[i]);

        /* 128 位块矢量相加 */
        ma = _mm_add_epi32(ma, mb);

        /* 将相加结果存储到 c 数组的 128 位块 */
        _mm_storeu_si128((__m128i*) &c[i], ma);
    }
}
void add(int size, int *a, int *b, int *c) {
    for(int i = 0; i < size; i++) {
    	c[i] = a[i] + b[i];
    }
}

int main()
{
    for (int i = 0; i < N; i++) {
	a[i] = i;
	b[i] = i << 1;
    }
    clock_t start = clock();
    add(N, a, b, c);
    double elapsedTime = clock();
    std::cout << "NO-SIMD cost: " << static_cast<double> (elapsedTime - start) / CLOCKS_PER_SEC  << std::endl;
    add_sse2(N, a, b, c);
    double elapsedTime2 = static_cast<double>(clock() - elapsedTime) / CLOCKS_PER_SEC;
    std::cout << "SIMD cost: " << elapsedTime2 << '\n';
}