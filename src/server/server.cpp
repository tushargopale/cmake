#include "common.h"
#include "utils.h"
#include "server_utils.h"
#include <unistd.h>
#include <netinet/in.h>

int main() {
    print_server_banner();

    int server_sock = create_socket();
    bind_socket(server_sock, 8080);
    listen_socket(server_sock, 5);
    log("Server", "Listening on port 8080...");

    int client_sock = accept_socket(server_sock);

    std::string msg = receive_message(client_sock);
    log("Server", "Received: " + msg);

    send_message(client_sock, "Hello from server!");
    close_socket(client_sock);
    close_socket(server_sock);
    return 0;
}
