#ifndef IMAGEEDITOR_MAKECOLLAGECOMMAND_H
#define IMAGEEDITOR_MAKECOLLAGECOMMAND_H


#include "ActiveCommand.h"

class MakeCollageCommand : public ActiveCommand {
public:
    MakeCollageCommand(Image* firstImage, Image* secondImage, CollageType type);

    void actualExecute() override;

private:
    Image* firstImage;
    Image* secondImage;
    CollageType type;
};


#endif //IMAGEEDITOR_MAKECOLLAGECOMMAND_H
