#ifndef IMAGEEDITOR_LAZYCOMMAND_H
#define IMAGEEDITOR_LAZYCOMMAND_H


#include "ImageCommand.h"

class LazyCommand : public ImageCommand {
public:
    void execute() final;
};


#endif //IMAGEEDITOR_LAZYCOMMAND_H
