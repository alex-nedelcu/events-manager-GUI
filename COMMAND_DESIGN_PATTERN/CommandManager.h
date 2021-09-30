//
// Created by Alex Nedelcu on 31.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_COMMANDMANAGER_H
#define A10_915_NEDELCU_ALEXANDRU_1_COMMANDMANAGER_H

#include <stack>
#include "ICommand.h"

class CommandManager {
private:
    std::stack<std::shared_ptr<ICommand>> mUndoStack;
    std::stack<std::shared_ptr<ICommand>> mRedoStack;

public:
    CommandManager();

    void executeCommand(std::shared_ptr<ICommand> command);

    void undo();

    void redo();

};


#endif //A10_915_NEDELCU_ALEXANDRU_1_COMMANDMANAGER_H
