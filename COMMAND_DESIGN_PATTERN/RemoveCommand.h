//
// Created by Alex Nedelcu on 31.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_REMOVECOMMAND_H
#define A10_915_NEDELCU_ALEXANDRU_1_REMOVECOMMAND_H


#include <QTableView>
#include "../BUSINESS/AdminService.h"
#include "ICommand.h"

class RemoveCommand : public ICommand {
private:
    // object that handles the command //
    AdminService* mAdminService;
    QTableView* mView;

    // arguments of the command //
    int mRemoveID;

    // arguments of the reverse command //
    int mID;
    std::string mTitle;
    std::string mDescription;
    int mDay;
    int mMonth;
    int mYear;
    std::string mTime;
    int mParticipantsNumber;
    std::string mLink;

public:
    explicit RemoveCommand(AdminService* adminService, QTableView* view, int removeID);

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif //A10_915_NEDELCU_ALEXANDRU_1_REMOVECOMMAND_H
