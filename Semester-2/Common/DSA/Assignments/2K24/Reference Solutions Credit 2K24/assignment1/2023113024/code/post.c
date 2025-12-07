#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include<stdlib.h>
#include<string.h>

extern Platform* socialMedia;

Post* createPost(char* username, char* caption){
    Post* newPost = (Post*)malloc(sizeof(Post));

    if(newPost == NULL){
        return NULL;
    }//! if malloc fails

    //* initialize the newPost struct with values
    //! INITIALISE POINTERS IN PLATFORM.C

    strcpy(newPost->Username, username);
    strcpy(newPost->Caption, caption);
    newPost->Comments = NULL;
    newPost->latestComment = NULL;
    newPost->next = NULL;
    newPost->prev = NULL;
    newPost->commentSize = 0;

    return newPost;//* return the newPost
}

void freePost(Post* post) {
    if(post==NULL){
        return;
    }//! if post is NULL (error

    Comment* currentComment = post->Comments;

    while (currentComment != NULL) {
        Comment* nextComment = currentComment->next;
        freeComment(currentComment);  // assuming you have a function to free a Comment
        currentComment = nextComment;
    }
    
    free(post);
    post = NULL;
}