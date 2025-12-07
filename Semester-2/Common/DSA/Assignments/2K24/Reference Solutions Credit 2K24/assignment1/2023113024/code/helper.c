#include<stdio.h>
#include<stdlib.h>
#include "platform.h"
#include "helper.h"
#define FLUSH while(getchar()!='\n')

extern Platform* socialMedia;

void getCommand(char* command){
    printf("Enter command (or type 'help')>> ");
    scanf("%s", command);
    FLUSH;
}

void getUsername(char* username){
    printf("Enter username >> ");
    scanf("%s", username);
    FLUSH;
}

void getContent(char* content){
    printf("Enter content >> ");
    scanf("%[^\n]s", content);
    FLUSH;
}

void getPostNumber(int *postNumber){
    printf("Enter post number >> ");
    scanf("%d", postNumber);
    FLUSH;
}

void getCommentNumber(int *commentNumber){
    printf("Enter comment number >> ");
    scanf("%d", commentNumber);
    FLUSH;
}

void getReplyNumber(int *replyNumber){
    printf("Enter reply number >> ");
    scanf("%d", replyNumber);
    FLUSH;
}

void displayPost(Post* post){
    printf("%s > %s\n", post->Username, post->Caption);

    if(post->Comments == NULL){
        return;
    }//* if there are no comments

    printf("Do you wish to see the comments/replies? (y/n) >> ");
    char choice;
    scanf("%c", &choice);
    FLUSH;

    if(choice == 'n') return;
    if(choice != 'y'){
        printf("Invalid choice\n");
        return;
    }

    Comment* currentComment = post->Comments;

    while(currentComment != NULL){
        printf("\t%s > %s\n", currentComment->Username, currentComment->Content);

        Reply* currentReply = currentComment->Replies;

        while(currentReply != NULL){
            printf("\t\t%s > %s\n", currentReply->Username, currentReply->Content);
            currentReply = currentReply->next;
        }

        currentComment = currentComment->next;
    }
}

void displayAllComments(Comment* comment){
    Comment* currentComment = comment;

    while(currentComment != NULL){
        printf("%s > %s\n", currentComment->Username, currentComment->Content);

        Reply* currentReply = currentComment->Replies;

        while(currentReply != NULL){
            printf("\t\t%s > %s\n", currentReply->Username, currentReply->Content);
            currentReply = currentReply->next;
        }

        currentComment = currentComment->next;
    }
}
