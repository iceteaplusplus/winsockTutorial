#include <cstdlib>
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <string>
using namespace std;
WSADATA wsa;
SOCKET sock;

bool bConnection(char* pszAddress,int nNoPort);
void CloseConnection();
void shell (int socket);
int main(){
	int nPort =12345;
	bool bKondisi;

	bKondisi =bConnection("127.0.0.1",nPort);
	if(bKondisi==true){
		cout << "koneksi berhasil" <<endl;
		char szInput[1024] = { '\0'};
		SOCKET aSend;
		cout << "send>";
		cin.getline(szInput,1024);
		aSend = send(sock,szInput,1024,0);
		if(aSend==INVALID_SOCKET){
			cout << "(Gagal Mengirim)"<<endl;
			return FALSE;
	
		}
		else{
			cout << "(Sending OK)" << endl;
		}}
	else{
		cout <<"Koneksi Gagal !!" <<endl;
	}

system("pause");
CloseConnection();
    return EXIT_SUCCESS;
}
bool bConnection(char* pszAddress, int nNoPort){
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
    addr.sin_addr.s_addr=inet_addr(pszAddress);

    sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

    if(sock==INVALID_SOCKET){
        return FALSE;
    }
    if(connect(sock,(SOCKADDR *) &addr,sizeof(addr))==SOCKET_ERROR){
        return FALSE;
    }
    else{
    	return true;
    }

}
void CloseConnection(){
    if(sock){
        closesocket(sock);
    }
    WSACleanup();
}
