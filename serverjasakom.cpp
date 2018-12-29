#include <iostream>
#include <cstdlib>
#include <winsock.h>
#include <windows.h>
using namespace std;
WSADATA wsa;
SOCKET sock;
bool bListenOnPort(int nNoPort);
void CloseConnection();
int main()
{
int nPort =123457 ;
bool bStatus;
SOCKET sAcc;

bStatus = bListenOnPort(nPort);
if(bStatus== false){
    cout<<"Listerning pada port "<<nPort<<" gagal";
}
else{
    cout<<"Listerning pada port "<<nPort<<" berhasil";
}
sAcc = accept(sock,NULL,NULL);
if(sAcc = INVALID_SOCKET){
    cout<<"Tidak dapat Menerima Koneksi";
}else{
    while(true){
        Sleep(100);
        char szMessage[1024]={'\0'};
        SOCKET sRcv;
        sRcv =recv(sAcc,szMessage,1024,0);
        if(sRcv==INVALID_SOCKET){
            cout << "Gagal Menerima Data !!" <<endl;
            return false;
        }
        else{
            cout <<"data> " <<szMessage<<endl;
        }
    }
}
system("pause");
CloseConnection();
    return EXIT_SUCCESS;
}
bool bListenOnPort(int nNoPort){
    int error = WSAStartup(0x0202, &wsa);

    if(error){
        return FALSE;
    }

    if(wsa.wVersion != 0x0202){
        WSACleanup();
        return FALSE;
    }
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port= htons(nNoPort);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

    if(sock==INVALID_SOCKET){
        return FALSE;
    }
    if(bind(sock,(LPSOCKADDR) &addr,sizeof(addr))==SOCKET_ERROR){
        return FALSE;
    }
    listen(sock,SOMAXCONN);

}
void CloseConnection(){
    if(sock){
        closesocket(sock);
    }
    WSACleanup();
}
