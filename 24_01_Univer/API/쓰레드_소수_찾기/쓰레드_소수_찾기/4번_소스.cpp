//#include <windows.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//
//typedef struct tmp {
//    DWORD end;
//    DWORD Tnum;
//    DWORD TTtalnum;
//}tp;
//
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
//DWORD WINAPI prime(LPVOID param) {
//    tp* num = (tp*)param; // LPVOID를 int로 변환
//    int count = 0;
//    for (DWORD i = num->Tnum; i < num->end; i += num->TTtalnum) {
//        if (is_prime(i)) {
//            count++;
//        }
//    }
//    return count;
//}
//
//int makethread(HANDLE* hThreads, DWORD* threadIds, DWORD tnum, tp* param, int* results) {
//
//    clock_t start, end;
//    start = clock();
//    for (DWORD i = 0; i < tnum; i++) {
//        hThreads[i] = CreateThread(
//            NULL,               // 기본 보안 속성
//            0,                  // 기본 스택 크기
//            prime,              // 스레드 함수
//            &param[i],          // 스레드 함수에 전달할 매개 변수
//            0,                  // 기본 생성 플래그
//            &threadIds[i]       // 스레드 ID를 받을 포인터
//        );
//
//        if (hThreads[i] == NULL) {
//            _tprintf(_T("Error creating thread %d. Error code: %lu\n"), i, GetLastError());
//            return 1;
//        }
//    }
//
//    // 모든 스레드가 종료될 때까지 대기
//    WaitForMultipleObjects(tnum, hThreads, TRUE, INFINITE);
//
//    // 각 스레드의 종료 코드 얻기
//    for (DWORD i = 0; i < tnum; i++) {
//        DWORD exitCode;
//        if (GetExitCodeThread(hThreads[i], &exitCode)) {
//            results[i] = exitCode;
//        }
//        else {
//            _tprintf(_T("Error getting exit code for thread %d. Error code: %lu\n"), i, GetLastError());
//        }
//        CloseHandle(hThreads[i]);
//    }
//    end = clock();
//    printf("%d 개의 쓰레드 활용 시간 : %f \n", tnum, (float)(end - start) / CLOCKS_PER_SEC);
//    return 0;
//}
//
//int _tmain() {
//    HANDLE hThreads[32];
//    DWORD threadIds[32];
//    int results[32] = { 0 };
//
//    tp* t1 = (tp*)malloc(sizeof(tp) * 1);
//    tp* t2 = (tp*)malloc(sizeof(tp) * 2);
//    tp* t3 = (tp*)malloc(sizeof(tp) * 4);
//    tp* t4 = (tp*)malloc(sizeof(tp) * 8);
//    tp* t5 = (tp*)malloc(sizeof(tp) * 16);
//    tp* t6 = (tp*)malloc(sizeof(tp) * 32);
//
//    t1->end = 1000000;
//    t1->Tnum = 0;
//    t1->TTtalnum = 1;
//
//    for (int i = 0; i < 2; i++) {
//        t2[i].end = 1000000;
//        t2[i].Tnum = i;
//        t2[i].TTtalnum = 2;
//    }
//    for (int i = 0; i < 4; i++) {
//        t3[i].end = 1000000;
//        t3[i].Tnum = i;
//        t3[i].TTtalnum = 4;
//    }
//    for (int i = 0; i < 8; i++) {
//        t4[i].end = 1000000;
//        t4[i].Tnum = i;
//        t4[i].TTtalnum = 8;
//    }
//    for (int i = 0; i < 16; i++) {
//        t5[i].end = 1000000;
//        t5[i].Tnum = i;
//        t5[i].TTtalnum = 16;
//    }
//    for (int i = 0; i < 32; i++) {
//        t6[i].end = 1000000;
//        t6[i].Tnum = i;
//        t6[i].TTtalnum = 32;
//    }
//
//    makethread(hThreads, threadIds, 1, t1, results);
//    int totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//    printf("Total prime numbers found: %d\n", totalPrimes);
//    makethread(hThreads, threadIds, 2, t2, results);
//    totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//    printf("Total prime numbers found: %d\n", totalPrimes);
//    makethread(hThreads, threadIds, 4, t3, results);
//    totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//    printf("Total prime numbers found: %d\n", totalPrimes);
//    makethread(hThreads, threadIds, 8, t4, results);
//    totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//    printf("Total prime numbers found: %d\n", totalPrimes);
//    makethread(hThreads, threadIds, 16, t5, results);
//    totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//    printf("Total prime numbers found: %d\n", totalPrimes);
//    makethread(hThreads, threadIds, 32, t6, results);
//
//    totalPrimes = 0;
//    for (int i = 0; i < 32; i++) {
//        totalPrimes += results[i];
//    }
//
//    printf("Total prime numbers found: %d\n", totalPrimes);
//
//    free(t1);
//    free(t2);
//    free(t3);
//    free(t4);
//    free(t5);
//    free(t6);
//
//    return 0;
//}