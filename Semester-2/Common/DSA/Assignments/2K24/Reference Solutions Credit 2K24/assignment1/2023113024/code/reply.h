#ifndef __REPLY_H__
#define __REPLY_H__

typedef struct Reply Reply;

struct Reply{
    char Username[128];
    char Content[128];
    Reply* next;
    Reply* prev;
};

Reply* createReply(char* username, char* content);
void freeReply(Reply* reply);

#endif