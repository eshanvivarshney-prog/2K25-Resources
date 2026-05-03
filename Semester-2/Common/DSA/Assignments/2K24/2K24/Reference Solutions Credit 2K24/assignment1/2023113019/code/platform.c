#include "platform.h"
#include "comment.h"
#include "reply.h"
#include "post.h"
#include <stdlib.h>

Platform * platform;
int flag = 0;//to check if a post has been viewed or not

/*Create an instance of the platform data type. Only one such instance should be made through out the code*/
Platform * createPlatform(){
    if(platform!=NULL){
        return NULL;//there aldready exists a platform- createPlatform has aldready been called once
    }
    platform = (Platform *)malloc(sizeof(Platform));
    if(platform==NULL)
    return NULL;
    platform->Posts = NULL;
    platform->lastViewedPost = NULL;
    return platform;
}

/*Create a post of the given parameters (by calling the previous implemented function) and adds it to the existing list of posts, returning whether the process is successful or not*/
bool addPost(char * username, char * caption){
    bool posted = true; // assuming true unless found otherwise.
    Post * p = createPost(username,caption);
    if(p==NULL){//in case createPost() has some error.
        posted = false;
        return posted;
    }
    Post * temp = platform->Posts;
    if(temp==NULL){
        platform->Posts = p;
        platform->lastViewedPost = p;
        return posted;
    }
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = p;
    p->prev = temp;
    if(flag == 0){
        platform->lastViewedPost = p;
    }
    return posted;
}

/*Deletes the nth recent post, returning whether the deletion is successful or not. Also, it should clear the comments and replies as well to the post*/
bool deletePost(int n){
    bool deleted = true;// assuming true unless found otherwise.
    Post * temp = platform->Posts;
    if(temp==NULL){
        deleted = false;
        return deleted;
    }

    //reaches the end of the linkedlist. 
    while(temp->next!=NULL){
        temp = temp->next;
    }

    for(int i = 1;i<n;i++){
        temp = temp->prev;
        if(temp==NULL){//there does not exist a nth recent post.
            deleted = false;
            return deleted;
        }
    }
    //temp is not NULL. NULL checking was done after temp updation.
    if(platform->lastViewedPost==temp){//if the lastViewedPost is being deleted
        flag = 0;
        Post * traverse = platform->Posts;
        //traverse can never be NULL: lastViewedPost exists.

        if(traverse->next==NULL){
            platform->lastViewedPost = NULL;
        }
        else{
            //reaches the end of the list.
            while(traverse->next !=NULL){
                traverse = traverse->next;
            }
            if(traverse==temp){//if the post to be deleted is the last post.
                platform->lastViewedPost = traverse->prev;
            }
            else{
                platform->lastViewedPost = traverse;
            }
        }
    }
    
    if(temp->prev!=NULL){
        temp->prev->next = temp->next;
    }
    else{//temp->prev is NULL means start of the list.
        platform->Posts = temp->next;
    }

    if(temp->next!=NULL){
        temp->next->prev = temp->prev;
    }
    //nothing special if end of list:temp->next = NULL.

    Comment * traverseComment = temp->Comments;
    while(traverseComment!=NULL){
        Comment * storeNextComment = traverseComment->next;
        Reply * traverseReply = traverseComment->Replies;
        while(traverseReply!=NULL){
            Reply * storeNextReply = traverseReply->next;
            free(traverseReply);
            traverseReply = storeNextReply;
        }
        free(traverseComment);
        traverseComment = storeNextComment;
    }
    free(temp);
    return deleted;
}

/*Returns the nth recent post, if existing. If it does not exist, a NULL pointer must be returned*/
Post * viewPost(int n){
    Post * post;
    Post * temp = platform->Posts;
    if(temp==NULL){
        post = NULL;
        return post;
    }
    
    //reaches last post of linked list.
    while(temp->next!=NULL){
        temp = temp->next;
    }

    for(int i = 1;i<n;i++){
        temp =temp->prev;
        if(temp==NULL){
            post = NULL;
            return post;
        }
    }
    
    post = temp;
    platform->lastViewedPost = temp;
    flag = 1;
    return post;
}

/*Returns the lastViewedPost. As described earlier, this post will be the most recent post, if no other post has been viewed. 
If no post has been done, a NULL pointer must be returned*/
Post * currPost(){
    Post * post;
    post = platform->lastViewedPost;
    if(post==NULL){
        return post;
    }
    flag = 1;
    return post;
}

/*Returns post which was posted just before posting the lastViewedPost. If the lastViewedPost is the first post to be added, then return it.
 In case of any error, a NULL pointer must be returned. Doing this operation, will change the lastViewedPost, by it’s definition*/
Post * nextPost(){
    Post * post;
    if(platform->lastViewedPost==NULL){
        post = NULL;
        return post;
    }
    if(platform->lastViewedPost->prev==NULL){//first post
        post = platform->lastViewedPost;
    }
    else{
        post = platform->lastViewedPost->prev;
        platform->lastViewedPost = post;
    }
    if(post == NULL){
        return post;
    }
    flag = 1;
    return post;
}

/*Returns post which was posted just after posting the lastViewedPost. If the lastViewedPost is the most recent to be added, then return it. 
In case of any error, a NULL pointer must be returned.Doing this operation, will change the lastViewedPost, by it’s definition*/
Post * previousPost(){
    Post * post;
    if(platform->lastViewedPost==NULL){
        post = NULL;
        return post;
    }
    if(platform->lastViewedPost->next==NULL){//most recent post
        post = platform->lastViewedPost;
    }
    else{
        post = platform->lastViewedPost->next;
        platform->lastViewedPost = post;
    }
    if(post == NULL){
        return post;
    }
    flag = 1;
    return post;
}

/*Adds a comment to the lastViewedPost, returning whether the addition is successful or not*/
bool addComment(char * username, char * content){
    bool commented = true;
    Comment * comment = createComment(username,content);
    if(comment ==NULL){//error in createComment implementation
        commented = false;
        return commented;
    }

    if(platform->lastViewedPost==NULL){
        commented = false;
        return commented;
    }

    Comment * traverseComments = platform->lastViewedPost->Comments;
    if(traverseComments==NULL){
        platform->lastViewedPost->Comments= comment;
        return commented;
    }
    
    while(traverseComments->next!=NULL){//reaches last comment
        traverseComments = traverseComments->next;
    }
    traverseComments->next = comment;
    comment->prev = traverseComments;
    return commented;
}


/*Deletes the nth recent comment to the lastViewedPost, returning whether the deletion is successful or not. Also, it should clear the replies to the comment as well*/
bool deleteComment(int n){
    bool deleted = true;
    if(platform->lastViewedPost==NULL){
        deleted = false;
        return deleted;
    }
    Comment * temp = platform->lastViewedPost->Comments;   
    if(temp==NULL){
        deleted = false;
        return deleted;
    } 

    //reaches end of comment list
    while(temp->next!=NULL){
        temp = temp->next;
    }
    
    for(int i= 1;i<n;i++){
        temp = temp->prev;
        if(temp==NULL){//there does not exist a nth recent comment
            deleted = false;
            return deleted;
        }
    }
    if(temp->prev!=NULL){
        temp->prev->next = temp->next;
    }
    else{//first comment is to be deleted.
        platform->lastViewedPost->Comments = temp->next;
    }

    if(temp->next!=NULL){
        temp->next->prev = temp->prev;
    }

    Reply * traverseReply = temp->Replies;
    while(traverseReply!=NULL){
        Reply * storeNextReply = traverseReply->next;
        free(traverseReply);
        traverseReply = storeNextReply;
    }
    free(temp);
    return deleted;
}

/*Returns a list of all comments to the lastViewedPost and returns whether the viewing was successful or not. 
The order of the comments in the list must be in order of the time of commenting, the latest being at last. The order of replies should be the same as well*/
Comment * viewComments(){
    Comment * comments;
    if(platform->lastViewedPost==NULL){
        comments = NULL;
        return comments;
    }
    comments = platform->lastViewedPost->Comments;
    return comments;
}

/*Adds a reply to the nth recent comment of the lastViewedPost, returning whether the addition is successful or not*/
bool addReply(char * username, char * content, int n){
    bool replied = true;
    Reply * reply = createReply(username,content);
    if(reply==NULL){//some problem with createReply
        replied = false;
        return replied;
    }

    if(platform->lastViewedPost==NULL){
        replied = false;
        return replied;
    }    
    Comment * comment = platform->lastViewedPost->Comments;
    if(comment == NULL){
        replied = false;
        return replied;
    }
    while(comment->next!=NULL){//reaches the end of the list.
        comment = comment->next;
    }
    for(int i = 1;i<n;i++){
        comment = comment->prev;
        if(comment==NULL){
            replied = false;
            return replied;
        }
    }
    Reply * traverseReply = comment->Replies;
    if(traverseReply==NULL){
        comment->Replies=reply;
    }
    else{
        while(traverseReply->next!=NULL){
            traverseReply= traverseReply->next;
        }
        traverseReply->next = reply;
        reply->prev = traverseReply;
    }
    return replied;
}

/*Deletes the mth recent reply to the nth recent comment of the lastViewedPost, returning whether the deletion is successful or not*/
bool deleteReply(int n, int m){
    bool deleted = true;
    if(platform->lastViewedPost==NULL){
        deleted = false;
        return deleted;
    }
    Comment * traverseComments = platform->lastViewedPost->Comments;   
    if(traverseComments==NULL){
        deleted = false;
        return deleted;
    } 

    //reaches end of comment list
    while(traverseComments->next!=NULL){
        traverseComments = traverseComments->next;
    }

    for(int i = 1;i<n;i++){
        traverseComments = traverseComments->prev;
        if(traverseComments==NULL){//there does not exist a nth recent comment
            deleted = false;
            return deleted;
        }
    }

    Reply * temp = traverseComments->Replies;
    if(temp==NULL){
        deleted = false;
        return deleted;
    } 

    //reaches end of reply list
    while(temp->next!=NULL){
        temp = temp->next;
    }
    
    for(int i= 1;i<m;i++){
        temp = temp->prev;
        if(temp==NULL){//there does not exist a mth recent reply
            deleted = false;
            return deleted;
        }
    }
    if(temp->prev!=NULL){
        temp->prev->next = temp->next;
    }
    else{//first reply is to be deleted.
        traverseComments->Replies = temp->next;
    }

    if(temp->next!=NULL){
        temp->next->prev = temp->prev;
    }
    free(temp);
    return deleted;
}