//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <windows.h>
//#include <time.h>
//
//#define CHUNK_SIZE 250000
//
//typedef struct {
//    long long start;
//    long long end;
//    int prime_count;
//} ThreadData;
//
//int global_prime_count_atomic = 0;
//int global_prime_count_critical = 0;
//int global_prime_count_unsynced = 0;
//CRITICAL_SECTION critical_section;
//
//// 소수 판별 함수
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
//// 스레드 함수 (전역 변수에 원자적으로 접근)
//DWORD WINAPI count_primes_atomic(LPVOID arg) {
//    ThreadData* data = (ThreadData*)arg;
//    data->prime_count = 0;
//    for (long long i = data->start; i <= data->end; i++) {
//        if (is_prime(i)) {
//            data->prime_count++;
//        }
//    }
//    InterlockedAdd(&global_prime_count_atomic, data->prime_count);
//    return 0;
//}
//
//// 스레드 함수 (임계 구역을 사용하여 전역 변수에 접근)
//DWORD WINAPI count_primes_critical(LPVOID arg) {
//    ThreadData* data = (ThreadData*)arg;
//    data->prime_count = 0;
//    for (long long i = data->start; i <= data->end; i++) {
//        if (is_prime(i)) {
//            data->prime_count++;
//        }
//    }
//    EnterCriticalSection(&critical_section);
//    global_prime_count_critical += data->prime_count;
//    LeaveCriticalSection(&critical_section);
//    return 0;
//}
//
//// 스레드 함수 (동기화 없이 전역 변수에 접근)
//DWORD WINAPI count_primes_unsynced(LPVOID arg) {
//    ThreadData* data = (ThreadData*)arg;
//    data->prime_count = 0;
//    for (long long i = data->start; i <= data->end; i++) {
//        if (is_prime(i)) {
//            data->prime_count++;
//        }
//    }
//    global_prime_count_unsynced += data->prime_count; // 동기화 없음
//    return 0;
//}
//
//void run_prime_count(long long start_range, long long end_range, int num_threads,
//    DWORD(WINAPI* thread_func)(LPVOID), const char* method_name, int* global_prime_count) {
//
//    long long total_numbers = end_range - start_range + 1;
//    long long chunk_size = (total_numbers + num_threads - 1) / num_threads;
//
//    HANDLE* threads = (HANDLE*)malloc(num_threads * sizeof(HANDLE));
//    ThreadData* thread_data = (ThreadData*)malloc(num_threads * sizeof(ThreadData));
//
//    *global_prime_count = 0;
//
//    clock_t start_time = clock();
//    for (int i = 0; i < num_threads; i++) {
//        thread_data[i].start = start_range + i * chunk_size;
//        thread_data[i].end = (i == num_threads - 1) ? end_range : (start_range + (i + 1) * chunk_size - 1);
//        threads[i] = CreateThread(NULL, 0, thread_func, &thread_data[i], 0, NULL);
//    }
//    WaitForMultipleObjects(num_threads, threads, TRUE, INFINITE);
//    clock_t end_time = clock();
//    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//
//    printf("%s - 쓰레드 수: %d, 소수 갯수: %d, 걸린 시간: %f seconds\n", method_name, num_threads, *global_prime_count, time_taken);
//
//    free(threads);
//    free(thread_data);
//}
//
//int main() {
//    long long start_range, end_range;
//    int thread_counts[] = { 1, 4, 8, 16, 32 };
//
//    printf("시작 수: ");
//    scanf("%lld", &start_range);
//    printf("마지막 수: ");
//    scanf("%lld", &end_range);
//
//    InitializeCriticalSection(&critical_section);
//
//    for (int i = 0; i < sizeof(thread_counts) / sizeof(thread_counts[0]); i++) {
//        int num_threads = thread_counts[i];
//        run_prime_count(start_range, end_range, num_threads, count_primes_atomic, "Atomic", &global_prime_count_atomic);
//        run_prime_count(start_range, end_range, num_threads, count_primes_critical, "Critical", &global_prime_count_critical);
//        run_prime_count(start_range, end_range, num_threads, count_primes_unsynced, "Unsynced", &global_prime_count_unsynced);
//    }
//
//    DeleteCriticalSection(&critical_section);
//    return 0;
//}