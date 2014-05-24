// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef CWEBDAVITEMMODEL_H
#define CWEBDAVITEMMODEL_H

#include "cwebdavdatamodel.h"
#include <QFileIconProvider>
#include <QAbstractItemModel>

class CWebDavItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CWebDavItemModel(CWebDavDataModel *dataModel, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;  
private slots:
    void itemRemoved(CWebDavDataItem *parent, int start, int end);
    void itemInserted(CWebDavDataItem *parent, int start, int end);
private:
    CWebDavDataModel *m_dataModel;
    QFileIconProvider m_iconProvider;
};

#endif // CWEBDAVITEMMODEL_H
