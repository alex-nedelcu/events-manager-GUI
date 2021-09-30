//
// Created by Alex Nedelcu on 31.05.2021.
//

#include "RemoveCommand.h"

RemoveCommand::RemoveCommand(AdminService* adminService, QTableView* view, int removeID)
        : mAdminService{adminService},
          mView{view},
          mRemoveID{removeID} {}

void RemoveCommand::execute() {
    Event removedEvent = mAdminService->removeEvent(mRemoveID);

    mID = removedEvent.getID();
    mTitle = removedEvent.getTitle();
    mDescription = removedEvent.getDescription();
    mDay = removedEvent.getDate().getDay();
    mMonth = removedEvent.getDate().getMonth();
    mYear = removedEvent.getDate().getYear();
    mTime = removedEvent.getTime();
    mParticipantsNumber = removedEvent.getParticipantsNumber();
    mLink = removedEvent.getLink();

    mView->model()->removeRow(mAdminService->getEventsNumber() - 2);
}

void RemoveCommand::undo() {
    mAdminService->addEvent(mID, mTitle, mDescription, mTime, mParticipantsNumber, mLink, mDay, mMonth, mYear);
    mView->model()->insertRow(mAdminService->getEventsNumber() - 1);
}

void RemoveCommand::redo() {
    mAdminService->removeEvent(mRemoveID);
    mView->model()->removeRow(mAdminService->getEventsNumber() - 2);
}
