//
// Created by Alex Nedelcu on 05.05.2021.
//

#include <QVBoxLayout>
#include <QFontDatabase>
#include <QMessageBox>
#include <QFormLayout>
#include "PersistenceOptionsGUI.h"


void PersistenceOptionsGUI::initialize() {
    // Creation and customization of buttons and labels //
    m_label = new QLabel{};
    m_buttonForCSV = new QRadioButton{};
    m_buttonForHTML = new QRadioButton{};
    m_buttonForInMemory = new QRadioButton{};
    m_chooseButton = new QPushButton{};

    m_label->setText(QString::fromStdString("Choose the persistence option"));
    m_buttonForCSV->setText(QString::fromStdString("CSV"));
    m_buttonForHTML->setText(QString::fromStdString("HTML"));
    m_buttonForInMemory->setText(QString::fromStdString("RAM"));
    m_chooseButton->setText(QString::fromStdString("Choose"));

    m_label->setFont(QFont("Helvetica Neue", 19));
    m_buttonForCSV->setFont(QFont("Helvetica Neue", 13, 40));
    m_buttonForHTML->setFont(QFont("Helvetica Neue", 13, 40));
    m_buttonForInMemory->setFont(QFont("Helvetica Neue", 13, 40));
    m_chooseButton->setFont(QFont("Helvetica Neue", 15));

    m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonForCSV->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonForHTML->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonForInMemory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_chooseButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_buttonForCSV->setFocusPolicy(Qt::ClickFocus);
    m_buttonForHTML->setFocusPolicy(Qt::ClickFocus);
    m_buttonForInMemory->setFocusPolicy(Qt::ClickFocus);
    m_chooseButton->setFocusPolicy(Qt::NoFocus);

    m_buttonForCSV->click();
    m_buttonForCSV->setFocus();
    m_buttonForHTML->setChecked(false);
    m_buttonForInMemory->setChecked(false);

    m_chooseButton->setMaximumHeight(30);
    // -------------------------------------------------------------------------------------- //


    // Layouts design //
    QVBoxLayout* mainLayout = new QVBoxLayout{this};

    QHBoxLayout* labelLayout = new QHBoxLayout{};
    labelLayout->addWidget(m_label, 0, Qt::AlignmentFlag::AlignCenter);

    QGridLayout* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(m_buttonForCSV);
    buttonsLayout->addWidget(m_buttonForHTML);
    buttonsLayout->addWidget(m_buttonForInMemory);

    QFormLayout* finalLayout = new QFormLayout{};
    finalLayout->addWidget(m_chooseButton);

    mainLayout->addLayout(labelLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(finalLayout);
    // --------------------------------------------------- //

    this->setBaseSize(this->sizeHint());
    this->move(555,460);
}

PersistenceOptionsGUI::PersistenceOptionsGUI() : QWidget() {
    this->initialize();
    this->connectSignalsToSlots();
}

void PersistenceOptionsGUI::connectSignalsToSlots() {
    QObject::connect(m_chooseButton, &QPushButton::clicked, this, &PersistenceOptionsGUI::transitionToNextWindow);
}

void PersistenceOptionsGUI::transitionToNextWindow() {
    int selectedOption = getSelectedOption();

    if (selectedOption == -1) {
        QMessageBox::critical(this, "Error", QString::fromStdString("No option selected!"));
        return;
    } else {
        this->close();
        m_modeOptionsWindow = std::make_unique<ModeOptionsGUI>(selectedOption);
        m_modeOptionsWindow->show();
    }
}

int PersistenceOptionsGUI::getSelectedOption() const {
    if (m_buttonForCSV->isChecked())
        return 1;
    else if (m_buttonForHTML->isChecked())
        return 2;
    else if (m_buttonForInMemory->isChecked())
        return 3;
    else
        return -1;
}

PersistenceOptionsGUI::~PersistenceOptionsGUI() {
    delete m_buttonForCSV;
    delete m_buttonForHTML;
    delete m_buttonForInMemory;
    delete m_label;
    delete m_chooseButton;
}


