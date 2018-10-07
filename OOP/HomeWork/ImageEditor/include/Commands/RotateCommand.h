#ifndef IMAGEEDITOR_ROTATECOMMAND_H
#define IMAGEEDITOR_ROTATECOMMAND_H


#include "LazyCommand.h"
#include "Image.h"

class RotateCommand : public LazyCommand{
public:
    explicit RotateCommand(RotationDirection direction);

    void actualExecute() override;

private:
    RotationDirection direction;
};


#endif //IMAGEEDITOR_ROTATECOMMAND_H
