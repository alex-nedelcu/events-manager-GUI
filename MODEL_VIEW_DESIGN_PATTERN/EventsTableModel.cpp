//
// Created by Alex Nedelcu on 30.05.2021.
//

#include "EventsTableModel.h"

EventsTableModel::EventsTableModel(AdminService* adminService) : m_adminService{adminService} {
}

int EventsTableModel::rowCount(const QModelIndex& parent) const {
    return m_adminService->getAllEvents().size();
}

int EventsTableModel::columnCount(const QModelIndex& parent) const {
    return 9;
}

QVariant EventsTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();
    Event currentEvent = m_adminService->getAllEvents()[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
            case 0:
                return QString::number(currentEvent.getID());
            case 1:
                return QString::fromStdString(currentEvent.getTitle());
            case 2:
                return QString::fromStdString(currentEvent.getDescription());
            case 3:
                return QString::number(currentEvent.getDate().getDay());
            case 4:
                return QString::number(currentEvent.getDate().getMonth());
            case 5:
                return QString::number(currentEvent.getDate().getYear());
            case 6:
                return QString::fromStdString(currentEvent.getTime());
            case 7:
                return QString::number(currentEvent.getParticipantsNumber());
            case 8:
                return QString::fromStdString(currentEvent.getLink());
        }
    }

    return QVariant();
}

QVariant EventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
                case 0:
                    return QString("ID");
                case 1:
                    return QString("Title");
                case 2:
                    return QString("Description");
                case 3:
                    return QString("Day");
                case 4:
                    return QString("Month");
                case 5:
                    return QString("Year");
                case 6:
                    return QString("Time");
                case 7:
                    return QString("Participants");
                case 8:
                    return QString("Link");
            }
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);

}

bool EventsTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    int column = index.column();
    Event& currentEvent = m_adminService->getAllEvents()[row];

    switch (column) {
        case 0:
            break;
        case 1: {
            std::string titleCopy = value.toString().toStdString();
            currentEvent.setTitle(titleCopy);
            break;
        }
        case 2: {
            std::string descriptionCopy = value.toString().toStdString();
            currentEvent.setDescription(descriptionCopy);
            break;
        }
        case 3: {
            int day = std::stoi(value.toString().toStdString());
            currentEvent.setDay(day);
            break;
        }
        case 4: {
            int month = std::stoi(value.toString().toStdString());
            currentEvent.setMonth(month);
            break;
        }
        case 5: {
            int year = std::stoi(value.toString().toStdString());
            currentEvent.setYear(year);
            break;
        }
        case 6: {
            std::string timeCopy = value.toString().toStdString();
            currentEvent.setTime(timeCopy);
            break;
        }
        case 7: {
            int participants = std::stoi(value.toString().toStdString());
            currentEvent.setParticipantsNumber(participants);
            break;
        }
        case 8: {
            std::string linkCopy = value.toString().toStdString();
            currentEvent.setLink(linkCopy);
            break;
        }
        default:
            break;
    }

    m_adminService->writeToFile();
    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags EventsTableModel::flags(const QModelIndex& index) const {
    if (index.column() == 0)
        return Qt::ItemFlags{};

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool EventsTableModel::removeRows(int row, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, row, row);
    endRemoveRows();
    return true;
}

bool EventsTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    beginInsertRows(parent, row, row);
    endInsertRows();
    return true;
}
