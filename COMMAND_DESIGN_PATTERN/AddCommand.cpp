//
// Created by Alex Nedelcu on 31.05.2021.
//

#include "AddCommand.h"

void AddCommand::execute() {
    mAddedEventID = mID;
    mAdminService->addEvent(mID, mTitle, mDescription, mTime, mParticipantsNumber, mLink, mDay, mMonth, mYear);
    mView->model()->insertRow(mAdminService->getEventsNumber() - 1);
}

void AddCommand::undo() {
    mAdminService->removeEvent(mAddedEventID);
    mView->model()->removeRow(mAdminService->getEventsNumber() - 2);
}

void AddCommand::redo() {
    mAdminService->addEvent(mID, mTitle, mDescription, mTime, mParticipantsNumber, mLink, mDay, mMonth, mYear);
    mView->model()->insertRow(mAdminService->getEventsNumber() - 1);
}

AddCommand::AddCommand(AdminService* adminService, QTableView* view, int ID, std::string title, std::string description, int day, int month, int year, std::string time, int participantsNumber, std::string link)
        : mAdminService{adminService},
          mView{view},
          mID{ID},
          mTitle{title},
          mDescription{description},
          mDay{day}, mMonth{month}, mYear{year},
          mTime{time},
          mParticipantsNumber{participantsNumber}, mLink{link} {}
