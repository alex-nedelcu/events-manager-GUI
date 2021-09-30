//
// Created by Alex Nedelcu on 31.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_ICOMMAND_H
#define A10_915_NEDELCU_ALEXANDRU_1_ICOMMAND_H


class ICommand {
public:
    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;
};


#endif //A10_915_NEDELCU_ALEXANDRU_1_ICOMMAND_H
