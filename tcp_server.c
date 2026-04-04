#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

	// 1. TCP için SOCK_STREAM kullanıyoruz.
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	// 2. TCP'de sunucu önce "dinlemeye" başlar. (Aynı anda 5 kişiyi kuyrukta tutabilir)
	listen(server_socket, 5);
	printf("TCP Sunucu 8080 portunda baglanti bekliyorrr...\n");

	struct sockaddr_in client_address;
	socklen_t client_addr_len = sizeof(client_address);

	// 3. Biri kapıyı çalana kadar bekliyoruz accept() fonksiyonu ile
	// Kapı çalındığında o kişiye özel YENİ bir telefon hattı (client_socket) açıyoruz!!
	int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_len);
	printf("Biri baglandi! IP: %s\n", inet_ntoa(client_address.sin_addr));

	char buffer[1024];

	// 4. TCP'de hedefi her seferinde belirtmeye gererk yok. Hat zaten özel.
	// sendto/recvfrom yerine sadece recv ve send kullanıyoruz.
	int received_bytes = recv(client_socket, buffer, sizeof(buffer), 0);

	if (received_bytes > 0){
		buffer[received_bytes] = '\0';
		printf("Gelen mesaj: %s\n", buffer);

		send(client_socket, "TCP Baglantisi Basarili!", 24, 0);
	}

	// 5. TCP'de kapatılacak iki hat var:
	close(client_socket); // Client özel hattını kapat
	close(server_socket); // Dükkanın ana kapısnı kapat

	return 0;
}
