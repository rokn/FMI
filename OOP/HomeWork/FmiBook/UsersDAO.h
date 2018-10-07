#ifndef FMIBOOK_USERSDAO_H
#define FMIBOOK_USERSDAO_H


#include "User.h"

class UsersDAO {
public:
    virtual bool addUser(User* user) = 0;
    virtual bool removeUser(const char* nickname) = 0;
    virtual User* getByNickname(const char* nickname) = 0;
    virtual bool isUsernameTaken(const char* nickname) = 0;
};


#endif //FMIBOOK_USERSDAO_H
