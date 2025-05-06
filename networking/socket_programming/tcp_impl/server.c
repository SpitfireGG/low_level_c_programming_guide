#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()

{
    int server_fd, new_sock;
    struct sockaddr_in address;
    int opt                  = 1;
    socklen_t addrlen        = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *msg                = "hello from the server";

    // create the socket file descriptor
    // here :
    //      the `AF_INET` is the ipv4 family
    //      the `SOCK_STREAM` is the sequence, two-way byte streams (TCP)
    //      `0` lets the OS choose the preferred protocol automatically, TCP for
    //      SOCK_STREAM  in this case
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("creating socket fd failed");
        exit(1);
    }
    printf("creattion socket fd success\n");

    // if the creation is success then check for if address / port already to
    // avoid errors
    if (setsockopt(server_fd,
                   SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT,
                   &opt,
                   sizeof(opt)))
    {
        perror("setsockopt failed");
        return 1;
    }
    printf("setsockopt success");

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // this is equivalent to 0.0.0.0 & binds to
    // all the available interfaces
    address.sin_port = htons(PORT);
    // converts the decimal port number to network byte order

    // bind the socket to specific ip & port
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) == -1)
    {
        perror("binding failed\n");
        return 1;
    }
    printf("socket bound to port %d", PORT);

    // listen for incomings
    if (listen(server_fd, 3) == -1)
    {
        perror("listening failed\n");
        exit(1);
    }
    printf("listening sucess, listening on port %d", PORT);

    // accepting the connection, creating a new socket that block until a client
    // connects  to it
    if ((new_sock = accept(server_fd, (struct sockaddr *) &address, &addrlen))
        == -1)
    {
        perror("accept failed");
        exit(1);
    }
    printf("acception connection from %s, %d\n",
           inet_ntoa(address.sin_addr),
           ntohs(address.sin_port));

    // communicate with the client

    size_t bytes_recieved = recv(server_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_recieved == -1)
    {
        perror("recv failed");
    }
    else if (bytes_recieved == 0)
    {
        printf("client disconnected unexpectedly.\n");
    }
    else
    {
        buffer[bytes_recieved] = '\0';
        printf("Received message: %s\n", buffer);

        ssize_t bytes_sent = send(new_sock, msg, strlen(msg), 0);
        if (bytes_sent == -1)
        {
            perror("send failed");
        }
        else
        {
            printf("sent message: %s (%zd bytes)\n", msg, bytes_sent);
        }
    }

    close(new_sock);
    printf("client connection closed.\n");

    close(server_fd);
    printf("server listening socket closed.\n");

    return 0;
}
