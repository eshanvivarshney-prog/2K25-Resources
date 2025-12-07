#include <string.h>

#ifndef __REPLY_H__
#define __REPLY_H__

#define MAX_USERNAME_SIZE 100
#define MAX_CONTENT_SIZE 100

typedef struct Reply{
    char Username[MAX_USERNAME_SIZE];
    char Content[MAX_CONTENT_SIZE];
    struct Reply * next;
    struct Reply * prev;
}Reply;

Reply * createReply(char * username, char * content);

#endif