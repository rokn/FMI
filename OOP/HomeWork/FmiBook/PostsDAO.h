#ifndef FMIBOOK_POSTSDAO_H
#define FMIBOOK_POSTSDAO_H

#include "Post.h"

class PostsDAO {
public:
    virtual bool addPost(Post *post) = 0;
    virtual Post* getPost(unsigned id) = 0;
    virtual Post* getPostsBy(const char* nickname) = 0;
    virtual unsigned getPostCount(const char* nickname) = 0;
};


#endif //FMIBOOK_POSTSDAO_H
