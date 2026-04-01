#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
   int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(8080);
   server_address.sin_addr.s_addr = INADDR_ANY;

   bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

   printf("Sunucu 8080 portunda, tetikte bekleniyor...\n");

   char buffer[1024];
   struct sockaddr_in client_address;
   socklen_t client_addr_len = sizeof(client_address);

   while(1) {
      printf("Mesaj bekleniyor...\n");

      int received_bytes = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_addr_len);

      if (received_bytes > 0) {
         buffer[received_bytes] = '\0';
         printf("Gelen mesaj: %s\n ", buffer);

         printf("Gönderen IP: %s\n", inet_ntoa(client_address.sin_addr));
      }
   }

   close(server_socket);

   return 0;
}
