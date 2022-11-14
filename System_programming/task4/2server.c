#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int sockfd;                           /* Дескриптор сокета */
    int clilen, n;                        /* Переменные для различных длин и количества символов */
    char line[1000];                      /* Массив для принятой и отсылаемой строки */
    struct sockaddr_in servaddr, cliaddr; /* Структуры для адресов сервера и клиента */
    /* Заполняем структуру для адреса сервера */
    if (argc != 2) {
        printf("Usage: a.out <port>\n");
        exit(1);
    }
    int port = atoi(argv[1]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Создаем UDP сокет */
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }
    /* Настраиваем адрес сокета */
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    while (1) {
        /* Основной цикл обслуживания*/
        clilen = sizeof(cliaddr);
        /* Ожидаем прихода запроса от клиента и читаем его */
        if ((n = recvfrom(sockfd, line, 999, 0,
                          (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        /* Печатаем принятый текст на экране */
        printf("%s\n", line);
        bzero(line, 1000);
        printf("Ansver => ");
        fgets(line, 1000, stdin);
        /* Принятый текст отправляем обратно по адресу отправителя */
        if (sendto(sockfd, line, strlen(line), 0,
                   (struct sockaddr *)&cliaddr, clilen) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        } /* Уходим ожидать новую датаграмму*/
    }
    return 0;
}