// 파일명: chat.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>

#define MAX_BUF 4096
#define NAME_LEN 20
#define MAX_CLIENTS 10

// 메시지 타입 정의
enum {
    MSG_JOIN,       // 입장
    MSG_NORMAL,     // 일반 대화
    MSG_WHISPER,    // 귓속말
    MSG_LIST,       // 리스트 요청/응답
    MSG_FILE_START, // 파일 전송 시작
    MSG_FILE_DATA,  // 파일 데이터
    MSG_FILE_END    // 파일 전송 끝
};

// 통신 프로토콜 구조체
typedef struct {
    int type;                 // 메시지 타입
    char source[NAME_LEN];    // 보낸 사람 이름
    char target[NAME_LEN];    // 받는 사람 이름 (귓속말/파일용)
    int data_len;             // 데이터 길이 (파일 전송 시 유효)
    char data[MAX_BUF];       // 실제 메시지 또는 파일 청크
} Packet;