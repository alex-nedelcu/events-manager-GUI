//
// Created by Alex Nedelcu on 05.05.2021.
//

#include "ModeOptionsGUI.h"
#include "AdminGUI.h"
#include "UserGUI.h"

void ModeOptionsGUI::initialize() {
    // Creation and customization of buttons and labels //
    m_message = new QLabel{};
    m_adminModeButton = new QPushButton{};
    m_userModeButton = new QPushButton{};

    m_message->setText(QString::fromStdString("Available modes"));
    m_adminModeButton->setText(QString::fromStdString("Admin mode"));
    m_userModeButton->setText(QString::fromStdString("User mode"));

    m_message->setFont(QFont("Helvetica Neue", 18));
    m_adminModeButton->setFont(QFont("Helvetica Neue", 14));
    m_userModeButton->setFont(QFont("Helvetica Neue", 14));

    m_message->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_adminModeButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_userModeButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    m_adminModeButton->setMaximumHeight(32);
    m_userModeButton->setMaximumHeight(32);
    m_adminModeButton->setMinimumWidth(120);
    m_userModeButton->setMinimumWidth(120);
    // -------------------------------------------------------------------------------------- //

    // Layouts design //
    QVBoxLayout* mainLayout = new QVBoxLayout{this};

    QHBoxLayout* messageLayout = new QHBoxLayout{};
    messageLayout->addWidget(m_message, 0, Qt::AlignmentFlag::AlignCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout{};
    buttonsLayout->addWidget(m_adminModeButton);
    buttonsLayout->addWidget(m_userModeButton);

    mainLayout->addLayout(messageLayout, 35);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    // --------------------------------------------------- //

    this->setBaseSize(this->sizeHint());
    this->move(555, 460);
}

void ModeOptionsGUI::connectSignalsToSlots() {
    QObject::connect(m_adminModeButton, &QPushButton::clicked, this, &ModeOptionsGUI::startAdminGUI);
    QObject::connect(m_userModeButton, &QPushButton::clicked, this, &ModeOptionsGUI::startUserGUI);
}

ModeOptionsGUI::ModeOptionsGUI(int persistenceOption) : QWidget(), m_persistenceOption{persistenceOption} {
    m_validator = nullptr;
    m_adminRepositoryCSV = nullptr;
    m_userRepositoryCSV = nullptr;
    m_adminRepositoryHTML = nullptr;
    m_userRepositoryHTML = nullptr;
    m_adminRepositoryRAM = nullptr;
    m_userRepositoryRAM = nullptr;
    m_adminService = nullptr;
    m_userService = nullptr;
    m_eventsTableModel = nullptr;

    this->initialize();
    this->connectSignalsToSlots();
}

ModeOptionsGUI::~ModeOptionsGUI() {
    delete m_message;
    delete m_adminModeButton;
    delete m_userModeButton;

    if (m_validator != nullptr)
        delete m_validator;

    if (m_adminRepositoryCSV != nullptr)
        delete m_adminRepositoryCSV;

    if (m_userRepositoryCSV != nullptr)
        delete m_userRepositoryCSV;

    if (m_adminRepositoryHTML != nullptr)
        delete m_adminRepositoryHTML;

    if (m_userRepositoryHTML != nullptr)
        delete m_userRepositoryHTML;

    if (m_adminRepositoryRAM != nullptr)
        delete m_adminRepositoryRAM;

    if (m_userRepositoryRAM != nullptr)
        delete m_userRepositoryRAM;

    if (m_adminService != nullptr)
        delete m_adminService;

    if (m_userService != nullptr)
        delete m_userService;

    if (m_eventsTableModel != nullptr)
        delete m_eventsTableModel;
}

void ModeOptionsGUI::startAdminGUI() {
    this->hide();
    m_validator = new Validator{};

    if (m_persistenceOption == 1) {
        if (m_adminRepositoryCSV == nullptr)
            m_adminRepositoryCSV = new CSVFileRepository<Event>{"../DATA/admin_events.csv", m_validator};

        if (m_userRepositoryCSV == nullptr)
            m_userRepositoryCSV = new CSVFileRepository<Event>{"../DATA/user_events.csv", m_validator};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryCSV, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryCSV, m_validator, std::to_string(m_persistenceOption)};

        if (m_eventsTableModel == nullptr) {
            m_eventsTableModel = new QSortFilterProxyModel{};
            EventsTableModel* tableModel = new EventsTableModel{m_adminService};
            m_eventsTableModel->setSourceModel(tableModel);
        }

        if (m_adminGUI == nullptr)
            m_adminGUI = std::make_unique<AdminGUI>(m_adminService, *this, m_eventsTableModel);

        m_adminGUI->show();
    } else if (m_persistenceOption == 2) {
        if (m_adminRepositoryHTML == nullptr)
            m_adminRepositoryHTML = new HTMLEventsRepository{"../DATA/admin_events.html", m_validator};

        if (m_userRepositoryHTML == nullptr)
            m_userRepositoryHTML = new HTMLEventsRepository{"../DATA/user_events.html", m_validator};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryHTML, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryHTML, m_validator, std::to_string(m_persistenceOption)};

        if (m_eventsTableModel == nullptr) {
            m_eventsTableModel = new QSortFilterProxyModel{};
            EventsTableModel* tableModel = new EventsTableModel{m_adminService};
            m_eventsTableModel->setSourceModel(tableModel);
        }

        if (m_adminGUI == nullptr)
            m_adminGUI = std::make_unique<AdminGUI>(m_adminService, *this, m_eventsTableModel);

        m_adminGUI->show();
    } else {
        if (m_adminRepositoryRAM == nullptr)
            m_adminRepositoryRAM = new MemoryRepository<Event>{};

        if (m_userRepositoryRAM == nullptr)
            m_userRepositoryRAM = new MemoryRepository<Event>{};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryRAM, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryRAM, m_validator, std::to_string(m_persistenceOption)};

        if (m_eventsTableModel == nullptr) {
            m_eventsTableModel = new QSortFilterProxyModel{};
            EventsTableModel* tableModel = new EventsTableModel{m_adminService};
            m_eventsTableModel->setSourceModel(tableModel);
        }

        if (m_adminGUI == nullptr)
            m_adminGUI = std::make_unique<AdminGUI>(m_adminService, *this, m_eventsTableModel);

        m_adminGUI->show();
    }
}

void ModeOptionsGUI::startUserGUI() {
    this->hide();
    m_validator = new Validator{};

    if (m_persistenceOption == 1) {
        if (m_adminRepositoryCSV == nullptr)
            m_adminRepositoryCSV = new CSVFileRepository<Event>{"../DATA/admin_events.csv", m_validator};

        if (m_userRepositoryCSV == nullptr)
            m_userRepositoryCSV = new CSVFileRepository<Event>{"../DATA/user_events.csv", m_validator};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryCSV, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryCSV, m_validator, std::to_string(m_persistenceOption)};

        if (m_userGUI == nullptr)
            m_userGUI = std::make_unique<UserGUI>(m_userService, m_adminService, *this);

        m_userGUI->populateEventsList();
        m_userGUI->show();
    } else if (m_persistenceOption == 2) {
        if (m_adminRepositoryHTML == nullptr)
            m_adminRepositoryHTML = new HTMLEventsRepository{"../DATA/admin_events.html", m_validator};

        if (m_userRepositoryHTML == nullptr)
            m_userRepositoryHTML = new HTMLEventsRepository{"../DATA/user_events.html", m_validator};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryHTML, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryHTML, m_validator, std::to_string(m_persistenceOption)};

        if (m_userGUI == nullptr)
            m_userGUI = std::make_unique<UserGUI>(m_userService, m_adminService, *this);

        m_userGUI->populateEventsList();
        m_userGUI->show();
    } else {
        if (m_adminRepositoryRAM == nullptr)
            m_adminRepositoryRAM = new MemoryRepository<Event>{};

        if (m_userRepositoryRAM == nullptr)
            m_userRepositoryRAM = new MemoryRepository<Event>{};

        if (m_adminService == nullptr) {
            m_adminService = new AdminService{m_adminRepositoryRAM, m_validator};
            m_adminService->populateEventsRepository();
        }

        if (m_userService == nullptr)
            m_userService = new UserService{m_userRepositoryRAM, m_validator, std::to_string(m_persistenceOption)};

        if (m_userGUI == nullptr)
        m_userGUI = std::make_unique<UserGUI>(m_userService, m_adminService, *this);

        m_userGUI->populateEventsList();
        m_userGUI->show();
    }
}
