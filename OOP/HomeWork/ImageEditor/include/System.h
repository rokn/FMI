#ifndef IMAGEEDITOR_SYSTEM_H
#define IMAGEEDITOR_SYSTEM_H


#include "Session.h"

class System {
public:
    System();
    System(const System& o) = delete;
    void operator=(const System& o) = delete;
    ~System();

    Session* addSession(Session* newSession);
    Session* switchSession(unsigned id);

    Session* getSession();

private:
    Vector<Session*> sessions;

    Session* currentSession;
};


#endif //IMAGEEDITOR_SYSTEM_H
