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
#include "cwebdavitemmodel.h"

CWebDavItemModel::CWebDavItemModel(QObject *parent) :
        QAbstractItemModel(parent)
{
}

QVariant CWebDavItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:;
        case 1:;
        case 2:;
        }
    }

    return QVariant();
}

QVariant CWebDavItemModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return tr("Name");
        case 1:
            return tr("Size");
        case 2:
            return tr("Date");
        }
    }

    return QVariant();
}

QModelIndex CWebDavItemModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex CWebDavItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

int CWebDavItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0 || parent.isValid())
    {
        return 0;
    }

    return 0;
}

int CWebDavItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}
