//
// Created by Alex Nedelcu on 05.05.2021.
//

#include "UserGUI.h"

UserGUI::UserGUI(UserService* userService, AdminService* adminService, ModeOptionsGUI& modeOptionsGUI)
        : m_userService{userService},
          m_adminService{adminService},
          m_modeOptionsGUI{modeOptionsGUI} {
    this->initialize();
    this->populateEventsList();
    this->populateWishlist();
    this->connectSignalsToSlots();
}

void UserGUI::initialize() {
    // Creation and customization of widgets //
    m_allEvents = new QListWidget{};
    m_wishlist = new QListWidget{};
    m_IDLineEdit = new QLineEdit{};
    m_titleLineEdit = new QLineEdit{};
    m_descriptionLineEdit = new QLineEdit{};
    m_dateLineEdit = new QLineEdit{};
    m_timeLineEdit = new QLineEdit{};
    m_participantsLineEdit = new QLineEdit{};
    m_linkLineEdit = new QLineEdit{};
    m_openLinkButton = new QPushButton{"Open link"};
    m_addToWishlistButton = new QPushButton{"Add to wishlist"};
    m_removeFromWishlistButton = new QPushButton{"Remove from wishlist"};
    m_eventsLabel = new QLabel{};
    m_wishlistLabel = new QLabel{};
    m_backButton = new QPushButton{"Back"};
    m_switchToMainList = new QPushButton("Switch to main list");
    m_switchToWishlist = new QPushButton("Switch to wishlist");

    m_eventsLabel->setFont(QFont("Helvetica Neue", 20));
    m_wishlistLabel->setFont(QFont("Helvetica Neue", 20));
    m_IDLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_titleLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_descriptionLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_dateLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_participantsLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_linkLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_timeLineEdit->setFont(QFont("Helvetica Neue", 13));
    m_openLinkButton->setFont(QFont("Helvetica Neue", 13));
    m_addToWishlistButton->setFont(QFont("Helvetica Neue", 13));
    m_removeFromWishlistButton->setFont(QFont("Helvetica Neue", 13));
    m_backButton->setFont(QFont("Helvetica Neue", 13));
    m_switchToMainList->setFont(QFont("Helvetica Neue", 13));
    m_switchToWishlist->setFont(QFont("Helvetica Neue", 13));

    m_allEvents->setMinimumSize(500, 200);
    m_wishlist->setMinimumSize(500, 200);

    m_IDLineEdit->setReadOnly(true);
    m_titleLineEdit->setReadOnly(true);
    m_descriptionLineEdit->setReadOnly(true);
    m_dateLineEdit->setReadOnly(true);
    m_timeLineEdit->setReadOnly(true);
    m_participantsLineEdit->setReadOnly(true);
    m_linkLineEdit->setReadOnly(true);

    m_IDLineEdit->setFixedWidth(320);
    m_titleLineEdit->setFixedWidth(320);
    m_descriptionLineEdit->setFixedWidth(320);
    m_dateLineEdit->setFixedWidth(320);
    m_timeLineEdit->setFixedWidth(320);
    m_participantsLineEdit->setFixedWidth(320);
    m_linkLineEdit->setFixedWidth(320);

    m_IDLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_titleLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_descriptionLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_dateLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_timeLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_participantsLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_linkLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    m_eventsLabel->setText("Events");
    m_wishlistLabel->setText("Wishlist");

    m_backButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_openLinkButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_addToWishlistButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_removeFromWishlistButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_switchToMainList->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_switchToWishlist->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    m_switchToMainList->setMinimumWidth(155);
    m_switchToWishlist->setMinimumWidth(155);

    m_eventsLabel->setVisible(true);
    m_allEvents->setVisible(true);
    m_switchToWishlist->setVisible(true);

    m_wishlistLabel->setVisible(false);
    m_wishlist->setVisible(false);
    m_switchToMainList->setVisible(false);
    // ---------------------------------------------------------------------------------- //

    // Layouts design //
    QVBoxLayout* mainLayout = new QVBoxLayout{this};

    QVBoxLayout* mainListLayout = new QVBoxLayout{};
    mainListLayout->addWidget(m_eventsLabel, 0, Qt::AlignCenter);
    mainListLayout->addWidget(m_allEvents);
    mainListLayout->addWidget(m_switchToWishlist, 0, Qt::AlignCenter);

    QVBoxLayout* wishlistLayout = new QVBoxLayout{};
    wishlistLayout->addWidget(m_wishlistLabel, 0, Qt::AlignCenter);
    wishlistLayout->addWidget(m_wishlist);
    wishlistLayout->addWidget(m_switchToMainList, 0, Qt::AlignCenter);

    QFormLayout* eventDetailsLayout = new QFormLayout{};
    eventDetailsLayout->addRow("ID:", m_IDLineEdit);
    eventDetailsLayout->addRow("Name:", m_titleLineEdit);
    eventDetailsLayout->addRow("Description:", m_descriptionLineEdit);
    eventDetailsLayout->addRow("Date:", m_dateLineEdit);
    eventDetailsLayout->addRow("Time:", m_timeLineEdit);
    eventDetailsLayout->addRow("Participants:", m_participantsLineEdit);
    eventDetailsLayout->addRow("Link:", m_linkLineEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout{};
    buttonsLayout->addWidget(m_openLinkButton);
    buttonsLayout->addWidget(m_addToWishlistButton);
    buttonsLayout->addWidget(m_removeFromWishlistButton);

    mainLayout->addWidget(m_backButton, 0, Qt::AlignLeft);
    mainLayout->addSpacing(7);
    mainLayout->addLayout(mainListLayout);
    mainLayout->addLayout(wishlistLayout);
    mainLayout->addSpacing(18);
    mainLayout->addLayout(eventDetailsLayout);
    mainLayout->addSpacing(25);
    mainLayout->addLayout(buttonsLayout);
    // -------------------------------------------------------------------- //

    this->setBaseSize(this->sizeHint());
    this->move(440, 130);
}

void UserGUI::connectSignalsToSlots() {
    QObject::connect(m_allEvents, &QListWidget::itemSelectionChanged, this, &UserGUI::actualizeFieldsByLeftBox);
    QObject::connect(m_wishlist, &QListWidget::itemSelectionChanged, this, &UserGUI::actualizeFieldsByRightBox);
    QObject::connect(m_openLinkButton, &QPushButton::clicked, this, &UserGUI::openLink);
    QObject::connect(m_addToWishlistButton, &QPushButton::clicked, this, &UserGUI::addToWishlist);
    QObject::connect(m_removeFromWishlistButton, &QPushButton::clicked, this, &UserGUI::removeFromWishlist);
    QObject::connect(m_switchToMainList, &QPushButton::clicked, [this]() {
        m_wishlistLabel->setVisible(false);
        m_wishlist->setVisible(false);
        m_switchToMainList->setVisible(false);

        m_eventsLabel->setVisible(true);
        m_allEvents->setVisible(true);
        m_switchToWishlist->setVisible(true);

        populateEventsList();
    });
    QObject::connect(m_switchToWishlist, &QPushButton::clicked, [this]() {
        m_eventsLabel->setVisible(false);
        m_allEvents->setVisible(false);
        m_switchToWishlist->setVisible(false);

        m_wishlistLabel->setVisible(true);
        m_wishlist->setVisible(true);
        m_switchToMainList->setVisible(true);

        populateWishlist();
    });
    QObject::connect(m_backButton, &QPushButton::clicked, [this]() {
        this->hide();
        m_modeOptionsGUI.show();
    });
}

UserGUI::~UserGUI() {
    delete m_allEvents;
    delete m_wishlist;
    delete m_IDLineEdit;
    delete m_titleLineEdit;
    delete m_descriptionLineEdit;
    delete m_dateLineEdit;
    delete m_timeLineEdit;
    delete m_participantsLineEdit;
    delete m_linkLineEdit;
    delete m_openLinkButton;
    delete m_addToWishlistButton;
    delete m_removeFromWishlistButton;
    delete m_eventsLabel;
    delete m_wishlistLabel;
    delete m_backButton;
    delete m_switchToMainList;
    delete m_switchToWishlist;
}

void UserGUI::populateEventsList() {
    m_allEvents->clear();
    std::vector<Event> events = m_adminService->getAllEvents();
    std::for_each(events.begin(), events.end(), [this](const Event& event) {
        m_allEvents->addItem(QString::fromStdString(event.toStringEssentials()));
    });
}

void UserGUI::populateWishlist() {
    m_wishlist->clear();
    std::vector<Event> wishlist = m_userService->getEventsWishlist();
    std::for_each(wishlist.begin(), wishlist.end(), [this](const Event& event) {
        m_wishlist->addItem(QString::fromStdString(event.toStringEssentials()));
    });
}

void UserGUI::clearEventFields() {
    m_IDLineEdit->clear();
    m_titleLineEdit->clear();
    m_descriptionLineEdit->clear();
    m_dateLineEdit->clear();
    m_timeLineEdit->clear();
    m_participantsLineEdit->clear();
    m_linkLineEdit->clear();
}

int UserGUI::getAnySelectedIndex() {
    QModelIndexList leftListSelectedIndexes = m_allEvents->selectionModel()->selectedIndexes();
    QModelIndexList rightListSelectedIndexes = m_wishlist->selectionModel()->selectedIndexes();
    int selectedIndex = -1;

    if (leftListSelectedIndexes.size() == 0 && rightListSelectedIndexes.size() == 0) {
        this->clearEventFields();
        return -1;
    } else {
        if (leftListSelectedIndexes.size() != 0) {
            selectedIndex = leftListSelectedIndexes.at(0).row();
        } else if (rightListSelectedIndexes.size() != 0) {
            selectedIndex = rightListSelectedIndexes.at(0).row();
        }
        return selectedIndex;
    }
}

void UserGUI::actualizeFieldsByLeftBox() {
    m_wishlist->clearSelection();
    int selectedElementIndex = this->getAnySelectedIndex();
    if (selectedElementIndex == -1)
        return;

    Event selectedEvent = m_adminService->getAllEvents()[selectedElementIndex];

    std::string stringDate = std::to_string(selectedEvent.getDate().getDay()) + "/" + \
            std::to_string(selectedEvent.getDate().getMonth()) + "/" + \
            std::to_string(selectedEvent.getDate().getYear());

    m_IDLineEdit->setText(QString::fromStdString(std::to_string(selectedEvent.getID())));
    m_titleLineEdit->setText(QString::fromStdString(selectedEvent.getTitle()));
    m_descriptionLineEdit->setText(QString::fromStdString(selectedEvent.getDescription()));
    m_dateLineEdit->setText(QString::fromStdString(stringDate));
    m_timeLineEdit->setText(QString::fromStdString(selectedEvent.getTime()));
    m_participantsLineEdit->setText(QString::fromStdString(std::to_string(selectedEvent.getParticipantsNumber())));
    m_linkLineEdit->setText(QString::fromStdString(selectedEvent.getLink()));
}

void UserGUI::actualizeFieldsByRightBox() {
    m_allEvents->clearSelection();
    int selectedElementIndex = this->getAnySelectedIndex();
    if (selectedElementIndex == -1)
        return;

    Event selectedEvent = m_userService->getEventsWishlist()[selectedElementIndex];

    std::string stringDate = std::to_string(selectedEvent.getDate().getDay()) + "/" + \
            std::to_string(selectedEvent.getDate().getMonth()) + "/" + \
            std::to_string(selectedEvent.getDate().getYear());

    m_IDLineEdit->setText(QString::fromStdString(std::to_string(selectedEvent.getID())));
    m_titleLineEdit->setText(QString::fromStdString(selectedEvent.getTitle()));
    m_descriptionLineEdit->setText(QString::fromStdString(selectedEvent.getDescription()));
    m_dateLineEdit->setText(QString::fromStdString(stringDate));
    m_timeLineEdit->setText(QString::fromStdString(selectedEvent.getTime()));
    m_participantsLineEdit->setText(QString::fromStdString(std::to_string(selectedEvent.getParticipantsNumber())));
    m_linkLineEdit->setText(QString::fromStdString(selectedEvent.getLink()));
}

void UserGUI::openLink() {
    int selectedElementIndex = getAnySelectedIndex();
    if (selectedElementIndex == -1) {
        QMessageBox::critical(this, "Error", QString::fromStdString("No event selected!"));
        return;
    } else {
        std::string link = m_linkLineEdit->text().toStdString();
        std::string linkOpener = "open " + link;
        system(linkOpener.c_str());
    }
}

void UserGUI::addToWishlist() {
    int selectedElementIndex = getLeftBoxSelectedIndex();

    if (selectedElementIndex == -1) {
        QMessageBox::critical(this, "Error", QString::fromStdString("No event from the list selected!"));
        return;
    } else {
        Event selectedEvent = m_adminService->getAllEvents()[selectedElementIndex];
        try {
            m_userService->addEvent(selectedEvent);
        } catch (const RepositoryException& rex) {
            QMessageBox::critical(this, "Error", QString::fromStdString(rex.getErrorMessage()));
            return;
        }
        m_adminService->incrementParticipantsNumber(selectedEvent.getID());
        m_userService->incrementParticipantsNumber(selectedEvent.getID());
        populateEventsList();
        populateWishlist();

        if (selectedElementIndex < m_adminService->getAllEvents().size() - 1) {
            selectedElementIndex++;
            m_allEvents->item(selectedElementIndex)->setSelected(true);
        } else {
            selectedElementIndex = 0;
            m_allEvents->item(selectedElementIndex)->setSelected(true);
        }
    }
}

int UserGUI::getLeftBoxSelectedIndex() {
    QModelIndexList leftListSelectedIndexes = m_allEvents->selectionModel()->selectedIndexes();

    if (leftListSelectedIndexes.size() == 0) {
        return -1;
    } else {
        int selectedIndex = leftListSelectedIndexes.at(0).row();
        return selectedIndex;
    }
}

int UserGUI::getRightBoxSelectedIndex() {
    QModelIndexList rightListSelectedIndexes = m_wishlist->selectionModel()->selectedIndexes();

    if (rightListSelectedIndexes.size() == 0) {
        return -1;
    } else {
        int selectedIndex = rightListSelectedIndexes.at(0).row();
        return selectedIndex;
    }
}

void UserGUI::removeFromWishlist() {
    int selectedElementIndex = getRightBoxSelectedIndex();

    if (selectedElementIndex == -1) {
        QMessageBox::critical(this, "Error", QString::fromStdString("No event from the wishlist selected!"));
        return;
    } else {
        Event selectedEvent = m_userService->getEventsWishlist()[selectedElementIndex];
        m_userService->removeEvent(selectedEvent.getID());
        try {
            m_adminService->decrementParticipantsNumber(selectedEvent.getID());
        } catch (...) {

        }
        populateEventsList();
        populateWishlist();

        if (m_userService->getEventsWishlist().size() != 0 && selectedElementIndex < m_userService->getEventsWishlist().size())
            m_wishlist->setCurrentRow(selectedElementIndex);
        else if (m_userService->getEventsWishlist().size() != 0)
            m_wishlist->setCurrentRow(selectedElementIndex - 1);
    }
}
