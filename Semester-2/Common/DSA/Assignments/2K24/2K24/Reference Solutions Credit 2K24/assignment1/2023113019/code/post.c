#include "post.h"
#include <stdlib.h>

/*Creates a post using the given parameters, returning a pointer to it*/
Post * createPost(char * username, char * caption){
    Post *  post = (Post *)malloc(sizeof(Post));
    if(post==NULL){
        return NULL;
    }
    strcpy(post->Username,username);
    strcpy(post->Caption,caption);
    //putting a default value in Comments, next and previous pointers.
    post->Comments = NULL;
    post->next = NULL;
    post->prev = NULL;
    return post;
}