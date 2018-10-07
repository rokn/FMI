#ifndef IMAGEEDITOR_NEGATIVECOMMAND_H
#define IMAGEEDITOR_NEGATIVECOMMAND_H


#include "LazyCommand.h"

class NegativeCommand : public LazyCommand {
public:
    NegativeCommand();
    
    void actualExecute() override;
};


#endif //IMAGEEDITOR_NEGATIVECOMMAND_H
