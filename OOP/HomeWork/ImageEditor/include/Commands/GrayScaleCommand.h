#ifndef IMAGEEDITOR_GRAYSCALECOMMAND_H
#define IMAGEEDITOR_GRAYSCALECOMMAND_H


#include "LazyCommand.h"

class GrayScaleCommand : public LazyCommand {
public:
    GrayScaleCommand();

    void actualExecute() override;
};


#endif //IMAGEEDITOR_GRAYSCALECOMMAND_H
