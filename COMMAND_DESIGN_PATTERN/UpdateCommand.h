//
// Created by Alex Nedelcu on 31.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_UPDATECOMMAND_H
#define A10_915_NEDELCU_ALEXANDRU_1_UPDATECOMMAND_H


#include <QTableView>
#include "../BUSINESS/AdminService.h"
#include "ICommand.h"

class UpdateCommand : public ICommand {
private:
    // object that handles the command //
    AdminService* mAdminService;
    QTableView* mView;

    // arguments of the command //
    int mID;
    const std::string& mTitle;
    const std::string& mDescription;
    int mDay;
    int mMonth;
    int mYear;
    const std::string& mTime;
    int mParticipantsNumber;
    const std::string& mLink;

    // arguments of the reverse command //
    int mInitialID;
    std::string mInitialTitle;
    std::string mInitialDescription;
    int mInitialDay;
    int mInitialMonth;
    int mInitialYear;
    std::string mInitialTime;
    int mInitialParticipantsNumber;
    std::string mInitialLink;

public:
    explicit UpdateCommand(AdminService* adminService, QTableView* view, int ID, const std::string& title, const std::string& description, int day, int month, int year, const std::string& time, int participantsNumber, const std::string& link);

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif //A10_915_NEDELCU_ALEXANDRU_1_UPDATECOMMAND_H
