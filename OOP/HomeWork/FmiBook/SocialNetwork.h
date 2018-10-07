#ifndef FMIBOOK_FMIBOOK_H
#define FMIBOOK_FMIBOOK_H


#include "UsersDAO.h"

class SocialNetwork {
private:
    SocialNetwork();
    ~SocialNetwork();

public:
    static SocialNetwork* getInstance();

    UsersDAO* getUsersDAO();
    PostsDAO* getPostsDAO();
};


#endif //FMIBOOK_FMIBOOK_H
