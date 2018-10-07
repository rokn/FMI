#include "ImagePost.h"

ImagePost::ImagePost(const char *content) : Post(content) {}

void ImagePost::writeAsHtml(std::ostream &stream) {
    stream << "<img src=\"" << getContent() << "\">" << std::endl;
}
