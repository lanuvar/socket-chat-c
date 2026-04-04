#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

   int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(8080);
   server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

   char message[1024]; // Klavyeden girilecek mesaj için boş kutu

   printf("Chat basladi! (Cikmak icin Ctrl+C)\n");

   while(1) { // Sürekli klavyeyi dinle

      printf("Sen: ");

      // fgets: klavyeden (stdin) en fazla 1024 karakter oku ve message dizisine yaz
      fgets(message, sizeof(message), stdin);

      sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));
      char server_response[1024];
      struct sockaddr_in from_server;
      socklen_t addr_len = sizeof(from_server);

      int resp_bytes = recvfrom(client_socket, server_response, sizeof(server_response), 0, (struct sockaddr*)&from_server, &addr_len);

      if (resp_bytes > 0){
         server_response[resp_bytes] = '\0';
         printf("Sunucudan cevap: %s\n", server_response );
      }

   }

   printf("Mesaj basariyla sunucuya ateslendii!\n");

   close(client_socket);

   return 0;


}
