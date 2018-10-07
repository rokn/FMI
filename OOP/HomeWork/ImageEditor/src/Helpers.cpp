#include <cstring>
#include "Helpers.h"

unsigned Helpers::mod(int k, int n) {
    int kModN = k % n;
    return (unsigned)((kModN >= 0) ? kModN : n+kModN);
}

unsigned Helpers::mapRanges(unsigned minFrom, unsigned maxFrom, unsigned minTo, unsigned maxTo, unsigned value) {
    maxFrom -= minFrom;
    value -= minFrom;
    float map = (float)value / maxFrom;
    return (unsigned int)(minTo + (maxTo - minTo) * map);
}

const char *Helpers::getWithoutExtension(const char *filename, char* ext) {
    size_t len = strlen(filename);
    size_t i = len - 1;
    for (; i > 0; --i) {
        if(filename[i] == '.') {
            break;
        }
    }

    if(i==0) {
        i = len;
    } else {
        if(ext != nullptr) {
            strcpy(ext, filename + i);
        }
    }

    char* withoutExt = new char[i + 1];
    strncpy(withoutExt, filename, i);
    withoutExt[i] = '\0';

    return withoutExt;
}
