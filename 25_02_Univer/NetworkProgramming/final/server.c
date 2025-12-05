// 파일명: server.c
#include "chat.h"

// 클라이언트 정보 구조체
typedef struct {
    int sock;
    char name[NAME_LEN];
} Client;

Client clients[MAX_CLIENTS];
int num_chat = 0;

int getmax(int k) {
    int max = k;
    for (int i = 0; i < num_chat; i++) {
        if (clients[i].sock > max) max = clients[i].sock;
    }
    return max;
}

void removeClient(int i) {
    close(clients[i].sock);
    // 배열 당기기
    for (int j = i; j < num_chat - 1; j++) {
        clients[j] = clients[j + 1];
    }
    num_chat--;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int listen_sock, accp_sock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t addrlen = sizeof(cliaddr);
    fd_set read_fds;
    Packet packet;

    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind fail"); exit(1);
    }
    listen(listen_sock, 5);

    printf("Server started on port %s...\n", argv[1]);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(listen_sock, &read_fds);
        for (int i = 0; i < num_chat; i++) FD_SET(clients[i].sock, &read_fds);

        int maxfd = getmax(listen_sock) + 1;
        if (select(maxfd, &read_fds, NULL, NULL, NULL) < 0) continue;

        // 1. 새로운 연결 요청 처리
        if (FD_ISSET(listen_sock, &read_fds)) {
            accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen);
            if (num_chat < MAX_CLIENTS) {
                clients[num_chat].sock = accp_sock;
                // 이름은 나중에 JOIN 패킷으로 받음
                num_chat++;
                printf("New connection (socket %d)\n", accp_sock);
            } else {
                close(accp_sock); // 꽉 찼으면 끊음
            }
        }

        // 2. 클라이언트 메시지 처리
        for (int i = 0; i < num_chat; i++) {
            if (FD_ISSET(clients[i].sock, &read_fds)) {
                int n = recv(clients[i].sock, &packet, sizeof(Packet), 0);
                if (n <= 0) {
                    printf("Client %s disconnected\n", clients[i].name);
                    removeClient(i);
                    i--; // 인덱스 보정
                    continue;
                }

                // 패킷 처리 로직
                // [server.c 파일 중간 MSG_JOIN 부분]

                // ... (생략)
                if (packet.type == MSG_JOIN) {
                    
                    // 1. 이름 끝에 붙은 엔터(\n) 제거 (가장 중요!)
                    int len = strlen(packet.source);
                    if (len > 0 && packet.source[len - 1] == '\n') {
                        packet.source[len - 1] = '\0'; 
                    }

                    // 2. 서버 메모리에 이름 저장
                    strcpy(clients[i].name, packet.source);
                    printf("[DEBUG] User Saved: index=%d, name=%s\n", i, clients[i].name); // 서버 확인용 로그

                    // 3. 입장 알림 브로드캐스트
                    Packet noti;
                    noti.type = MSG_NORMAL;
                    strcpy(noti.source, "SERVER"); // <--- [수정] 이게 없어서 []로 떴던 겁니다!
                    sprintf(noti.data, ">>> [Notice] %s joined the chat.", packet.source);
                    
                    for(int j=0; j<num_chat; j++) send(clients[j].sock, &noti, sizeof(Packet), 0);


                } else if (packet.type == MSG_LIST) {
                    // 리스트 요청 처리
                    Packet list_pkt;
                    list_pkt.type = MSG_LIST;
                    strcpy(list_pkt.data, "--- User List ---\n");
                    for(int j=0; j<num_chat; j++) {
                        strcat(list_pkt.data, clients[j].name);
                        strcat(list_pkt.data, "\n");
                    }
                    send(clients[i].sock, &list_pkt, sizeof(Packet), 0);

                } else if (packet.type == MSG_WHISPER) {
                    // 귓속말 처리
                    int target_found = 0;
                    for (int j = 0; j < num_chat; j++) {
                        if (strcmp(clients[j].name, packet.target) == 0) {
                            send(clients[j].sock, &packet, sizeof(Packet), 0);
                            target_found = 1;
                            break;
                        }
                    }
                    if (!target_found) {
                        sprintf(packet.data, "User '%s' not found.", packet.target);
                        packet.type = MSG_NORMAL;
                        send(clients[i].sock, &packet, sizeof(Packet), 0);
                    }

                } else if (packet.type == MSG_FILE_START || packet.type == MSG_FILE_DATA || packet.type == MSG_FILE_END) {
                     // 파일 전송 중계 (대상에게 전달)
                    for (int j = 0; j < num_chat; j++) {
                        if (strcmp(clients[j].name, packet.target) == 0) {
                            send(clients[j].sock, &packet, n, 0); // 받은 크기만큼 그대로 전송
                            break;
                        }
                    }
                } else {
                    // 일반 메시지 브로드캐스트 (자신 제외)
                    for (int j = 0; j < num_chat; j++) {
                        // if (i != j) send(clients[j].sock, &packet, sizeof(Packet), 0); 
                        // 채팅방은 보통 나에게도 보여지거나 서버가 뿌려줌. 여기선 모두에게 전송
                        send(clients[j].sock, &packet, sizeof(Packet), 0);
                    }
                }
            }
        }
    }
    return 0;
}