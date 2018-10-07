#include <cstring>
#include <new>
#include "User.h"
#include "SocialNetwork.h"
#include "PostsDAO.h"

User::User(UserType type, const char *nickname, unsigned age)
: type(type)
, nickname(nullptr)
, blocked(false)
, age(age) {
    this->nickname = new char[strlen(nickname)];
    strcpy(this->nickname, nickname);
}

User::~User() {
    delete[] nickname;
}

User::UserCreateResult User::createUser(UserType type, const char *nickname, unsigned age) {
    UserCreateResult result;
    result.status = SUCCESS;
    result.user = nullptr;

    if(!isAdmin() || type == ADMIN) {
        result.status = PRIVILEGE_VIOLATION;
        return result;
    }

    UsersDAO* usersDAO = SocialNetwork::getInstance()->getUsersDAO();

    if (usersDAO->isUsernameTaken(nickname)) {
        result.status = NAME_ALREADY_TAKEN;
        return result;
    }

    try {
        result.user = new User(type, nickname, age);
    } catch (std::bad_alloc& e) {
        result.status = UNKNOWN;
    }

    if(result.status == SUCCESS) {
        bool success = usersDAO->addUser(result.user);
        if(!success) {
            result.status = UNKNOWN;
        }
    }

    return result;
}

const char *User::getNickname() const {
    return nickname;
}

unsigned User::getAge() const {
    return age;
}

bool User::isBlocked() const {
    return blocked;
}

User::UserType User::getType() const {
    return type;
}

bool User::isAdmin() const {
    return (type & ADMIN) == ADMIN;
}

bool User::isModerator() const {
    return (type & MODERATOR) == MODERATOR;
}

User::CommandStatus User::changeBlockStatusOf(const char *nickname, bool block) {
    if(!isModerator()) {
        return PRIVILEGE_VIOLATION;
    }

    UsersDAO* usersDAO = SocialNetwork::getInstance()->getUsersDAO();
    User* user = usersDAO->getByNickname(nickname);
    if(!user) {
        return USER_NOT_FOUND;
    }

    if(user->type == ADMIN) {
        return PRIVILEGE_VIOLATION;
    }

    user->blocked = block;
    return SUCCESS;
}

User::CommandStatus User::removeUser(const char *nickname) {
    if(!isAdmin()) {
        return PRIVILEGE_VIOLATION;
    }

    UsersDAO* usersDAO = SocialNetwork::getInstance()->getUsersDAO();
    if(!usersDAO->removeUser(nickname)) {
        return USER_NOT_FOUND;
    }

    return SUCCESS;
}

User::CommandStatus User::createPost(const Post &post) {
    if(blocked) {
        return USER_BLOCKED;
    }

    Post* newPost = new Post(post);
    PostsDAO* postsDAO = SocialNetwork::getInstance()->getPostsDAO();
    if(!postsDAO->addPost(newPost)) {
        return UNKNOWN;
    }

    return SUCCESS;
}

