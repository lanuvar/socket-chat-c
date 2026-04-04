#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	// 1. TCP Soketi Oluştur (SOCK_STREAM)
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// 2. Hedef Adres (Sunucumuzun adresi ve portu)
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 3. YENİ: TCP'de doğrudan fırlatmak yok, önce kapıyı çalacağız (Connect)
	printf("Sunucuya baglaniliyor...\n");
	int connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if (connection_status == -1){
		printf("Baglanti hatasi! Sunuc acik mi?\n");
		return 1; // Hata varsa programı bitir

	}

	printf("Baglanti basarili! Mesaj gönderiliyor...\n");

	// 4. Bağlantı kurulduktan sonra hedef belirtmeden (sendto yerine send ile) konuşuruz
	char *message = "Merhaba TCP server. Ben yeni TCP client";
	send(client_socket, message, strlen(message), 0);

	// 5. Sunucunun cevabını bekle (recvfrom yerine recv)
	char server_response[1024];
	int received_bytes = recv(client_socket, server_response, sizeof(server_response), 0);

	if (received_bytes > 0) {
		server_response[received_bytes] = '\0';
		printf("Sunucudan gelen: %s\n", server_response);
	}

	// 6. İşim bitti hattı kapatıyorum
	close(client_socket);

	return 0;
}
