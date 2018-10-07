#include "TextPost.h"

TextPost::TextPost(const char *content) : Post(content) {}

void TextPost::writeAsHtml(std::ostream &stream) {
    stream << getContent() << std::endl;
}
