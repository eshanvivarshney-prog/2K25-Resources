# DSA ASSIGNMENT 1

## Roll No. 2023113024

## Name: Shreyas Deb

## Files included:

- `main.c` - The main file which contains the main function and the menu.
- `platform.h` and `platform.c` - Contains the functions for the platform.
- `post.h` and `post.c` - Contains the functions for the post.
- `comment.h` and `comment.c` - Contains the functions for the comment.
- `reply.h` and `reply.c` - Contains the functions for the reply.
- `helper.h` and `helper.c` - Contains the helper functions.

## Data Structures used:

- `struct platform` - Contains the details of the platform.

```
struct Platform{
    Post* Posts;
    Post* lastViewedPost;
    bool lastViewedPostFixed;
    Post* latestPost;
    int postSize;
};
```
- `struct post` - Contains the details of the post.

```
struct Post{
    char Username[128];
    char Caption[128];
    Comment* Comments;
    Comment* latestComment;
    Post* next;
    Post* prev;
    int commentSize;
};  
```

- `struct comment` - Contains the details of the comment.

```
struct Comment{
    char Username[128];
    char Content[128];
    Reply* Replies;
    Reply* latestReply;
    Comment* next;
    Comment* prev;
    int replySize;
};
```

- `struct reply` - Contains the details of the reply.

```
struct Reply{
    char Username[128];
    char Content[128];
    Reply* next;
    Reply* prev;
};
```

## Functions used:

- Inside `platform.c`:

```
Platform* createPlatform();
bool addPost(char* username, char* caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();
bool addComment(char* username, char* content);
bool deleteComment(int n);
Comment* viewComments();
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);
void freePlatform();
```

- Inside `post.c`:

```
Post* createPost(char* username, char* caption);
void freePost(Post* post);
```

- Inside `comment.c`:

```
Comment* createComment(char* username, char* content);
void freeComment(Comment* comment);
```

- Inside `reply.c`:

```
Reply* createReply(char* username, char* content);
void freeReply(Reply* reply);
```

- Inside `helper.c`:

```
void getCommand(char* command);
void getUsername(char* username);
void getContent(char* content);
void getPostNumber(int *postNumber);
void getCommentNumber(int *commentNumber);
void getReplyNumber(int *replyNumber);
void displayPost(Post* post);
void displayAllComments(Comment* comment);
```

## Assumptions:

- The username and caption of the post are limited to 128 characters.
- The content of the comment and reply are limited to 128 characters.
- The username has no spaces.
- The caption of the post can have spaces.
- Empty posts, comments and replies are not allowed.
- Input will be given one by one.
- Only one platform can be created at a time.

## How to run:

- Run `make` to compile the code. This also runs the code for the first time.
- Run `make run` to run the code.
- Run `make clean` to remove the executable.

