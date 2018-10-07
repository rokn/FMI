#ifndef IMAGEEDITOR_SESSION_H
#define IMAGEEDITOR_SESSION_H


#include "Commands/ImageCommandContainer.h"

class Session : public ImageCommandContainer {
public:
    explicit Session(const Vector<Image*>& startingImages);
    ~Session();

    Vector<Image *> &getImages() override;
    Vector<ImageCommand *> &getQueuedCommands() override;

    unsigned getId() const;

    void addCommand(ImageCommand* command);
    bool undoCommand();

    void save();

    void printInfo() const;

private:
    static unsigned ID_COUNTER;

    Vector<Image *> addedImages;
    Vector<ImageCommand *> queuedLazyCommands;

    Vector<ImageCommand *> commands;
    unsigned id;

    const char *getTimeSuffix() const;

    void clearCommands();
};


#endif //IMAGEEDITOR_SESSION_H
