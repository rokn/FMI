#ifndef IMAGEEDITOR_HELPERS_H
#define IMAGEEDITOR_HELPERS_H

namespace Helpers {
    unsigned mod(int k, int n);

    unsigned mapRanges(unsigned minFrom, unsigned maxFrom, unsigned minTo, unsigned maxTo, unsigned value);

    const char* getWithoutExtension(const char* filename, char* ext = nullptr);
}


#endif //IMAGEEDITOR_HELPERS_H
