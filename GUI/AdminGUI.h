//
// Created by Alex Nedelcu on 05.05.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_ADMINGUI_H
#define A89_915_NEDELCU_ALEXANDRU_ADMINGUI_H


#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QModelIndexList>
#include <QMessageBox>
#include <QLabel>
#include <QTableView>
#include <QShortcut>
#include "../BUSINESS/AdminService.h"
#include "../EXCEPTIONS/BaseException.h"
#include "../MODEL_VIEW_DESIGN_PATTERN//EventsTableModel.h"
#include "ModeOptionsGUI.h"
#include "../COMMAND_DESIGN_PATTERN/CommandManager.h"
#include "../COMMAND_DESIGN_PATTERN/AddCommand.h"
#include "../COMMAND_DESIGN_PATTERN/RemoveCommand.h"
#include "../COMMAND_DESIGN_PATTERN/UpdateCommand.h"

class AdminGUI : public QWidget {
private:
    // Back-end elements //
    AdminService* m_adminService;
    std::unique_ptr<CommandManager> m_commandManager;
    ModeOptionsGUI& m_modeOptionsGUI;
    QTableView* m_tableView;
    QSortFilterProxyModel* m_tableModel;
    QShortcut* m_shortcutUndo;
    QShortcut* m_shortcutRedo;

    // Front-end elements //
    QPushButton* m_addButton;
    QPushButton* m_removeButton;
    QPushButton* m_backButton;
    QPushButton* m_undoButton;
    QPushButton* m_redoButton;
    QLabel* m_text;
    QLineEdit* m_IDLineEdit;
    QLineEdit* m_titleLineEdit;
    QLineEdit* m_descriptionLineEdit;
    QLineEdit* m_dayLineEdit;
    QLineEdit* m_monthLineEdit;
    QLineEdit* m_yearLineEdit;
    QLineEdit* m_timeLineEdit;
    QLineEdit* m_participantsLineEdit;
    QLineEdit* m_linkLineEdit;

    void initialize();

    void initializeLineEdits();

    void connectSignalsToSlots();

    void removeGUI();

    void addGUI();

    void undoGUI();

    void redoGUI();

    friend class ModeOptionsGUI;

public:
    explicit AdminGUI(AdminService* adminService, ModeOptionsGUI& modeOptionsGUI, QSortFilterProxyModel* eventsTableModel);

    ~AdminGUI();
};


#endif //A89_915_NEDELCU_ALEXANDRU_ADMINGUI_H
