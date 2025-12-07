#include "comment.h"
#include <stdlib.h>

/*Creates a comment using the given parameters, returning a pointer to it*/
Comment * createComment(char * username, char * content){
    Comment * comment = (Comment *) malloc(sizeof(Comment));
    if(comment ==NULL){
        return comment;
    }
    strcpy(comment->Username,username);
    strcpy(comment->Content,content);
    //default value assignment to replies, next and prev pointers.
    comment->Replies = NULL;
    comment->next = NULL;
    comment->prev = NULL;
    return comment;
}