#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include<stdlib.h>
#include<string.h>

extern Platform* socialMedia;

Reply* createReply(char* username, char* content){
    Reply* newReply = (Reply*)malloc(sizeof(Reply));

    if(newReply == NULL){
        return NULL;
    }//! if malloc fails

    //* initialize the newReply struct with values
    //! INITIALISE POINTERS IN PLATFORM.C
    strcpy(newReply->Username, username);
    strcpy(newReply->Content, content);
    newReply->next = NULL;
    newReply->prev = NULL;

    return newReply;//* return the newReply
}

void freeReply(Reply* reply){
    if(reply == NULL){
        return;
    }//! if reply is NULL

   free(reply);
    reply = NULL;
   return;
}