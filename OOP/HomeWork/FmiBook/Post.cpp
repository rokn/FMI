#include <cstring>
#include "Post.h"

Post::Post(const char *content, const char* poster)
: content(nullptr)
, poster(nullptr){
    setContent(content);
    setPoster(poster);
}

Post::~Post() {
    delete[] content;
}

const char *Post::getContent() const {
    return content;
}

void Post::setContent(const char *content) {
    if(!content) {
        return;
    }

    char* newContent = new char[strlen(content)];
    strcpy(newContent, content);

    delete[] this->content;
    this->content = newContent;
}

unsigned Post::getId() const {
    return id;
}

void Post::setId(unsigned id) {
    this->id = id;
}

void Post::setPoster(const char *poster) {
    if(!poster) {
        return;
    }

    char* newPoster = new char[strlen(poster)];
    strcpy(newPoster, poster);

    delete[] this->poster;
    this->poster = newPoster;
}
