//
// Created by Alex Nedelcu on 31.05.2021.
//

#include "CommandManager.h"

CommandManager::CommandManager()
        : mUndoStack{std::stack<std::shared_ptr<ICommand>>{}},
          mRedoStack{std::stack<std::shared_ptr<ICommand>>{}} {}

void CommandManager::executeCommand(std::shared_ptr<ICommand> command) {
    mRedoStack = std::stack<std::shared_ptr<ICommand>>{}; // clear the redo stack
    command->execute();
    mUndoStack.push(command);
}

void CommandManager::undo() {
    if (mUndoStack.size() == 0)
        return;

    mUndoStack.top()->undo();
    mRedoStack.push(mUndoStack.top());
    mUndoStack.pop();
}

void CommandManager::redo() {
    if (mRedoStack.size() == 0)
        return;

    mRedoStack.top()->redo();
    mUndoStack.push(mRedoStack.top());
    mRedoStack.pop();
}
