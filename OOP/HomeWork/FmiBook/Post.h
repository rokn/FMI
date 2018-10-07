#ifndef FMIBOOK_POST_H
#define FMIBOOK_POST_H


#include <ostream>

class Post {
public:
    Post(const char* content, const char* poster);
    virtual ~Post() = default;
    virtual void writeAsHtml(std::ostream& stream) = 0;

    unsigned getId() const;
    void setId(unsigned id); // TODO: needs work

protected:
    const char* getContent() const;

private:
    unsigned id;
    char* content;
    char* poster;

    void setContent(const char* content);
    void setPoster(const char* poster);
};


#endif //FMIBOOK_POST_H
