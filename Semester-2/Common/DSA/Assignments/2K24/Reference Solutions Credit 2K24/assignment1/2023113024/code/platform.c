#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Platform* socialMedia = NULL;

Platform* createPlatform(){
    if(socialMedia != NULL){
        return socialMedia;
    }//* if socialMedia is not NULL

    socialMedia = (Platform*)malloc(sizeof(Platform));

    if(socialMedia == NULL){
        return NULL;
    }//* if malloc fails

    //* initialize the newPlatform struct with values
    socialMedia->Posts = NULL;
    socialMedia->lastViewedPost = NULL;
    socialMedia->lastViewedPostFixed = false;
    socialMedia->latestPost = NULL;
    socialMedia->postSize = 0;

    return socialMedia;//* return the socialMedia
}

bool addPost(char* username, char* caption){
    Post* newPost = createPost(username, caption);

    if(newPost == NULL){
        return false;
    }//* if createPost fails

    if(socialMedia->Posts == NULL){
        socialMedia->Posts = newPost;
        socialMedia->latestPost = newPost;
        socialMedia->postSize++;
        socialMedia->lastViewedPost = newPost;     
        return true;
    }//* if there are no posts

    socialMedia->latestPost->next = newPost;
    newPost->prev = socialMedia->latestPost;
    socialMedia->latestPost = newPost;
    socialMedia->postSize++;

    if(socialMedia->lastViewedPostFixed==false){
        socialMedia->lastViewedPost = newPost;
    }//* if lastViewedPost is NOT FIXED

    return true;
}

bool deletePost(int n){
    //* n denotes the nth recent post, so its from the bottom, so from top its (postSize - n + 1)th post

    if(n > socialMedia->postSize || n < 1){
        return false;
    }//* if n is greater than the number of posts

    Post* postToBeDeleted = socialMedia->latestPost;

    for(int i = 1; i < n; i++){
        if(postToBeDeleted == NULL){
            return false;
        }//* if postToBeDeleted is NULL

        postToBeDeleted = postToBeDeleted->prev;
    }//* for loop to get the post to be deleted

    if(postToBeDeleted == NULL){
        return false;
    }//* if postToBeDeleted is NULL

    if(socialMedia->postSize==1){
        socialMedia->latestPost = NULL;
        socialMedia->lastViewedPost = NULL;
        socialMedia->lastViewedPostFixed = false;
        socialMedia->Posts = NULL;
        freePost(postToBeDeleted);
        postToBeDeleted = NULL;
        socialMedia->postSize--;
        return true;   
    }//* if there is only one post

    if(postToBeDeleted == socialMedia->lastViewedPost){
        if(socialMedia->lastViewedPost == socialMedia->latestPost){
            socialMedia->lastViewedPost = socialMedia->lastViewedPost->prev;
        }//* if lastViewedPost is the latestPost
        else{
            socialMedia->lastViewedPost = socialMedia->latestPost;
        }//* if lastViewedPost is not the latestPost
        socialMedia->lastViewedPostFixed = false;
    }//* if postToBeDeleted is the lastViewedPost

    if(postToBeDeleted->prev == NULL){
        socialMedia->Posts = postToBeDeleted->next;
        freePost(postToBeDeleted);
        postToBeDeleted = NULL;
        socialMedia->postSize--;
        return true;
    }//* if postToBeDeleted is the first post
    else if(postToBeDeleted->next == NULL){
        socialMedia->latestPost = postToBeDeleted->prev;
        freePost(postToBeDeleted);
        postToBeDeleted = NULL;
        socialMedia->postSize--;
        return true;
    }//* if postToBeDeleted is the last post
    else{
        postToBeDeleted->prev->next = postToBeDeleted->next;
        postToBeDeleted->next->prev = postToBeDeleted->prev;
    }//* if postToBeDeleted is neither the first nor the last post

    freePost(postToBeDeleted);
    postToBeDeleted = NULL;
    socialMedia->postSize--;

    return true;
}

Post* viewPost(int n){
    //* n denotes the nth recent post from bottom

    if(n > socialMedia->postSize || n < 1){
        return NULL;
    }//* if n is greater than the number of posts

    if(socialMedia->postSize == 0){
        return NULL;
    }//* if there are no posts

    Post* postToBeViewed = socialMedia->latestPost;

    for(int i = 1; i < n; i++){
        if(postToBeViewed == NULL){
            return NULL;
        }//* if postToBeViewed is NULL

        postToBeViewed = postToBeViewed->prev;
    }//* for loop to get the post to be viewed

    if(postToBeViewed == NULL){
        return NULL;
    }//* if postToBeViewed is NULL

    socialMedia->lastViewedPost = postToBeViewed;

    if(socialMedia->lastViewedPostFixed == false){
        socialMedia->lastViewedPostFixed = true;
    }//* if lastViewedPost is NOT FIXED

    return postToBeViewed;
}

Post* currPost(){
    if(socialMedia->postSize == 0){
        return NULL;
    }//* if there are no posts

    if(socialMedia->lastViewedPostFixed == false){
        socialMedia->lastViewedPostFixed = true;
    }//* if lastViewedPost is NOT FIXED

    return socialMedia->lastViewedPost;
}

Post* nextPost(){
    //* This denotes the post posted right BEFORE the lastViewedPost
    if(socialMedia->postSize == 0){
        return NULL;
    }//* if there are no posts

    if(socialMedia->lastViewedPost == NULL){
        return NULL;
    }//* if lastViewedPost is NULL

    if(socialMedia->lastViewedPost->prev == NULL){
        return socialMedia->lastViewedPost;
    }//* if lastViewedPost is the first post

    socialMedia->lastViewedPost = socialMedia->lastViewedPost->prev;

    if(socialMedia->lastViewedPostFixed==false){
        socialMedia->lastViewedPostFixed=true;
    }

    return socialMedia->lastViewedPost;
}

Post* previousPost(){
    //* This denotes the post posted right AFTER the lastViewedPost

    if(socialMedia->lastViewedPost == NULL){
        return NULL;
    }//* if lastViewedPost is NULL

    if(socialMedia->lastViewedPost->next == NULL){
        return socialMedia->lastViewedPost;
    }//* if lastViewedPost is the last post

    socialMedia->lastViewedPost = socialMedia->lastViewedPost->next;

    if(socialMedia->lastViewedPostFixed==false){
        socialMedia->lastViewedPostFixed=true;
    }

    return socialMedia->lastViewedPost;
}

bool addComment(char* username, char* content){
    if(socialMedia->lastViewedPost == NULL){
        return false;
    }//* if there are no posts

    Comment* newComment = createComment(username, content);

    if(newComment == NULL){
        return false;
    }//* if createComment fails

    if(socialMedia->lastViewedPost->Comments == NULL){
        socialMedia->lastViewedPost->Comments = newComment;
        socialMedia->lastViewedPost->latestComment = newComment;
        socialMedia->lastViewedPost->commentSize++;
        return true;
    }//* if there are no comments

    socialMedia->lastViewedPost->latestComment->next = newComment;
    newComment->prev = socialMedia->lastViewedPost->latestComment;
    socialMedia->lastViewedPost->latestComment = newComment;
    socialMedia->lastViewedPost->commentSize++;

    return true;
}

bool deleteComment(int n){
    //* n denotes the nth recent comment, so its from the bottom, so from top its (commentSize - n + 1)th comment
    if(socialMedia->lastViewedPost == NULL){
        return false;
    }//* if there are no posts

    if(n > socialMedia->lastViewedPost->commentSize || n < 1){
        return false;
    }//* if n is greater than the number of comments

    Comment* commentToBeDeleted = socialMedia->lastViewedPost->latestComment;

    for(int i = 1; i < n; i++){
        if(commentToBeDeleted == NULL){
            return false;
        }//* if commentToBeDeleted is NULL

        commentToBeDeleted = commentToBeDeleted->prev;
    }//* for loop to get the comment to be deleted

    if(commentToBeDeleted == NULL){
        return false;
    }//* if commentToBeDeleted is NULL

    if(socialMedia->lastViewedPost->commentSize==1){
        socialMedia->lastViewedPost->latestComment = NULL;
        socialMedia->lastViewedPost->Comments = NULL;
        freeComment(commentToBeDeleted);
        commentToBeDeleted = NULL;
        socialMedia->lastViewedPost->commentSize--;
        return true;   
    }//* if there is only one comment

    if(commentToBeDeleted->prev == NULL){
        socialMedia->lastViewedPost->Comments = commentToBeDeleted->next;
        freeComment(commentToBeDeleted);
        commentToBeDeleted = NULL;
        socialMedia->lastViewedPost->commentSize--;
        return true;
    }//* if commentToBeDeleted is the first comment

    if(commentToBeDeleted->next == NULL){
        socialMedia->lastViewedPost->latestComment = commentToBeDeleted->prev;
        freeComment(commentToBeDeleted);
        commentToBeDeleted = NULL;
        socialMedia->lastViewedPost->commentSize--;
        return true;
    }//* if commentToBeDeleted is the last comment

    commentToBeDeleted->prev->next = commentToBeDeleted->next;
    commentToBeDeleted->next->prev = commentToBeDeleted->prev;

    freeComment(commentToBeDeleted);
    commentToBeDeleted = NULL;
    socialMedia->lastViewedPost->commentSize--;

    return true;
}

Comment* viewComments(){
    if(socialMedia->lastViewedPost == NULL){
        return NULL;
    }//* if there are no comments
    return socialMedia->lastViewedPost->Comments;
}

bool addReply(char* username, char* content, int n){
    //* reply to the nth recent comment of the lastViewedPost
    if(socialMedia->lastViewedPost == NULL){
        return false;
    }//* if there are no posts

    if(n > socialMedia->lastViewedPost->commentSize){
        return false;
    }//* if n is greater than the number of comments

    Comment* commentToReplyTo = socialMedia->lastViewedPost->latestComment;

    for(int i = 1; i < n; i++){
        if(commentToReplyTo == NULL){
            return false;
        }//* if commentToReplyTo is NULL

        commentToReplyTo = commentToReplyTo->prev;
    }//* for loop to get the comment to reply to

    if(commentToReplyTo == NULL){
        return false;
    }//* if commentToReplyTo is NULL

    Reply* newReply = createReply(username, content);

    if(newReply == NULL){
        return false;
    }//* if createReply fails

    if(commentToReplyTo->Replies == NULL){
        commentToReplyTo->Replies = newReply;
        commentToReplyTo->latestReply = newReply;
        commentToReplyTo->replySize++;
        return true;
    }//* if there are no replies

    commentToReplyTo->latestReply->next = newReply;
    newReply->prev = commentToReplyTo->latestReply;
    commentToReplyTo->latestReply = newReply;
    commentToReplyTo->replySize++;

    return true;
}

bool deleteReply(int n, int m){
    //* nth comment, mth reply
    if(socialMedia->lastViewedPost == NULL){
        return false;
    }//* if there are no posts

    if(n > socialMedia->lastViewedPost->commentSize){
        return false;
    }//* if n is greater than the number of comments

    Comment* commentToBeDeleted = socialMedia->lastViewedPost->latestComment;

    for(int i = 1; i < n; i++){
        if(commentToBeDeleted == NULL){
            return false;
        }//* if commentToBeDeleted is NULL

        commentToBeDeleted = commentToBeDeleted->prev;
    }//* for loop to get the comment to be deleted

    if(commentToBeDeleted == NULL){
        return false;
    }//* if commentToBeDeleted is NULL

    Reply* replyToBeDeleted = commentToBeDeleted->latestReply;

    if(m > commentToBeDeleted->replySize){
        return false;
    }//* if m is greater than the number of replies

    for(int i = 1; i < m; i++){
        if(replyToBeDeleted == NULL){
            return false;
        }//* if replyToBeDeleted is NULL

        replyToBeDeleted = replyToBeDeleted->prev;
    }//* for loop to get the reply to be deleted

    if(replyToBeDeleted == NULL){
        return false;
    }//* if replyToBeDeleted is NULL

    if(commentToBeDeleted->replySize==1){
        commentToBeDeleted->latestReply = NULL;
        commentToBeDeleted->Replies = NULL;
        freeReply(replyToBeDeleted);
        replyToBeDeleted = NULL;
        commentToBeDeleted->replySize--;
        return true;   
    }//* if there is only one reply

    if(replyToBeDeleted->prev == NULL){
        commentToBeDeleted->Replies = replyToBeDeleted->next;
        freeReply(replyToBeDeleted);
        replyToBeDeleted = NULL;
        commentToBeDeleted->replySize--;
        return true;
    }//* if replyToBeDeleted is the first reply

    if(replyToBeDeleted->next == NULL){
        commentToBeDeleted->latestReply = replyToBeDeleted->prev;
        freeReply(replyToBeDeleted);
        replyToBeDeleted = NULL;
        commentToBeDeleted->replySize--;
        return true;
    }//* if replyToBeDeleted is the last reply

    replyToBeDeleted->prev->next = replyToBeDeleted->next;
    replyToBeDeleted->next->prev = replyToBeDeleted->prev;

    freeReply(replyToBeDeleted);
    replyToBeDeleted = NULL;
    commentToBeDeleted->replySize--;

    return true;
}

void freePlatform(){
    if(socialMedia==NULL){
        return;
    }//* Incase exit called in first line

    Post* postToBeDeleted = socialMedia->Posts;
    Post* temp;

    while(postToBeDeleted!=NULL){
        temp = postToBeDeleted;
        postToBeDeleted=postToBeDeleted->next;
        freePost(temp);
    }//* Iterate through all the posts and delete each of them

    free(socialMedia);
    socialMedia = NULL;
}