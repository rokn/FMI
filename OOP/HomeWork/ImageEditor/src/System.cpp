#include "System.h"

System::System()
: currentSession(nullptr) {

}

System::~System() {
    for (unsigned i = 0; i < sessions.getSize(); ++i) {
        delete sessions[i];
    }

    sessions.clear();
}

Session * System::addSession(Session *newSession) {
    sessions.pushBack(newSession);
    currentSession = newSession;
    return newSession;
}

Session * System::switchSession(unsigned id) {
    for (unsigned i = 0; i < sessions.getSize(); ++i) {
        if(sessions[i]->getId() == id) {
            currentSession = sessions[i];
            return currentSession;
        }
    }

    return nullptr;
}

Session *System::getSession() {
    return currentSession;
}
