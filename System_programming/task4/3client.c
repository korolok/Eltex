#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int my_sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[500];

    printf("TCP DEMO CLIENT\n");
    if (argc != 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(1);
    }
    // извлечение порта
    portno = atoi(argv[2]);
    // Шаг 1 - создание сокета
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0)
        error("ERROR opening socket");
    // извлечение хоста
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(1);
    }
    // заполенние структуры serv_addr
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    // установка порта
    serv_addr.sin_port = htons(portno);
    // Шаг 2 - установка соединения
    if (connect(my_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    // Шаг 3 - чтение и передача сообщений
    for (int i = 0; i < 4; ++i) {
        n = recv(my_sock, buff, sizeof(buff) - 1, 0);
        if (n < 0) {
            printf("Recv error \n");
            close(my_sock);
            return 1;
        }
        // ставим завершающий ноль в конце строки
        buff[n] = 0;
        // выводим на экран
        printf("S=>C:%s", buff);
        if (i < 3) {
            // читаем пользовательский ввод с клавиатуры
            printf("S<=C:");
            fgets(buff, sizeof(buff) - 1, stdin);
            // передаем строку клиента серверу
            send(my_sock, buff, strlen(buff), 0);
        }
        bzero(buff, 500);
    }
    printf("disconnect...\n");
    close(my_sock);
    return 0;
}