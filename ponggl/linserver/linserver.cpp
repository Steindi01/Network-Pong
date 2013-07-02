#include <stdio.h>
#include <io.h>
#include <winsock2.h>
//pragma ws2_32.lib


#define port 5555

typedef struct {int x;int y;} vektor;

char readstring[30]="";
	
int readfromclient (int filedes)
{
/*vektor position;
int buffer;
int *bufferp;
bufferp=&buffer;
int nbytes;
nbytes=read(filedes,&position,8);
if (nbytes <0)
{
	exit(1);
}
else if (nbytes ==0)//eof
	return -1;
else
{
int test=888888;
printf("printingint %i",test);
printf("received posx %i",position.x);
printf("received posy %i",position.y);
return 0;
}*/
	return 0;
}

void main(){

WORD wVersionRequested;
WSADATA wsaData;
int wsaerr;

 

// Using MAKEWORD macro, Winsock version request 2.2
wVersionRequested = MAKEWORD(2, 2);
wsaerr = WSAStartup(wVersionRequested, &wsaData);

if (wsaerr != 0) 
{
    /* Tell the user that we could not find a usable WinSock DLL.*/
    printf("Server: The Winsock dll not found!\n");

}
else 
{
       printf("Server: The Winsock dll found!\n");
       printf("Server: The status: %s.\n", wsaData.szSystemStatus);
}

 

/* Confirm that the WinSock DLL supports 2.2.*/
/* Note that if the DLL supports versions greater    */
/* than 2.2 in addition to 2.2, it will still return */
/* 2.2 in wVersion since that is the version we      */
/* requested.                                        */

if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 ) 
{
    /* Tell the user that we could not find a usable WinSock DLL.*/
    printf("Server: The dll do not support the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
    WSACleanup();

}
else 
{
       printf("Server: The dll supports the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
       printf("Server: The highest version this dll can support: %u.%u\n", LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
}

//////////CREATE SOCKET////////////////
// Create a socket object called m_socket.

SOCKET m_socket;

// Call the socket function and return its value to the m_socket variable.
// For this application, use the Internet address family, streaming sockets, and
// the TCP/IP protocol.
// using AF_INET family, TCP socket type and protocol of the AF_INET - IPv4

m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

// Check for errors to ensure that the socket is a valid socket.

if (m_socket == INVALID_SOCKET)
{
    printf("Server: Error at socket(): %ld\n", WSAGetLastError());
    WSACleanup();

}

else 
{
	printf("Server: socket() is OK!\n"); 
}

 

////////////////bind//////////////////////////////
// Create a sockaddr_in object and set its values.

sockaddr_in service;

// AF_INET is the Internet address family.

service.sin_family = AF_INET;
// "127.0.0.1" is the local IP address to which the socket will be bound.
service.sin_addr.s_addr = inet_addr("127.0.0.1");
// 55555 is the port number to which the socket will be bound.
service.sin_port = htons(55555);

 

if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
{
    printf("Server: bind() failed: %ld.\n", WSAGetLastError());
    closesocket(m_socket);

}
else 
{
    printf("Server: bind() is OK!\n");
}
listen(m_socket, 1);

 

// Create a temporary SOCKET object called AcceptSocket for accepting connections.
/*schleife umbauen*/
SOCKET AcceptSocket;



while (1)

{
AcceptSocket = SOCKET_ERROR;
while (AcceptSocket == SOCKET_ERROR)
{
AcceptSocket = accept(m_socket, NULL, NULL);
}

 

// else, accept the connection...
// When the client connection has been accepted, transfer control from the
// temporary socket to the original socket and stop checking for new connections.

printf("Server: Client Connected!\n");

m_socket = AcceptSocket; 

break;

}

 

int bytesSent;

int bytesRecv = SOCKET_ERROR;

char sendbuf[200] = "This string is a test data from server";

// initialize to empty data...

char recvbuf[200] = "";

 

// Send some test string to client...
printf("Server: Sending some test data to client...\n");
int sender=543210;
//bytesSent = send(m_socket, &sender,sizeof(int), 0);
bytesSent = send(m_socket, sendbuf, strlen(sendbuf), 0);

//bytesSent = write(&m_socket,&sender,sizeof(int));
 

if (bytesSent == SOCKET_ERROR)
       printf("Server: send() error %ld.\n", WSAGetLastError());
else
{
       printf("Server: send() is OK.\n");
       printf("Server: Bytes Sent: %ld.\n", bytesSent);
}

 

// Receives some test string from client...and client
// must send something lol...

//bytesRecv = recv(m_socket, recvbuf, 200, 0);
vektor testcoord;
testcoord.x=11;
testcoord.y=22;

static vektor* vektorpointer=&testcoord;


bytesRecv=recv(m_socket,(char *)vektorpointer,sizeof(vektor),0);
printf("testcoord.x%i\n",testcoord.x);
	 printf("testcoord.y%i\n",testcoord.y);


/*
//{
     printf("Server: recv() is OK.\n");

       //printf("Server: Received data is: \"%s\"\n", recvbuf);
	 
       printf("Server: Bytes received: %ld.\n", bytesRecv);

//}
*/
 

if (bytesRecv == SOCKET_ERROR)

       printf("Server: recv() error %ld.\n", WSAGetLastError());

else

{
     printf("Server: recv() is OK.\n");

       printf("Server: Received data is: \"%s\"\n", recvbuf);

       printf("Server: Bytes received: %ld.\n", bytesRecv);

}

 

// Receives some test string from client...and client
// must send something lol...

//bytesRecv = recv(m_socket, recvbuf, 200, 0);
//FILE* empfang;
//empfang=fopen("empfangen.txt","w");
//fread((void*)m_socket,20,1,empfang);
//fclose(empfang); 

//if (bytesRecv == SOCKET_ERROR)

  //     printf("Server: recv() error %ld.\n", WSAGetLastError());

//else

 
closesocket(m_socket);
WSACleanup();


 /*

//int bytesSent;
//int bytesRecv = SOCKET_ERROR;
//char sendbuf[200] = "This string is a test data from server";

char recvbuf[200] = "";
//bytesSent = send(m_socket, sendbuf, strlen(sendbuf), 0);
 
//recv(m_socket, recvbuf, 200, 0);
int socketpointer=0;
UINT_PTR dort;
dort=m_socket;
//socketpointer=*dort;
//printf("sockp%i",socketpointer);

//read(dort,&recvbuf,20);	
//recv(m_socket,recvbuf,20,0);
 recv(m_socket, recvbuf, 20, 0);

printf("Server: Received data is: %s", recvbuf);



WSACleanup();





/*
while (1)
{
//select() linux zeug..bzw wer connected
int connection;
int size;
connection=accept(serversocket,NULL,NULL);
	if (connection <0)
		exit(1);
	else 
//	if (readfromclient(i)<0)
	{
		recv(serversocket,readstring,30,0);
		printf("read%s",readstring);
		//	close(serversocket);
		WSACleanup();
		exit(0);
	}
	*/
	}
 




