////#include <stdio.h>
////#include <stdlib.h>
////#include <windows.h>
////#include <time.h>
////#include <math.h>
////
////// 구조체 정의
////typedef struct {
////    long long start;
////    long long end;
////    long long step;
////} ThreadArgs;
////
////int count = 0;
////
////// 임계 구역 변수 선언
////CRITICAL_SECTION cs;
////
////// 소수 판별 함수
////int is_prime(long long num) {
////    if (num <= 1) return 0;
////    if (num == 2) return 1;
////    if (num % 2 == 0) return 0;
////    for (long long i = 3; i <= sqrt(num); i += 2) {
////        if (num % i == 0) return 0;
////    }
////    return 1;
////}
////
////// 스레드 함수
////DWORD WINAPI prime_count(LPVOID lpParam) {
////    ThreadArgs* args = (ThreadArgs*)lpParam;
////
////    // 임계 구역 설정
////    EnterCriticalSection(&cs);
////
////    // 소수 찾기
////    for (long long i = args->start; i <= args->end; i += args->step) {
////        if (is_prime(i)) {
////            count++;
////        }
////    }
////
////    // 임계 구역 해제
////    LeaveCriticalSection(&cs);
////
////    // 스레드 종료
////    return count;
////}
////
////int main() {
////    int num_threads[] = { 1, 4, 8, 16, 32 };
////    int num = 1000000;
////    HANDLE hThreads[32];
////    DWORD threadIds[32];
////    ThreadArgs args[32];
////    int results[32] = { 0 };
////    clock_t start, end;
////
////    // 임계 구역 초기화
////    InitializeCriticalSection(&cs);
////
////    // 각 스레드 수에 따라 소수 찾기 및 시간 측정
////    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); ++i) {
////        int tnum = num_threads[i];
////        start = clock();
////
////        for (int j = 0; j < tnum; ++j) {
////            args[j].start = j + 1;
////            args[j].end = num;
////            args[j].step = tnum;
////            hThreads[j] = CreateThread(NULL, 0, prime_count, &args[j], 0, &threadIds[j]);
////            if (hThreads[j] == NULL) {
////                printf("Error creating thread %d. Error code: %lu\n", j, GetLastError());
////                return 1;
////            }
////        }
////
////        // 스레드가 모두 종료될 때까지 대기
////        WaitForMultipleObjects(tnum, hThreads, TRUE, INFINITE);
////
////        // 각 스레드의 결과 얻기
////        for (int j = 0; j < tnum; ++j) {
////            DWORD exitCode;
////            if (GetExitCodeThread(hThreads[j], &exitCode)) {
////                results[j] = exitCode;
////            }
////            else {
////                printf("Error getting exit code for thread %d. Error code: %lu\n", j, GetLastError());
////            }
////            CloseHandle(hThreads[j]);
////        }
////
////        end = clock();
////        printf("%d 개의 쓰레드 활용 시간 : %f 초 %d개\n", tnum, (double)(end - start) / CLOCKS_PER_SEC, count);
////        count = 0;
////    }
////
////    // 임계 구역 삭제
////    DeleteCriticalSection(&cs);
////
////    return 0;
////}
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <time.h>
//#include <math.h>
//
//// 구조체 정의
//typedef struct {
//    long long start;
//    long long end;
//    long long step;
//} ThreadArgs;
//
//int count = 0;
//
//// 임계 구역 변수 선언
//CRITICAL_SECTION cs;
//
//// 비효율적인 소수 판별 함수
//int is_prime(long long num) {
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
//// 스레드 함수
//DWORD WINAPI prime_count(LPVOID lpParam) {
//    ThreadArgs* args = (ThreadArgs*)lpParam;
//
//    for (long long i = args->start; i <= args->end; i += args->step) {
//        if (is_prime(i)) {
//            EnterCriticalSection(&cs);
//            count++;
//            LeaveCriticalSection(&cs);
//        }
//    }
//
//    // 스레드 종료
//    return 0;
//}
//
//int main() {
//    int num_threads[] = { 1, 4, 8, 16, 32 };
//    int num = 1000000;
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    ThreadArgs args[32];
//    int results[32] = { 0 };
//    clock_t start, end;
//
//    // 임계 구역 초기화
//    InitializeCriticalSection(&cs);
//
//    // 각 스레드 수에 따라 소수 찾기 및 시간 측정
//    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); ++i) {
//        int tnum = num_threads[i];
//        start = clock();
//
//        for (int j = 0; j < tnum; ++j) {
//            args[j].start = j + 1;
//            args[j].end = num;
//            args[j].step = tnum;
//            hThreads[j] = CreateThread(NULL, 0, prime_count, &args[j], 0, &threadIds[j]);
//            if (hThreads[j] == NULL) {
//                printf("Error creating thread %d. Error code: %lu\n", j, GetLastError());
//                return 1;
//            }
//        }
//
//        // 스레드가 모두 종료될 때까지 대기
//        WaitForMultipleObjects(tnum, hThreads, TRUE, INFINITE);
//
//        // 각 스레드의 결과 얻기
//        for (int j = 0; j < tnum; ++j) {
//            DWORD exitCode;
//            if (GetExitCodeThread(hThreads[j], &exitCode)) {
//                results[j] = exitCode;
//            }
//            else {
//                printf("Error getting exit code for thread %d. Error code: %lu\n", j, GetLastError());
//            }
//            CloseHandle(hThreads[j]);
//        }
//
//        end = clock();
//        printf("%d 개의 쓰레드 활용 시간 : %f 초 %d개\n", tnum, (double)(end - start) / CLOCKS_PER_SEC, count);
//        count = 0;
//    }
//
//    // 임계 구역 삭제
//    DeleteCriticalSection(&cs);
//
//    return 0;
//}