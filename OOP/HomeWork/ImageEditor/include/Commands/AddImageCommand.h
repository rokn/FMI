#ifndef IMAGEEDITOR_ADDIMAGECOMMAND_H
#define IMAGEEDITOR_ADDIMAGECOMMAND_H


#include "ActiveCommand.h"

class AddImageCommand : public ActiveCommand {
public:
    explicit AddImageCommand(Image* newImage);
    ~AddImageCommand();

    void actualExecute() override;

private:
    Image* newImage;
};


#endif //IMAGEEDITOR_ADDIMAGECOMMAND_H
