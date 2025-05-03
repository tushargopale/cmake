#ifndef COMMON_H
#define COMMON_H

#include <string>
using namespace std;

void error(const string &msg);
int create_socket();
void bind_socket(int sockfd, int port);
void listen_socket(int sockfd, int backlog); // only used by server
int accept_socket(int sockfd); // only used by server
void connect_socket(int sockfd, const string &ip, int port);
void send_message(int sockfd, const string &message);
string receive_message(int sockfd);
void close_socket(int sockfd);
#endif
