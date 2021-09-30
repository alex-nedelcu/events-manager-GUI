//
// Created by Alex Nedelcu on 31.05.2021.
//

#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(AdminService* adminService, QTableView* view, int ID, const std::string& title, const std::string& description, int day, int month, int year, const std::string& time, int participantsNumber, const std::string& link)
        : mAdminService{adminService},
          mView{view},
          mID{ID},
          mTitle{title},
          mDescription{description},
          mDay{day}, mMonth{month}, mYear{year},
          mTime{time},
          mParticipantsNumber{participantsNumber}, mLink{link} {}

void UpdateCommand::execute() {
    Event initialEvent = mAdminService->updateEvent(mID, mTitle, mDescription, mTime, mParticipantsNumber, mLink, mDay, mMonth, mYear);

    mInitialID = initialEvent.getID();
    mInitialTitle = initialEvent.getTitle();
    mInitialDescription = initialEvent.getDescription();
    mInitialDay = initialEvent.getDate().getDay();
    mInitialMonth = initialEvent.getDate().getMonth();
    mInitialYear = initialEvent.getDate().getYear();
    mInitialTime = initialEvent.getTime();
    mInitialParticipantsNumber = initialEvent.getParticipantsNumber();
    mInitialLink = initialEvent.getLink();
}

void UpdateCommand::undo() {
    mAdminService->updateEvent(mInitialID, mInitialTitle, mInitialDescription, mInitialTime, mInitialParticipantsNumber, mInitialLink, mInitialDay, mInitialMonth, mInitialYear);
}

void UpdateCommand::redo() {
    mAdminService->updateEvent(mID, mTitle, mDescription, mTime, mParticipantsNumber, mLink, mDay, mMonth, mYear);
}
