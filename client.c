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

   char *message = "Merhabaaa! Ben senin elle yazdığın ilk Client Bip Bop!";

   sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));

   printf("Mesaj basariyla sunucuya ateslendii!\n");

   close(client_socket);

   return 0;


}
