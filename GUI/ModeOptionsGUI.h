//
// Created by Alex Nedelcu on 05.05.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_MODEOPTIONSGUI_H
#define A89_915_NEDELCU_ALEXANDRU_MODEOPTIONSGUI_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QFlags>
#include <QSortFilterProxyModel>
#include "../PERSISTENCE/CSVFileRepository.h"
#include "../PERSISTENCE/HTMLEventsRepository.h"
#include "../PERSISTENCE/MemoryRepository.h"
#include "../BUSINESS/UserService.h"
#include "../BUSINESS/AdminService.h"
#include "../MODEL_VIEW_DESIGN_PATTERN/EventsTableModel.h"

class AdminGUI;

class UserGUI;

class ModeOptionsGUI : public QWidget {
private:
    // Graphical elements //
    QLabel* m_message;
    QPushButton* m_adminModeButton;
    QPushButton* m_userModeButton;
    // ---------------------------- //

    // Application backend components //
    Validator* m_validator;
    CSVFileRepository<Event>* m_adminRepositoryCSV;
    CSVFileRepository<Event>* m_userRepositoryCSV;
    HTMLEventsRepository* m_adminRepositoryHTML;
    HTMLEventsRepository* m_userRepositoryHTML;
    MemoryRepository<Event>* m_adminRepositoryRAM;
    MemoryRepository<Event>* m_userRepositoryRAM;
    AdminService* m_adminService;
    UserService* m_userService;
    QSortFilterProxyModel* m_eventsTableModel;
    // ----------------------------------------- //

    // Application frontend components //
    std::unique_ptr<AdminGUI> m_adminGUI;
    std::unique_ptr<UserGUI> m_userGUI;
    // ----------------------------------------- //

    int m_persistenceOption;

    void connectSignalsToSlots();

    void initialize();

    void startAdminGUI();

    void startUserGUI();

    friend class AdminGUI;

    friend class UserGUI;

public:
    explicit ModeOptionsGUI(int persistenceOption);

    ~ModeOptionsGUI();
};

#endif //A89_915_NEDELCU_ALEXANDRU_MODEOPTIONSGUI_H
