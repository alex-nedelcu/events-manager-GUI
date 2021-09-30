//
// Created by Alex Nedelcu on 30.05.2021.
//

#ifndef A10_915_NEDELCU_ALEXANDRU_1_EVENTSTABLEMODEL_H
#define A10_915_NEDELCU_ALEXANDRU_1_EVENTSTABLEMODEL_H


#include <QAbstractTableModel>
#include "../BUSINESS/AdminService.h"

class EventsTableModel : public QAbstractTableModel {
private:
    AdminService* m_adminService;

public:
    explicit EventsTableModel(AdminService* adminService);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
};


#endif //A10_915_NEDELCU_ALEXANDRU_1_EVENTSTABLEMODEL_H
