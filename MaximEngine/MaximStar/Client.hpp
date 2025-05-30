#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>

enum UserMessage {
    USER_MESSAGE_RESIZE = WM_USER + 1,
    USER_MESSAGE_QUIT,
    USER_MESSAGE_MOUSE_CLICK,
    USER_MESSAGE_MOUSE_MOVE,
    USER_MESSAGE_MOUSE_WHEEL,
    USER_MESSAGE_SERVER_ON
  };

class Client {

public:

    SOCKET clientSocket;
    HWND hWnd;
    
    bool connectServer(HWND hwnd)
    {

        hWnd = hwnd;
            //WSAStartup
        WSADATA wsaData;
        int wserr;
        WORD wVersionRequested = MAKEWORD(2,2);
        wserr = WSAStartup(wVersionRequested, &wsaData);
        if(wserr != 0){
            //cout << "The winsock dll not found" << endl;
            return 0;
        } else {
            //cout << "The Winsock dll found" << endl;
            //cout << "The status: "<< wsaData.szSystemStatus << endl;
        }

        //socket creation
        
        clientSocket = INVALID_SOCKET;
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(clientSocket == INVALID_SOCKET){
            //cout << "Error at socket(): " << WSAGetLastError() << endl;
            WSACleanup();
            return 0;
        } else {
            //cout << "socket is OK!" << endl;
        }

        //connection to server
        sockaddr_in clientService;
        clientService.sin_family = AF_INET;
        clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
        clientService.sin_port = htons(55555);
        if(connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
            //cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << endl;
            WSACleanup();
            return 0;
        } else {
            //cout << "Client: Connect() is OK!" << endl;
            //cout << "Client: Can start sending and receiving data..." << endl;
        }

        std::thread* a = new std::thread(&Client::waitM, this);   
        
        return true;
    }; 

    void waitM(){

        bool test = true;

        while(test)
        {
            //receiving messages
            char receiveBuffer[200];
            int byteCount = recv(clientSocket, receiveBuffer, 200, 0);
            if(byteCount < 0){
            //     cout << "Server recv error: " << WSAGetLastError() << endl;
                 test = false;
             } else {
            //     cout << "Received data: " << receiveBuffer << endl;
           
                
                char* str = new char[200];
                strcpy_s(str, 200, receiveBuffer);
                // Send the message with the string pointer in lParam
                PostMessage(hWnd, USER_MESSAGE_SERVER_ON, 0, reinterpret_cast<LPARAM>(str));
                }
            
        }
    }

    bool IsWindowFocused(HWND hwnd) {
        // Get the handle of the currently focused (foreground) window
        HWND foregroundWindow = GetForegroundWindow();
        return hwnd == foregroundWindow;
    }
    
    bool sendMsg(char* msg)
    {
        //sending data
        //char buffer[5] = {'a','l','l','o', '\0'};
        //printf("Enter the message: ");
        //cin.getline(buffer,200);
        if(IsWindowFocused(hWnd))
        {
            int sbyteCount = send(clientSocket, msg, 200, 0);
            if(sbyteCount == SOCKET_ERROR){
                //cout << "Server send error: " << WSAGetLastError() << endl;
                return 1;
            } else {
                //cout << "Server: sent" << sbyteCount << endl;
            }
        }
        return 0;
    }
    
};

#endif