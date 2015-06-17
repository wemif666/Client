/* ClientCon
Coded by Rogoz
*/

#include "StdAfx.h"
#include "ClientCon.h"
#include<stdio.h>

#include <string.h>
#include "ClientDlg.h"
 
#pragma comment(lib,"ws2_32.lib") //biblioteka winsock

ClientCon::ClientCon(CClientDlg *dlg)
{
	m_pClient = dlg;
}


ClientCon::~ClientCon(void)
{
	closesocket(s);
	WSACleanup();
}

void ClientCon::StartConnect(string sAddress, int iPort, string sUsername)
{
    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;
	m_pUser = sUsername;

    printf("\nInicjalizacja ");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Blad. Error Code : %d",WSAGetLastError());
        return;
    }
     
    printf("Zainicjowano.\n");
     
    //tworzenie gniazda
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Nie mozna utworzyc gniazda : %d" , WSAGetLastError());
    }
 
    printf("Gniazdo wykonane.\n");
     
     
	server.sin_addr.s_addr = inet_addr(sAddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons( iPort );
 
    //polaczenie
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("blad polaczenia");
        return;
    }
     
    puts("Connected");
     
    //odpowiedz serwera
    while((recv_size = recv(s , server_reply , 2000 , 0)) != SOCKET_ERROR)
    { 
		puts("otrzymano odpowiedz\n");
 
		
		server_reply[recv_size] = '\0';
		puts(server_reply);

		string sTempMsg ="\n"+string(server_reply)+"\n";
		m_pClient->ShowServerInfo(sTempMsg);
    }
    
}

void ClientCon::SendData(string sMessage)
{
	string sTemp = m_pUser +">>"+ sMessage+"\n";

	if( send(s , sTemp.c_str(), sTemp.size() , 0) < 0)
    {
        puts("Blad wyslania");
        return;
    }
}