#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "../header.h"
//#include "../getKey.h"

int main() {
	int msgCounter = 1;
    printHeader();
    int key = getKey();
    printHeader();

	while (1) {
		WSADATA wsa;
    	SOCKET s;
    	struct sockaddr_in server;
    	char *request = malloc(500); 
    	char server_reply[2000];
    	int recv_size;

    	// Inisialisasi Winsock //////////////////////////////////////////////////////////////////
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            printf(" Winsock failed. Error code: %d",WSAGetLastError());
            return 1;
        } //else printf("Winsock initialised.\n");

        // Membuat socket ///////////////////////////////////////////////////////////////////////
        if((s = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET) {
            printf(" Could not create socket. Error code: %d" , WSAGetLastError());
            return 1;
        } //else printf("Socket created.\n");
        
        // Definisi identitas server ///////////////////////////////////////////////////////////
        // server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_addr.s_addr = inet_addr("103.43.44.105");
        server.sin_family = AF_INET;
        server.sin_port = htons(80);
     
        // Menghubungi server //////////////////////////////////////////////////////////////////
        if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf(" Tidak dapat terhubung dengan server.");
            return 1;
        } //else printf("Koneksi ke server berhasil.\n");



        sprintf(request, "GET /alpro/index.php/app/read/%d HTTP/1.1\r\n"
                        	"Host: 103.43.44.105\r\n"
                        	"Connection: keep-alive\r\n"
                        	"Accept: */*\r\n\r\n", msgCounter);

        send(s, request, strlen(request), 0);

        recv_size = recv(s, server_reply, 2000 , 0);
        server_reply[recv_size] = '\0';

        //printf("%c", server_reply[473]);
        //printf("%s", server_reply);
        int i=0;
        char server_reply_int[2000];

        if (server_reply[441] != 'X') {
            printf(" ");
        	int n = (server_reply[441] == '\n' ? 441 : 440);
	        for (n; n < strlen(server_reply); n++){
	        	server_reply_int[i] = server_reply[n];
	        	i++;
	        	printf("%c",server_reply[n]);
			}
	        msgCounter++;
        }
        
        
        
        
        
        int length=0;
        while(server_reply_int[length] != '\0'){
			length++;
		} 
		
		for(i=0;i<length;i++){
			printf("%c",server_reply_int[i]);
		}
        /*
        for(i=0;i<length;i++){
        	server_reply_int[i] = (100+(key+i));
		}
		
		char complete_msg[length];
		for(i=0;i<length;i++){
			complete_msg[i]=server_reply_int[i];
		}*/
		
		
		

        closesocket(s);
        WSACleanup();
        sleep(1);
	}
}
