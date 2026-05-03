#ifndef __HELPER_H__
#define __HELPER_H__
#include "platform.h"

// Helper functions
void getCommand(char* command);
void getUsername(char* username);
void getContent(char* content);
void getPostNumber(int *postNumber);
void getCommentNumber(int *commentNumber);
void getReplyNumber(int *replyNumber);
void displayPost(Post* post);
void displayAllComments(Comment* comment);

#endif