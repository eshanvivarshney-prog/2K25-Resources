#include "platform.h"
#include "helper.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FLUSH while(getchar()!='\n');

int main(void){
    extern Platform* socialMedia;
    socialMedia = NULL;

    while(true){
        printf("===========================SOCIALE MEDIOS===========================\n");

        char command[20];
        getCommand(command);

        if(strcmp(command, "exit")==0){
            freePlatform();
            exit(0);

        }else if(strcmp(command, "help")==0){
            printf("create_platform\n");
            printf("add_post <username> <caption>\n");
            printf("delete_post <nth recent post>\n");
            printf("view_post <nth recent>\n");
            printf("current_post\n");
            printf("next_post\n");
            printf("previous_post\n");
            printf("add_comment <username> <content>\n");
            printf("delete_comment <nth recent comment>\n");
            printf("view_comments\n");
            printf("add_reply <username> <content> <comment number>\n");
            printf("delete_reply <nth recent comment> <mth recent reply>\n");
            printf("display_all_posts\n");
            printf("help\n");
            printf("exit\n");
        
        }else if(strcmp(command,"create_platform")==0){
            if(socialMedia != NULL){
                printf("ERROR::Platform already created, type `exit` to exit\n");
                continue;
            }//! if socialMedia is not NULL (platform already created

            socialMedia = createPlatform();

            if(socialMedia == NULL){
                printf("ERROR::Platform could not be created\n");
            }else{
                printf("Platform created successfully\n");
            } 

        }else if(socialMedia==NULL){
            printf("ERROR::Platform not created yet, type `create_platform` or `exit`\n");

        }else if(strcmp(command,"add_post")==0){
            char username[128];
            char caption[128];

            getUsername(username);
            getContent(caption);

            bool success = addPost(username, caption);

            if(success){
                printf("Post added successfully\n");
            }else{
                printf("ERROR::Post could not be added\n");
            }

        }else if(strcmp(command, "delete_post")==0){
            int number;
            getPostNumber(&number);

            bool success = deletePost(number);

            if(success){
                printf("Post deleted successfully\n");
            }else{
                printf("ERROR::Post could not be deleted\n");
            }

        }else if(strcmp(command, "view_post")==0){
            int number;
            getPostNumber(&number);
            
            Post* requestedPost = viewPost(number);
            
            if(requestedPost == NULL){
                printf("ERROR::Requested post does not exist\n");
                continue;
            
            }

            displayPost(requestedPost);

        }else if(strcmp(command, "current_post")==0){
            Post* currentPost = currPost();      

            if(currentPost == NULL){
                printf("ERROR::Requested post does not exist\n");
                continue;
            }

            displayPost(currentPost);

        }else if(strcmp(command, "next_post")==0){
            Post* requestedPost = nextPost();
            
            if(requestedPost == NULL){
                printf("ERROR::Requested post does not exist\n");
                continue;
            }

            displayPost(requestedPost);

        }else if(strcmp(command, "previous_post")==0){
            Post* requestedPost = previousPost();
            
            if(requestedPost == NULL){
                printf("ERROR::Requested post does not exist\n");
                continue;
            }

            displayPost(requestedPost);

        }else if(strcmp(command, "add_comment")==0){
            char username[128];
            char comment[128];

            getUsername(username);
            getContent(comment);

            bool success = addComment(username, comment);

            if(success){
                printf("Comment added successfully\n");
            }else{
                printf("ERROR::Comment could not be added\n");
            }

        }else if(strcmp(command, "delete_comment")==0){
            int number;
            getCommentNumber(&number);

            bool success = deleteComment(number);

            if(success){
                printf("Comment deleted successfully\n");
            }else{
                printf("ERROR::Comment could not be deleted\n");
            }

        }else if(strcmp(command, "view_comments")==0){
            Comment* comment = viewComments();

            if(comment == NULL){
                printf("ERROR::Requested comments don't exist\n");
                continue;
            }

            displayAllComments(comment);

        }else if(strcmp(command, "add_reply")==0){
            char username[128];
            char reply[128];
            int number;

            getUsername(username);
            getContent(reply);
            getCommentNumber(&number);

            bool success = addReply(username, reply, number);

            if(success){
                printf("Reply added successfully\n");
            }else{
                printf("ERROR::Reply could not be added\n");
            }

        }else if(strcmp(command, "delete_reply")==0){
            int number1, number2;
            getCommentNumber(&number1);
            getReplyNumber(&number2);

            bool success = deleteReply(number1, number2);

            if(success){
                printf("Reply deleted successfully\n");
            }else{
                printf("ERROR::Reply could not be deleted\n");
            }
        }else{
            printf("ERROR::Invalid command entered... try again\n");
        }
    }   
}