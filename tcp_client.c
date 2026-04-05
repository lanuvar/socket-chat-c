#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Sunucuya baglaniliyor...\n");

	if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1){
		printf("Baglanti hatasi!\n");
		return 1; // Hata varsa programı bitir

	}

	printf("Baglanti basarili! Mesaj gönderiliyor...\n");

	//---SİHİRLİ BÖLÜNME NOKTASI---
	pid_t process_id = fork(); //Program burada ikiye ayrılı!!

	if (process_id == 0) {
		// ÇOCUK SÜREÇ (Child Process): Sadece gelen mesajları okur
		char server_response[1024];
		while(1) {
			int received_bytes = recv(client_socket, server_response, sizeof(server_response), 0);
			if (received_bytes > 0) {
				server_response[received_bytes] = '\0';
				// Gelen mesajı ekrana bas (Bunu yaparken klavyeyi engellemez!)
				printf("\n[Sunucu]: %s", server_response);
			}else if (received_bytes == 0){
				printf("Sunucu baglantiyi kesti.\n");
				break;
			}
		}

	}
	else if (process_id > 0){
		// PARENT PROCESS : Sadece klavyeden okur ve gönderir
		char message[1024];
		while(1) {
			fgets(message, sizeof(message), stdin); // Klavyede bekle
			send(client_socket, message, strlen(message), 0); // Fırlat
		}
	}
	else{
		printf("Fork basarisiz oldu!\n");
	}

	//  İşim bitti hattı kapatıyorum
	close(client_socket);

	return 0;
}
