#include "reply.h"
#include <string.h>

#ifndef __COMMENT_H__
#define __COMMENT_H__

typedef struct Comment{
    char Username[MAX_USERNAME_SIZE];
    char Content[MAX_CONTENT_SIZE];
    Reply * Replies;
    struct Comment * next;
    struct Comment * prev;
}Comment;

Comment * createComment(char * username, char * content);

#endif