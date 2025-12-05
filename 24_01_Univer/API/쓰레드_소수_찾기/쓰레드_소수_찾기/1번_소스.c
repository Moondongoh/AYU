//#include <windows.h>
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//
//typedef struct {
//    DWORD end;
//    DWORD start;
//    DWORD step;
//} ThreadArgs;
//
//volatile LONG total_prime_count = 0; // 전역 변수
//
//// 소수 여부를 판별하는 함수
//int is_prime(long long num) {
//    if (num <= 1) return 0;
//    if (num == 2) return 1;
//    if (num % 2 == 0) return 0;
//    for (long long i = 3; i <= sqrt(num); i += 2) {
//        if (num % i == 0) return 0;
//    }
//    return 1;
//}
//
//// 각 스레드에서 실행할 함수
//DWORD WINAPI prime_count(LPVOID param) {
//    ThreadArgs* args = (ThreadArgs*)param;
//    int count = 0;
//    for (DWORD i = args->start; i <= args->end; i += args->step) {
//        if (is_prime(i)) {
//            count++;
//        }
//    }
//    InterlockedAdd(&total_prime_count, count); // 전역 변수에 누적
//    return 0;
//}
//
//int main() {
//    const long long n = 1000000; // 범위의 상한
//    int thread_counts[] = { 1, 4, 8, 16, 32 }; // 스레드 개수 배열
//    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]); // 배열 길이
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    ThreadArgs args[32];
//
//    for (int i = 0; i < num_configs; i++) {
//        int num_threads = thread_counts[i]; // 현재 설정된 스레드 개수
//        clock_t start, end;
//        start = clock();
//        total_prime_count = 0; // 초기화
//
//        for (int t = 0; t < num_threads; t++) {
//            args[t].start = t + 1;
//            args[t].end = n;
//            args[t].step = num_threads;
//            hThreads[t] = CreateThread(NULL, 0, prime_count, &args[t], 0, &threadIds[t]);
//            if (hThreads[t] == NULL) {
//                printf("스레드 %d 생성 중 오류 발생. 오류 코드: %lu\n", t, GetLastError());
//                return 1;
//            }
//        }
//
//        // 모든 스레드의 완료를 대기
//        WaitForMultipleObjects(num_threads, hThreads, TRUE, INFINITE);
//
//        // 스레드 핸들을 닫음
//        for (int t = 0; t < num_threads; t++) {
//            CloseHandle(hThreads[t]);
//        }
//
//        end = clock();
//        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
//        printf("스레드 개수: %d, 소요 시간: %f 초, 찾은 소수 개수: %ld\n", num_threads, total_time, total_prime_count);
//    }
//
//    return 0;
//}
