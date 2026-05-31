#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	//Сервер для прийому файлу через UDP
    SetConsoleOutputCP(1251);
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    cout << "Сервер чекає...\n";
    ofstream file("received.rtf", ios::binary);
    char buffer[1024];
    int bytes;
    sockaddr_in clientAddr{};
    int clientSize = sizeof(clientAddr);
    while (true) {
        bytes = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
            (sockaddr*)&clientAddr, &clientSize);
        if (bytes <= 0) break;
        file.write(buffer, bytes);
        // умовне завершення 
        if (bytes < 1024) break;
    }
    cout << "Файл отримано\n";
    file.close();
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
