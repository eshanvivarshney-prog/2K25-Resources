#include "reply.h"
#ifndef __COMMENT_H__
#define __COMMENT_H__

typedef struct Comment Comment;

struct Comment{
    char Username[128];
    char Content[128];
    Reply* Replies;
    Reply* latestReply;
    Comment* next;
    Comment* prev;
    int replySize;
};

Comment* createComment(char* username, char* content);
void freeComment(Comment* comment);

#endif