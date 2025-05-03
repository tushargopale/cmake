#include "common.h"
#include "utils.h"
#include "client_utils.h"
#include <unistd.h>

int main() {
    print_client_banner();

    int sockfd = create_socket();
    connect_socket(sockfd, "127.0.0.1", 8080);

    send_message(sockfd, "Hello from client!");
    log("Client", "Message sent");

    std::string reply = receive_message(sockfd);
    log("Client", "Server replied: " + reply);

    close_socket(sockfd);
    return 0;
}
