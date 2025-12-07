#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include<stdlib.h>
#include<string.h>

extern Platform* socialMedia;

Comment* createComment(char* username, char* content){
    Comment* newComment = (Comment*)malloc(sizeof(Comment));

    if(newComment == NULL){
        return NULL;
    }//! if malloc fails

    //* initialize the newComment struct with values
    //! INITIALISE POINTERS IN PLATFORM.C
    strcpy(newComment->Username, username);
    strcpy(newComment->Content, content);
    newComment->Replies = NULL;
    newComment->latestReply = NULL;
    newComment->next = NULL;
    newComment->prev = NULL;
    newComment->replySize = 0;

    return newComment;//* return the newComment
}

void freeComment(Comment* comment){
    if(comment == NULL){
        return;
    }//! if comment is NULL

    Reply* currentReply = comment->Replies;

    while (currentReply != NULL) {
        Reply* nextReply = currentReply->next;
        freeReply(currentReply);  // assuming you have a function to free a Reply
        currentReply = nextReply;
    }

    free(comment);
    comment = NULL;
    return;
}