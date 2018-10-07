#ifndef FMIBOOK_USER_H
#define FMIBOOK_USER_H

#include "Post.h"

class User {
public:
    enum UserType {
        USER = 1 << 0,
        MODERATOR = 1 << 1 | USER,
        ADMIN = 1 << 2 | MODERATOR,
    };

    enum CommandStatus {
        SUCCESS,
        NAME_ALREADY_TAKEN,
        PRIVILEGE_VIOLATION,
        USER_NOT_FOUND,
        USER_BLOCKED,
        UNKNOWN,
    };

    struct UserCreateResult {
        CommandStatus status;
        User* user; // Will be null if status is not SUCCESS
    };

private:
    User(UserType type, const char* nickname, unsigned age);

public:
    ~User();

    User(const User&) = delete;
    void operator=(const User&) = delete;

    UserCreateResult createUser(UserType type, const char* nickname, unsigned age);
    CommandStatus changeBlockStatusOf(const char* nickname, bool block);
    CommandStatus removeUser(const char* nickname);
    CommandStatus createPost(const Post& post);

    const char* getNickname() const;
    unsigned getAge() const;
    bool isBlocked() const;
    UserType getType() const;
private:
    UserType type;
    char* nickname;
    unsigned age;
    bool blocked;

    bool isAdmin() const;
    bool isModerator() const;
};


#endif //FMIBOOK_USER_H
