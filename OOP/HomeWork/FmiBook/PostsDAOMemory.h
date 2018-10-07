#ifndef FMIBOOK_POSTSDAOMEMORY_H
#define FMIBOOK_POSTSDAOMEMORY_H


#include "Post.h"
#include "Vector.h"
#include "PostsDAO.h"

class PostsDAOMemory : PostsDAO{
public:
    PostsDAOMemory();
    PostsDAOMemory(const PostsDAOMemory&) = delete;
    void operator=(const PostsDAOMemory&) = delete;
    ~PostsDAOMemory();

private:
    bool addPost(Post *post) override;

    Post *getPost(unsigned id) override;

    Post *getPostsBy(const char *nickname) override;

    unsigned int getPostCount(const char *nickname) override;

private:
    Vector<Post*> posts;

    unsigned int getNewId();

    unsigned int currentId;
};


#endif //FMIBOOK_POSTSDAOMEMORY_H
