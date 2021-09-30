//
// Created by Alex Nedelcu on 05.05.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_PERSISTENCEOPTIONSGUI_H
#define A89_915_NEDELCU_ALEXANDRU_PERSISTENCEOPTIONSGUI_H


#include <QListWidget>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>
#include "../PERSISTENCE/CSVFileRepository.h"
#include "../PERSISTENCE/HTMLEventsRepository.h"
#include "../PERSISTENCE/MemoryRepository.h"
#include "../VALIDATION/Validator.h"
#include "../VALIDATION/VirtualValidator.h"
#include "../DOMAIN/Event.h"
#include "ModeOptionsGUI.h"

class PersistenceOptionsGUI : public QWidget {
private:
    // Graphical elements //
    QRadioButton* m_buttonForCSV;
    QRadioButton* m_buttonForHTML;
    QRadioButton* m_buttonForInMemory;
    QPushButton* m_chooseButton;
    QLabel* m_label;
    // ------------------------------ //

    std::unique_ptr<ModeOptionsGUI> m_modeOptionsWindow;

    void initialize();

    void transitionToNextWindow();

    int getSelectedOption() const;

    void connectSignalsToSlots();

public:
    explicit PersistenceOptionsGUI();

    ~PersistenceOptionsGUI();
};


#endif //A89_915_NEDELCU_ALEXANDRU_PERSISTENCEOPTIONSGUI_H
