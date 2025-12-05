#include "chat.h"

int sock;
char my_name[NAME_LEN];
char saved_filename[100]; // 파일 이름 저장용 전역 변수

// 파일 전송 함수
void send_file(char *target, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error: File not found.\n");
        return;
    }

    Packet pkt;
    strcpy(pkt.source, my_name);
    strcpy(pkt.target, target);

    // 1. 시작 알림
    pkt.type = MSG_FILE_START;
    strcpy(pkt.data, filename); // 데이터 영역에 파일명 담아서 보냄
    send(sock, &pkt, sizeof(Packet), 0);
    printf("[File] Sending %s to %s...\n", filename, target);

    // 2. 데이터 전송
    pkt.type = MSG_FILE_DATA;
    while ((pkt.data_len = fread(pkt.data, 1, MAX_BUF, fp)) > 0) {
        send(sock, &pkt, sizeof(Packet), 0);
        usleep(1000); // 전송 속도 조절 (패킷 뭉침 방지)
    }

    // 3. 종료 알림
    pkt.type = MSG_FILE_END;
    send(sock, &pkt, sizeof(Packet), 0);
    printf("[File] Transfer complete.\n");
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <server_ip> <port> <name>\n", argv[0]);
        exit(1);
    }

    strcpy(my_name, argv[3]);
    struct sockaddr_in servaddr;
    fd_set read_fds;
    Packet pkt;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect fail"); exit(1);
    }

    // 입장 패킷 전송
    pkt.type = MSG_JOIN;
    strcpy(pkt.source, my_name);
    send(sock, &pkt, sizeof(Packet), 0);

    printf("=== Chat Room Joined ===\n");
    printf("Commands: /list, /w <user> <msg>, /file <user> <filename>\n");

    FILE *recv_fp = NULL; // 파일 수신용 포인터

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);    // 키보드 입력
        FD_SET(sock, &read_fds); // 서버 수신

        if (select(sock + 1, &read_fds, NULL, NULL, NULL) < 0) break;

        // 1. 서버로부터 메시지 수신
        if (FD_ISSET(sock, &read_fds)) {
            int n = recv(sock, &pkt, sizeof(Packet), 0);
            if (n <= 0) break;

            if (pkt.type == MSG_NORMAL) {
                printf("[%s] %s\n", pkt.source, pkt.data);
            } else if (pkt.type == MSG_WHISPER) {
                printf("(Whisper from %s): %s\n", pkt.source, pkt.data);
            } else if (pkt.type == MSG_LIST) {
                printf("%s", pkt.data);
            } else if (pkt.type == MSG_FILE_START) {
                printf("Receiving file '%s' from %s...\n", pkt.data, pkt.source);
                
                // 파일 이름을 미리 저장
                strcpy(saved_filename, pkt.data); 
                
                char new_filename[100];
                sprintf(new_filename, "recv_%s", saved_filename); 
                recv_fp = fopen(new_filename, "wb");

            } else if (pkt.type == MSG_FILE_DATA) {
                if (recv_fp) fwrite(pkt.data, 1, pkt.data_len, recv_fp);

            } else if (pkt.type == MSG_FILE_END) {
                if (recv_fp) {
                    fclose(recv_fp);
                    recv_fp = NULL;
                    printf("File saved: recv_%s\n", saved_filename);

                    // 저장해둔 이름(saved_filename)을 사용해서 재생
                    char cmd[200];
                    
                    // [재생 명령] 리눅스 기본 실행 (xdg-open)
                    sprintf(cmd, "xdg-open recv_%s &", saved_filename);
                    system(cmd); 
                }
            }
        }

        // 2. 키보드 입력 처리
        if (FD_ISSET(0, &read_fds)) {
            char buf[MAX_BUF];
            fgets(buf, MAX_BUF, stdin);
            buf[strlen(buf) - 1] = 0; // 엔터 제거

            if (strlen(buf) == 0) continue;

            if (strcmp(buf, "/list") == 0) {
                pkt.type = MSG_LIST;
                send(sock, &pkt, sizeof(Packet), 0);
            } else if (strncmp(buf, "/w ", 3) == 0) {
                char *cmd = strtok(buf, " ");
                char *target = strtok(NULL, " ");
                char *msg = strtok(NULL, "");
                if (target && msg) {
                    pkt.type = MSG_WHISPER;
                    strcpy(pkt.source, my_name);
                    strcpy(pkt.target, target);
                    strcpy(pkt.data, msg);
                    send(sock, &pkt, sizeof(Packet), 0);
                } else {
                    printf("Usage: /w <user> <message>\n");
                }
            } else if (strncmp(buf, "/file ", 6) == 0) {
                char *cmd = strtok(buf, " ");
                char *target = strtok(NULL, " ");
                char *fname = strtok(NULL, " ");
                if (target && fname) {
                    send_file(target, fname);
                } else {
                    printf("Usage: /file <user> <filename>\n");
                }
            } else {
                // 일반 대화
                pkt.type = MSG_NORMAL;
                strcpy(pkt.source, my_name);
                strcpy(pkt.data, buf);
                send(sock, &pkt, sizeof(Packet), 0);
            }
        }
    }
    close(sock);
    return 0;
}