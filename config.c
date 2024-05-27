#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int read_config(const char *filename, DBConfig *config) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening config file: %s\n", filename);
        return -1;
    }

    char line[512];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, "=");
        if (token != NULL) {
            char *key = token;
            char *value = strtok(NULL, "\n");
            if (value != NULL) {
                if (strcmp(key, "DB_NAME") == 0) {
                    strncpy(config->dbname, value, sizeof(config->dbname) - 1);
                } else if (strcmp(key, "DB_USER") == 0) {
                    strncpy(config->user, value, sizeof(config->user) - 1);
                } else if (strcmp(key, "DB_PASSWORD") == 0) {
                    strncpy(config->password, value, sizeof(config->password) - 1);
                } else if (strcmp(key, "DB_HOST") == 0) {
                    strncpy(config->host, value, sizeof(config->host) - 1);
                } else if (strcmp(key, "DB_PORT") == 0) {
                    strncpy(config->port, value, sizeof(config->port) - 1);
                }
            }
        }
    }

    fclose(file);
    return 0;
}
