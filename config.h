#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char dbname[256];
    char user[256];
    char password[256];
    char host[256];
    char port[256];
} DBConfig;

int read_config(const char *filename, DBConfig *config);

#endif
