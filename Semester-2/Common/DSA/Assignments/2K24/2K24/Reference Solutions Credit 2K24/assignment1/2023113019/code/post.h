#include "comment.h"
#include <string.h>

#ifndef __POST_H__
#define __POST_H__

#define MAX_CAPTION_SIZE 100

typedef struct Post{
    char Username[MAX_USERNAME_SIZE];
    char Caption[MAX_CAPTION_SIZE];
    Comment * Comments;
    struct Post * next;
    struct Post * prev;
}Post; 

Post * createPost(char * username, char * caption);

#endif
