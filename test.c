#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int sockfd;
  struct sockaddr_in address;

  // Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    // Handle socket creation error
  }

  // Specify the IP address and port to bind the socket to
  address.sin_family = AF_INET;
  address.sin_port = htons(12345);
  address.sin_addr.s_addr = inet_addr("10.11.3.10");

  // Bind the socket to the specified IP address and port
  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		printf("nope\n");
    // Handle bind error
  }

  // ...

  // Close the socket when it's no longer needed
  close(sockfd);

  return 0;
}
