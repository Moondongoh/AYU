#include <stdio.h>
#include <math.h>
#include <time.h>

// 소수 판별 함수
int is_prime(long long num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (long long i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    const long long n = 1000000;
    int total_prime_count;
    clock_t start_time, end_time;

    // 소수 계산
    total_prime_count = 0;
    start_time = clock();
    for (long long j = 1; j <= n; j++) {
        if (is_prime(j)) {
            total_prime_count++;
        }
    }
    end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Total Prime Count: %d, Time Taken: %f seconds\n", total_prime_count, time_taken);

    return 0;
}
