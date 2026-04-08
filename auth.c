#include "auth.h"
#include "fileio.h"
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>

int login(const char *username, const char *password) {
    char *data = read_file("db.json");
    if (!data) return 0;

    cJSON *root = cJSON_Parse(data);
    free(data);

    if (!root) return 0;

    int size = cJSON_GetArraySize(root);

    for (int i = 0; i < size; i++) {
        cJSON *item = cJSON_GetArrayItem(root, i);

        cJSON *u = cJSON_GetObjectItem(item, "username");
        cJSON *p = cJSON_GetObjectItem(item, "password");

        if (u && p &&
            strcmp(u->valuestring, username) == 0 &&
            strcmp(p->valuestring, password) == 0) {

            cJSON_Delete(root);
            return 1;
        }
    }

    cJSON_Delete(root);
    return 0;
}
