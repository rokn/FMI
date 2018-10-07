#ifndef FMIBOOK_URLPOST_H
#define FMIBOOK_URLPOST_H


#include "Post.h"

class UrlPost : public Post{
public:
    UrlPost(const char *content, const char* url);
    ~UrlPost();
    UrlPost(const UrlPost& other);
    UrlPost& operator=(const UrlPost& other);

    void writeAsHtml(std::ostream &stream) override;

private:
    char* url;

    void setUrl(const char *url);
};


#endif //FMIBOOK_URLPOST_H
