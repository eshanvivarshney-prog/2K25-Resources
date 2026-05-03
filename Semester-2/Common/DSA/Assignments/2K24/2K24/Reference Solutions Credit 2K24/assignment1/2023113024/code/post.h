#include "comment.h"
#ifndef __POST_H__
#define __POST_H__

typedef struct Post Post;

struct Post{
    char Username[128];
    char Caption[128];
    Comment* Comments;
    Comment* latestComment;
    Post* next;
    Post* prev;
    int commentSize;
};  

Post* createPost(char* username, char* caption);
void freePost(Post* post);

#endif