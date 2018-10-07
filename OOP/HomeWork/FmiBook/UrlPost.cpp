#include <cstring>
#include "UrlPost.h"

UrlPost::UrlPost(const char *content, const char *url)
: Post(content)
, url(nullptr) {
    setUrl(url);
}

void UrlPost::setUrl(const char *url) {
    if(!url) {
        return;
    }

    char* newUrl = new char[strlen(url)];
    strcpy(newUrl, url);

    delete[] this->url;
    this->url = newUrl;
}

void UrlPost::writeAsHtml(std::ostream &stream) {
    stream << "<a href=\"" << url << "\">" << getContent() << "</a>" << std::endl;
}

UrlPost::~UrlPost() {
    delete[] url;
}

UrlPost::UrlPost(const UrlPost &other)
: UrlPost(other.getContent(), other.url) { }

UrlPost &UrlPost::operator=(const UrlPost &other) {
    if(this != &other) {
        Post::operator=(other);
        setUrl(other.url);
    }

    return *this;
}
