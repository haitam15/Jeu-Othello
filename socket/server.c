#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKET csock;
    SOCKADDR_IN sin;
    SOCKADDR_IN csin;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(3131);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    listen(sock, 1);
    printf("listen\n");
    int sinsize = sizeof(csin);
    csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
    printf("connect\n");
    char txt[10]="haitam";
    send(csock,txt,10*sizeof(char),0);
    closesocket(csock);
    closesocket(sock);
    WSACleanup();
    return 0;
}