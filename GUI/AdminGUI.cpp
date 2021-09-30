//
// Created by Alex Nedelcu on 05.05.2021.
//

#include "AdminGUI.h"

AdminGUI::AdminGUI(AdminService* adminService, ModeOptionsGUI& modeOptionsGUI, QSortFilterProxyModel* eventsTableModel)
        : m_adminService{adminService},
          m_modeOptionsGUI{modeOptionsGUI},
          m_tableModel{eventsTableModel} {
    m_commandManager = std::make_unique<CommandManager>();

    this->initialize();
    this->connectSignalsToSlots();
}

void AdminGUI::initialize() {
    this->initializeLineEdits();

    // Model-view creation //
    m_tableView = new QTableView{};
    m_tableView->setModel(m_tableModel);


    // Widgets creation and customization //
    m_shortcutUndo = new QShortcut{QKeySequence("CTRL+Z"), this};
    m_shortcutRedo = new QShortcut{QKeySequence("CTRL+R"), this};
    m_shortcutUndo->setEnabled(true);
    m_shortcutRedo->setEnabled(true);

    m_addButton = new QPushButton{"Add"};
    m_removeButton = new QPushButton{"Remove"};
    m_backButton = new QPushButton{"Back"};
    m_undoButton = new QPushButton{"Undo"};
    m_redoButton = new QPushButton{"Redo"};
    m_text = new QLabel{};

    m_addButton->setFont(QFont("Helvetica Neue", 13));
    m_removeButton->setFont(QFont("Helvetica Neue", 13));
    m_backButton->setFont(QFont("Helvetica Neue", 13));
    m_undoButton->setFont(QFont("Helvetica Neue", 13));
    m_redoButton->setFont(QFont("Helvetica Neue", 13));

    m_addButton->setMaximumHeight(32);
    m_removeButton->setMaximumHeight(32);
    m_backButton->setMaximumHeight(32);
    m_undoButton->setMaximumHeight(32);
    m_redoButton->setMaximumHeight(32);

    m_text->setText(QString::fromStdString("Events"));
    m_text->setFont(QFont("Helvetica Neue", 20));

    m_backButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_addButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_removeButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_undoButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_redoButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    // Layouts design //
    QVBoxLayout* mainLayout = new QVBoxLayout{this};

    QVBoxLayout* tableLayout = new QVBoxLayout{};
    tableLayout->addWidget(m_text, 0, Qt::AlignmentFlag::AlignCenter);
    tableLayout->addSpacing(7);
    tableLayout->addWidget(m_tableView);

    QGridLayout * upButtonsLayout = new QGridLayout{};
    upButtonsLayout->addWidget(m_backButton, 0, 0);
    upButtonsLayout->addWidget(m_undoButton, 0, 6);
    upButtonsLayout->addWidget(m_redoButton, 0, 7);

    QHBoxLayout* downButtonsLayout = new QHBoxLayout{};
    downButtonsLayout->addWidget(m_addButton);
    downButtonsLayout->addWidget(m_removeButton);

    QFormLayout* eventFieldsLayout = new QFormLayout{};
    eventFieldsLayout->addRow(QString::fromStdString("ID"), m_IDLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Title"), m_titleLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Description"), m_descriptionLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Day"), m_dayLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Month"), m_monthLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Year"), m_yearLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Time"), m_timeLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Participants"), m_participantsLineEdit);
    eventFieldsLayout->addRow(QString::fromStdString("Link"), m_linkLineEdit);

    mainLayout->addLayout(upButtonsLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(tableLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(eventFieldsLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(downButtonsLayout);

    // Other customizations //
    this->move(200, 100);
    m_tableView->setAlternatingRowColors(true);
    m_tableView->resizeColumnsToContents();
    m_tableView->setSortingEnabled(true);
    m_tableView->verticalHeader()->setHidden(true);
    m_tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->resize(1000, 700);
}

void AdminGUI::connectSignalsToSlots() {
    QObject::connect(m_backButton, &QPushButton::clicked, [this]() {
        this->hide();
        m_modeOptionsGUI.show();
    });
    QObject::connect(m_removeButton, &QPushButton::clicked, this, &AdminGUI::removeGUI);
    QObject::connect(m_addButton, &QPushButton::clicked, this, &AdminGUI::addGUI);
    QObject::connect(m_undoButton, &QPushButton::clicked, this, &AdminGUI::undoGUI);
    QObject::connect(m_redoButton, &QPushButton::clicked, this, &AdminGUI::redoGUI);
    QObject::connect(m_shortcutUndo, &QShortcut::activated, this, [this]() {emit m_undoButton->clicked(true);});
    QObject::connect(m_shortcutRedo, &QShortcut::activated, this, [this]() {emit m_redoButton->clicked(true);});
}

void AdminGUI::removeGUI() {
    QModelIndexList selectedIndexes = m_tableView->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty())
        return;

    int currentRow = selectedIndexes.at(0).row();
    int selectedEventID = m_tableView->model()->index(currentRow, 0).data().toInt();

    std::shared_ptr<ICommand> removeCommand(new RemoveCommand{m_adminService, m_tableView, selectedEventID});
    m_commandManager->executeCommand(removeCommand);
}

void AdminGUI::addGUI() {
    std::string stringID = m_IDLineEdit->text().toStdString();
    std::string title = m_titleLineEdit->text().toStdString();
    std::string description = m_descriptionLineEdit->text().toStdString();
    std::string stringDay = m_dayLineEdit->text().toStdString();
    std::string stringMonth = m_monthLineEdit->text().toStdString();
    std::string stringYear = m_yearLineEdit->text().toStdString();
    std::string time = m_timeLineEdit->text().toStdString();
    std::string stringParticipantsNumber = m_participantsLineEdit->text().toStdString();
    std::string link = m_linkLineEdit->text().toStdString();

    try {
        int ID = std::stoi(stringID);
        int day = std::stoi(stringDay);
        int month = std::stoi(stringMonth);
        int year = std::stoi(stringYear);
        int participantsNumber = std::stoi(stringParticipantsNumber);

        std::shared_ptr<ICommand> addCommand(new AddCommand{m_adminService, m_tableView, ID, title, description, day, month, year,
                                                            time, participantsNumber, link});
        m_commandManager->executeCommand(addCommand);
    } catch (const BaseException& bex) {
        QMessageBox::critical(this, "Error", QString::fromStdString(bex.getErrorMessage()));
        return;
    } catch (std::invalid_argument& iex) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
}

void AdminGUI::initializeLineEdits() {
    m_IDLineEdit = new QLineEdit{};
    m_titleLineEdit = new QLineEdit{};
    m_descriptionLineEdit = new QLineEdit{};
    m_dayLineEdit = new QLineEdit{};
    m_monthLineEdit = new QLineEdit{};
    m_yearLineEdit = new QLineEdit{};
    m_timeLineEdit = new QLineEdit{};
    m_participantsLineEdit = new QLineEdit{};
    m_linkLineEdit = new QLineEdit{};

    m_IDLineEdit->setClearButtonEnabled(true);
    m_titleLineEdit->setClearButtonEnabled(true);
    m_descriptionLineEdit->setClearButtonEnabled(true);
    m_dayLineEdit->setClearButtonEnabled(true);
    m_monthLineEdit->setClearButtonEnabled(true);
    m_yearLineEdit->setClearButtonEnabled(true);
    m_timeLineEdit->setClearButtonEnabled(true);
    m_participantsLineEdit->setClearButtonEnabled(true);
    m_linkLineEdit->setClearButtonEnabled(true);

    m_IDLineEdit->setFixedWidth(350);
    m_titleLineEdit->setFixedWidth(350);
    m_descriptionLineEdit->setFixedWidth(350);
    m_descriptionLineEdit->setFixedWidth(350);
    m_dayLineEdit->setFixedWidth(350);
    m_monthLineEdit->setFixedWidth(350);
    m_yearLineEdit->setFixedWidth(350);
    m_timeLineEdit->setFixedWidth(350);
    m_participantsLineEdit->setFixedWidth(350);
    m_linkLineEdit->setFixedWidth(350);
}

void AdminGUI::undoGUI() {
    m_commandManager->undo();
}

void AdminGUI::redoGUI() {
    m_commandManager->redo();
}

AdminGUI::~AdminGUI() {
    delete m_addButton;
    delete m_removeButton;
    delete m_backButton;
    delete m_text;
    delete m_IDLineEdit;
    delete m_titleLineEdit;
    delete m_descriptionLineEdit;
    delete m_dayLineEdit;
    delete m_monthLineEdit;
    delete m_yearLineEdit;
    delete m_timeLineEdit;
    delete m_participantsLineEdit;
    delete m_linkLineEdit;
}
