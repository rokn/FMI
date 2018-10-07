#ifndef FMIBOOK_TEXTPOST_H
#define FMIBOOK_TEXTPOST_H

#include "Post.h"

class TextPost : public Post {
public:

    TextPost(const char *content);

    void writeAsHtml(std::ostream &stream) override;

private:
};


#endif //FMIBOOK_TEXTPOST_H
