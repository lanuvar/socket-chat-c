#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	listen(server_socket, 5);
	printf("TCP Sunucu 8080 portunda baglanti bekliyorrr...\n");

	struct sockaddr_in client_address;
	socklen_t client_addr_len = sizeof(client_address);

	int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_len);
	printf("Biri baglandi! IP: %s\n", inet_ntoa(client_address.sin_addr));
	printf("Iki yonlu asenkron chat basladi! (Cikmak icin Ctrl+C)\n");

	//---BÖLÜNME NOKTASI (Sunucu için)---
	pid_t process_id = fork();

	if (process_id == 0) {
		// ÇOCUK SÜREÇ: Sadece istemciden gelen mesajları dinle
		char buffer[1024];
		while(1) {
			int received_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
			if (received_bytes > 0) {
				buffer[received_bytes] = '\0';
				printf("\n[Istemci]: %s", buffer);
			}
			else if (received_bytes == 0){
				printf("\nIstemci baglantiyi kesti.\n");
				break; //Döngüyü kır ve kapan.
			}
		}
	}
	else if (process_id > 0) {
		// PARENT PROCESS: sadece klavyeden yazıp istemciye gönder
		char message[1024];
		while(1) {
			fgets(message, sizeof(message), stdin);
			send(client_socket, message, strlen(message), 0);
		}
	}


	close(client_socket); // Client özel hattını kapat
	close(server_socket); // Dükkanın ana kapısnı kapat

	return 0;
}
