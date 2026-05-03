#include "reply.h"
#include <stdlib.h>

/*Creates a reply using the given parameters, returning a pointer to it*/
Reply * createReply(char * username, char * content){
    Reply * reply = (Reply *) malloc (sizeof(Reply));
    if(reply==NULL){
        return reply;
    }
    strcpy(reply->Username,username);
    strcpy(reply->Content,content);
    
    //default values
    reply->next = NULL;
    reply->prev = NULL;
    return reply;
}

