#ifndef IMAGEEDITOR_IMAGEENUMS_H
#define IMAGEEDITOR_IMAGEENUMS_H

enum Rotation {
    NONE  = 0,
    RIGHT = 1,
    DOWN  = 2,
    LEFT  = 3,
};

enum RotationDirection {
    ROTATE_LEFT  = -1,
    ROTATE_RIGHT =  1,
};

enum ImageType {
    MONOCHROME = 0,
    GRAY_SCALE  = 1,
    COLOR      = 2
};

enum CollageType {
    HORIZONTAL,
    VERTICAL,
};

typedef unsigned char Byte;

struct Dimensions {
    Dimensions() : Dimensions(0,0) {}
    Dimensions(unsigned width, unsigned height)
            : width(width)
            , height (height) {}

    unsigned width;
    unsigned height;

    unsigned pixelCount() const {
        return width*height;
    }
};

class Color {
public:
    static const Byte MAX_VALUE = 0xFF;

    // Colors
    static const unsigned WHITE = 0xFFFFFF;
    static const unsigned BLACK = 0x0;

    Color(unsigned color = BLACK) : color(color) {}
    Color(Byte r, Byte g, Byte b)
            : color((r << RED_OFS) | (g << GREEN_OFS) | (b << BLUE_OFS)) {}

    Byte r() const {
        return (Byte)((color & (MAX_VALUE << RED_OFS)) >> RED_OFS);
    }

    Byte g() const {
        return (Byte)((color & (MAX_VALUE << GREEN_OFS)) >> GREEN_OFS);
    }

    Byte b() const {
        return (Byte)((color & (MAX_VALUE << BLUE_OFS)) >> BLUE_OFS);
    }

    void setR(Byte red) {
        color &= ~(MAX_VALUE << RED_OFS);
        color |= red << RED_OFS;
    }

    void setG(Byte green) {
        color &= ~(MAX_VALUE << GREEN_OFS);
        color |= green << GREEN_OFS;
    }

    void setB(Byte blue) {
        color &= ~(MAX_VALUE << BLUE_OFS);
        color |= blue << BLUE_OFS;
    }

    void toMonochrome() {
        Byte grayScale = getGrayScaleValue();
        if(grayScale > 127) {
            color = WHITE;
        } else {
            color = BLACK;
        }
    }

    void toGrayScale() {
        Byte grayScale = getGrayScaleValue();
        color = (grayScale << RED_OFS) | (grayScale << GREEN_OFS) | (grayScale << BLUE_OFS);
    }

    void invert() {
        setR(MAX_VALUE - r());
        setG(MAX_VALUE - g());
        setB(MAX_VALUE - b());
    }

    bool isMonochrome() const {
        return color == BLACK || color == WHITE;
    }

    bool isGrayScale() const {
        return r() == g() && r() == b();
    }

private:
    unsigned color;

    // Masks
    static const Byte RED_OFS = 16;
    static const Byte GREEN_OFS = 8;
    static const Byte BLUE_OFS = 0;

    // Gray scale multipliers
    static constexpr float RED_MULTIPLIER = 0.21f;
    static constexpr float GREEN_MULTIPLIER = 0.72f;
    static constexpr float BLUE_MULTIPLIER = 0.07f;

    Byte getGrayScaleValue() const {
        return (Byte) (r() * RED_MULTIPLIER +
                       g() * GREEN_MULTIPLIER +
                       b() * BLUE_MULTIPLIER);
    }
};

#endif //IMAGEEDITOR_IMAGEENUMS_H
