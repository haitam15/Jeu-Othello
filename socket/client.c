#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(3131);
    connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    char txt[10]="vide";
    recv(sock,txt,sizeof(txt),0);
    printf("%s",txt);
    closesocket(sock);
    WSACleanup();
    return 0;
}