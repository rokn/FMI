#ifndef FMIBOOK_IMAGEPOST_H
#define FMIBOOK_IMAGEPOST_H


#include "Post.h"

class ImagePost : public Post{
public:
    ImagePost(const char *content);

    void writeAsHtml(std::ostream &stream) override;
};


#endif //FMIBOOK_IMAGEPOST_H
