//
// Created by Alex Nedelcu on 05.05.2021.
//

#include <QApplication>
#include "StarterGUI.h"
#include "../GUI/PersistenceOptionsGUI.h"

int StarterGUI::start(int argc, char** argv) {
    QApplication app{argc, argv};
    std::unique_ptr<PersistenceOptionsGUI> persistenceOptionsGUI = std::make_unique<PersistenceOptionsGUI>();
    persistenceOptionsGUI->show();
    return app.exec();
}