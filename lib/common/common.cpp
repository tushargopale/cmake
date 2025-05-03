#include "common.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void error(const string &msg) {
    perror(msg.c_str()); // The perror() function in C is used to produce an error message to the standard error stream (stderr)
    exit(1);
}

int create_socket() {
    // SOCK_STREAM- TCP connection-oriented, reliable socket
    // SOCK_DGRAM- UDP and sends data in independent datagrams
    // AF_INET- address family IPV4 which this sokcket supports. There are more like
    // AF_INET6, AF_UNIX, AF_BLUETOOTH, AF_CAN, etc
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("Socket creation failed");
    return sockfd;
}

/*
bind() function assigns a local address (IP address and port number) to a socket.
This establishes the socket's local endpoint, allowing it to receive incoming connections
or data on that specific address.
*/
void bind_socket(int sockfd, int port) {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (::bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) //c++ also has bind function in std namespace. :: ensures bind from global namespace
        error("Bind failed");
}

/*
listen() function that puts the server socket in a passive mode, where it waits for the client
to approach the server to make a connection
sockfd: socket file descriptor created using the socket() function.
backlog: number representing the size of the queue holding the pending connections while the server
    is waiting to accept a connection
*/
void listen_socket(int sockfd, int backlog) {
    listen(sockfd, backlog);
}

/*
In this step the server extracts the first connection request from the queue of pending connections
for the listening socket, sockfd, creates a new connected socket using the accept() function, and
returns a new file descriptor referring to that socket. At this point, the connection is established
between client and server, and they are ready to transfer data.
*/
int accept_socket(int sockfd) {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sockfd, (sockaddr*)&client_addr, &client_len);
    if (client_sock < 0) {
        error("Accept failed");
    }
    return client_sock;
}

/*
The connect() system call connects the socket referred to by the file descriptor sockfd
to the address specified by serv_addr. Server’s address and port is specified in serv_addr.
*/
void connect_socket(int sockfd, const string &ip, int port) {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error("Connection failed");
}

void send_message(int sockfd, const string &message) {
    send(sockfd, message.c_str(), message.length(), 0);
}

string receive_message(int sockfd) {
    char buffer[1024] = {0};
    ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) error("Read failed");
    return string(buffer);
}

void close_socket(int sockfd) {
    close(sockfd);
}
