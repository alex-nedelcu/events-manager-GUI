//
// Created by Alex Nedelcu on 31.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_ADDCOMMAND_H
#define A10_915_NEDELCU_ALEXANDRU_1_ADDCOMMAND_H


#include <QTableView>
#include "../BUSINESS/AdminService.h"
#include "ICommand.h"

class AddCommand : public ICommand {
private:
    // object that handles the command //
    AdminService* mAdminService;
    QTableView* mView;

    // arguments of the command //
    int mID;
    std::string mTitle;
    std::string mDescription;
    int mDay;
    int mMonth;
    int mYear;
    std::string mTime;
    int mParticipantsNumber;
    std::string mLink;

    // arguments of the reverse command //
    int mAddedEventID;

public:
    explicit AddCommand(AdminService* adminService, QTableView* view, int ID, std::string title, std::string description, int day, int month, int year, std::string time, int participantsNumber, std::string link);

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif //A10_915_NEDELCU_ALEXANDRU_1_ADDCOMMAND_H
