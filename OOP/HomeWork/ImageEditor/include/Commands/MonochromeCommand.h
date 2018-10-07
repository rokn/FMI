#ifndef IMAGEEDITOR_MONOCHROMECOMMAND_H
#define IMAGEEDITOR_MONOCHROMECOMMAND_H


#include "LazyCommand.h"

class MonochromeCommand : public LazyCommand {
public:
    MonochromeCommand();
    
    void actualExecute() override;
};


#endif //IMAGEEDITOR_MONOCHROMECOMMAND_H
