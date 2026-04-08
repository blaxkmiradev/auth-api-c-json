#include "server.h"
#include "auth.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

static void send_response(int c, const char *msg) {
    char buf[1024];
    sprintf(buf,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Connection: close\r\n\r\n"
        "%s",
        msg
    );
    send(c, buf, strlen(buf), 0);
}

void start_server() {
    int s, c;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char req[4096];

    s = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 5);

    printf("Server running http://localhost:%d\n", PORT);

    while (1) {
        c = accept(s, (struct sockaddr*)&addr, &len);
        read(c, req, sizeof(req));

        if (strstr(req, "POST /login")) {

            char user[100] = {0};
            char pass[100] = {0};

            char *u = strstr(req, "username=");
            char *p = strstr(req, "password=");

            if (u && p) {
                sscanf(u, "username=%[^&]", user);
                sscanf(p, "password=%s", pass);
            }

            if (login(user, pass))
                send_response(c, "{\"status\":\"success\",\"token\":\"fake_token_123\"}");
            else
                send_response(c, "{\"status\":\"fail\"}");

        } else {
            send_response(c, "{\"message\":\"not found\"}");
        }

        close(c);
    }
}
