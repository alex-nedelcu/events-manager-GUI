//
// Created by Alex Nedelcu on 05.05.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_USERGUI_H
#define A89_915_NEDELCU_ALEXANDRU_USERGUI_H


#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QModelIndexList>
#include <QLineEdit>
#include <QMessageBox>
#include <vector>
#include "../EXCEPTIONS/RepositoryException.h"
#include "../BUSINESS/UserService.h"
#include "../BUSINESS/AdminService.h"
#include "ModeOptionsGUI.h"

class UserGUI : public QWidget {
private:
    UserService* m_userService;
    AdminService* m_adminService;
    ModeOptionsGUI& m_modeOptionsGUI;

    //   Graphical elements   //
    QListWidget* m_allEvents;
    QListWidget* m_wishlist;
    QLineEdit* m_IDLineEdit;
    QLineEdit* m_titleLineEdit;
    QLineEdit* m_descriptionLineEdit;
    QLineEdit* m_dateLineEdit;
    QLineEdit* m_timeLineEdit;
    QLineEdit* m_participantsLineEdit;
    QLineEdit* m_linkLineEdit;
    QPushButton* m_openLinkButton;
    QPushButton* m_addToWishlistButton;
    QPushButton* m_removeFromWishlistButton;
    QLabel* m_eventsLabel;
    QLabel* m_wishlistLabel;
    QPushButton* m_backButton;
    QPushButton* m_switchToMainList;
    QPushButton* m_switchToWishlist;
    // ---------------------- //

    void initialize();

    void connectSignalsToSlots();

    void populateEventsList();

    void populateWishlist();

    void clearEventFields();

    int getAnySelectedIndex();

    int getLeftBoxSelectedIndex();

    int getRightBoxSelectedIndex();

    void actualizeFieldsByLeftBox();

    void actualizeFieldsByRightBox();

    void openLink();

    void addToWishlist();

    void removeFromWishlist();

    friend class ModeOptionsGUI;

public:
    explicit UserGUI(UserService* userService, AdminService* adminService, ModeOptionsGUI& modeOptionsGUI);

    ~UserGUI();
};


#endif //A89_915_NEDELCU_ALEXANDRU_USERGUI_H
