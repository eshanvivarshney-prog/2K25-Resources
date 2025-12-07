#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "platform.h"
#include <string.h>
#define flush while(getchar()!='\n');
int main(){
    char s[100];
    strcpy(s,"-h");//prints the command list once.
    while(1){
        //takes input in the end.
        if(!strcmp(s,"create_platform")){
            if(createPlatform()!=NULL){
                printf("The platform has been successfully created.\n");
            }
            else{
                printf("The platform could not be successfully created.\n");
            }
        }
        else if(!strcmp(s,"add_post")){
            char u[100],c[100];
            scanf("%[^\n]s",u);
            flush;
            scanf("%[^\n]s",c);
            flush;
            if(addPost(u,c)){
                printf("Post successfully added to the platform\n");
            }
            else{
                printf("Post could not be added successfully\n");
            }
        }
        else if(!strcmp(s,"delete_post")){
            int n;
            scanf("%d",&n);
            flush;
            if(deletePost(n)){
                printf("Post succesfully deleted\n");
            }
            else{
                printf("Post could not be successfully deleted\n");
            }
        }
        else if(!strcmp(s,"view_post")){
            int n;
            scanf("%d",&n);
            flush;
            Post * p = viewPost(n);
            if(p==NULL){
                printf("The posts could not be successfully viewed\n");
            }
            else{
                printf("Username : %s  Caption : %s\n",p->Username,p->Caption);
            }
        }
        else if(!strcmp(s,"current_post")){
            Post * p = currPost();
            if(p==NULL){
                printf("The current post could not be viewed\n");
            }
            else{
                printf("Username : %s  Caption : %s\n",p->Username,p->Caption);
            }
        }
        else if(!strcmp(s,"previous_post")){
            Post * p = previousPost();
            if(p==NULL){
                printf("The previous post could not be viewed\n");
            }
            else{
                printf("Username : %s  Caption : %s\n",p->Username,p->Caption);
            }
        }
        else if(!strcmp(s,"next_post")){
            Post * p = nextPost();
            if(p==NULL){
                printf("The next post could not be viewed\n");
            }
            else{
                printf("Username : %s  Caption : %s\n",p->Username,p->Caption);
            }
        }
        else if(!strcmp(s,"add_comment")){
            char u[100],c[100];
            scanf("%[^\n]s",u);
            flush;
            scanf("%[^\n]s",c);
            flush;

            if(addComment(u,c)){
                printf("Comment successfully added to the lastViewedPost\n");
            }
            else{
                printf("Comment could not be added.\n");
            }
        }
        else if(!strcmp(s,"view_all_comments") || !strcmp(s,"view_comments")){
            Comment * comment = viewComments();
            if(comment== NULL){
                printf("No comments to be shown.\n");
            }
            else{
                while(comment!=NULL){
                    printf("Username : %s  Content : %s\n",comment->Username,comment->Content);
                    Reply * traverseReplies = comment->Replies;
                    while(traverseReplies!=NULL){
                        printf("\tUsername : %s  Content : %s\n",traverseReplies->Username,traverseReplies->Content);
                        traverseReplies = traverseReplies->next;
                    }
                    comment = comment->next;
                }
            }
        }
        else if(!strcmp(s,"delete_comment")){
            int n;
            scanf("%d",&n);
            flush;
            if(deleteComment(n)){
                printf("Comment successfully deleted\n");
            }
            else{
                printf("Comment could not be deleted.\n");
            }
        }
        else if(!strcmp(s,"add_reply")){
            char u[100],c[100];
            scanf("%[^\n]s",u);
            flush;
            scanf("%[^\n]s",c);
            flush;
            int n;
            scanf("%d",&n);
            if(addReply(u,c,n)){
                printf("Reply successfully added to the Comment\n");
            }
            else{
                printf("Reply could not be added successfully\n");
            }
        }
        else if(!strcmp(s,"delete_reply")){
            printf("(nth recent comment's mth recent reply is to be deleted)\nEnter n\n");
            int n,m;
            scanf("%d",&n);
            flush;
            printf("Enter m\n");
            scanf("%d",&m);
            flush;
            if(deleteReply(n,m)){
                printf("Reply successfully deleted.\n");
            }
            else{
                printf("Reply could not be deleted.\n");
            }
        }
        else if(!strcmp(s,"help") || !strcmp(s,"-h")){
            printf("The menu is as follows: \ncreate_platform \nadd_post \ndelete_post \nview_post \ncurrent_post \nprevious_post \nnext_post \nadd_comment \nview_comments or view_all_comments \ndelete_comment \nadd_reply \ndelete_reply \nhelp or -h\n");
        }
        else{
            printf("The choice given is incorrect. \nUse -h or help to get more info\n");
        }
        scanf("%s",s);
        flush;
    }
    return 0;
}