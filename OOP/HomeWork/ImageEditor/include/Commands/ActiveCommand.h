#ifndef IMAGEEDITOR_ACTIVECOMMAND_H
#define IMAGEEDITOR_ACTIVECOMMAND_H


#include "ImageCommand.h"

class ActiveCommand : public ImageCommand{
public:
    void execute() final;
};


#endif //IMAGEEDITOR_ACTIVECOMMAND_H
