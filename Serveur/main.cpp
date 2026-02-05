//Refer ServerCreation.md for detail infos

#include <iostream>
#include <vector>
#include <thread>

#ifdef VK_USE_PLATFORM_WIN32_KHR

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

using namespace std;

std::vector<thread*> listThreads;
std::vector<SOCKET> listSockets;

void sendS(int s, char ss[]);

void waitS(SOCKET acceptSocket, int i)
{
    bool sortie = true;

    while(sortie)
    {
        //6. (a) receiving data
        char receiveBuffer[200];
        int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
        
        if(rbyteCount < 0){
            
            sortie = false;
            cout << "Server recv error: " << WSAGetLastError() << endl;
        } else {
            
            cout << "Received data: " << receiveBuffer << endl;

            for(int i = 0; i < listSockets.size(); i++)
            {
                sendS(i, receiveBuffer);
            }
        }
    }
}

void sendS(int i, char msg[])
{
    //6. (b)  sending data
    //const char* buffer = msg.c_str();

    int sbyteCount = send(listSockets[i], msg, 200, 0);
    
    if(sbyteCount == SOCKET_ERROR){
    
        cout << "Server send error: " << WSAGetLastError() << endl;
        listSockets.erase(listSockets.begin() + i);        
    } 
    else {
    
        cout << "Server: sent" << sbyteCount << endl;
    }
}

int main(){
    //1. Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2,2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    //WSAStartup resturns 0 if it is successfull or non zero if failed
    if(wsaerr != 0){ 
        cout << "The Winsock dll not found!" << endl;
        return 0;
    } else  {
        cout << "The Winsock dll found" << endl;
        cout << "The status: "<< wsaData.szSystemStatus << endl;
    }

    /*
    refer ServerCreation.md
    */
    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET; //initializing as a inivalid socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //check if creating socket is successfull or not
    if(serverSocket == INVALID_SOCKET){
        cout << "Error at socket():"<< WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    } else {
        cout << "socket is OK!" << endl;
    }

    /*
    3. Bind the socket to ip address and port number
    //refer ServerCreation.md
    */
   sockaddr_in service; //initialising service as sockaddr_in structure
   service.sin_family = AF_INET;
   //InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr); 
   //InetPton function is encountering an issue, so replaced with the following line which uses inet_addr to convert IP address string to the binary form (only for ipv4) and storing it
   service.sin_addr.s_addr = inet_addr("127.0.0.1");
//    service.sin_addr.s_addr = inet_addr("192.168.43.42");
   service.sin_port = htons(55555);
   //using the bind function
   if(bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
    cout << "bind() failed: " << WSAGetLastError() << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 0;
   } else {
    cout << "bind() is OK!" << endl;
   }

   

    while(true)
    {
        //4. Listen to incomming connections
        if(listen(serverSocket, 1) == SOCKET_ERROR){
            cout << "listen(): Error listening on socket: " << WSAGetLastError() << endl;
        } else {
            cout << "listen() is OK!, I'm waiting for new connections..." << endl;
        }

        //5. accepting incomming connections
        SOCKET acceptSocket;

        acceptSocket = accept(serverSocket, NULL, NULL);
        if(acceptSocket == INVALID_SOCKET){
            cout << "accept failed: " << WSAGetLastError() << endl;
            WSACleanup();
            //return -1;
        } else {
            cout << "accept() is OK!" << endl;

            thread* t = new thread(waitS, acceptSocket, (int)listSockets.size());

            listSockets.push_back(acceptSocket);

            listThreads.push_back(t);
        }
    }
}

#endif