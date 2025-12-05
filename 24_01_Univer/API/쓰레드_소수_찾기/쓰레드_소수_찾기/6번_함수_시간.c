//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//
//int num;
//
//// 효율적인 소수 판별 함수
//int is_prime_simple(long long num) {
//    if (num <= 1) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//    for (long long i = 3; i <= sqrt(num); i += 2) {
//        if (num % i == 0) return 0;
//    }
//    return 1;
//}
//
//// 비효율적인 소수 판별 함수
//int is_prime_complex(long long num) {
//    if (num < 2) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//
//    for (long long i = 3; i <= num / 2; i += 2) {
//        if (num % i == 0) return 0;
//    }
//
//    return 1;
//}
//
//int main() {
//    printf("숫자 입력 : ");
//    scanf("%d", &num);
//    printf("입력된 숫자 : %d\n", num);
//
//    clock_t start, end;
//    double cpu_time_used;
//
//    // 효율적인 소수 판별 함수의 실행 시간 측정
//    start = clock();
//    int simple_count = 0;
//    for (long long i = 2; i <= num; i++) {
//        if (is_prime_simple(i)) {
//            simple_count++;
//        }
//    }
//    end = clock();
//    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("is_prime_simple 함수 실행 시간: %f 초\n", cpu_time_used);
//    printf("is_prime_simple 소수 개수: %d\n", simple_count);
//
//    // 비효율적인 소수 판별 함수의 실행 시간 측정
//    start = clock();
//    int complex_count = 0;
//    for (long long i = 2; i <= num; i++) {
//        if (is_prime_complex(i)) {
//            complex_count++;
//        }
//    }
//    end = clock();
//    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("is_prime_complex 함수 실행 시간: %f 초\n", cpu_time_used);
//    printf("is_prime_complex 소수 개수: %d\n", complex_count);
//
//    return 0;
//}
