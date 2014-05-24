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
#include <QDebug>

CWebDavItemModel::CWebDavItemModel(CWebDavDataModel *dataModel,
        QObject *parent) : QAbstractItemModel(parent), m_dataModel(dataModel)
{
    connect(dataModel, SIGNAL(itemInserted(CWebDavDataItem*,int,int)),
            this, SLOT(itemInserted(CWebDavDataItem*,int,int)));
    connect(dataModel, SIGNAL(itemRemoved(CWebDavDataItem*,int,int)),
            this, SLOT(itemRemoved(CWebDavDataItem*,int,int)));
}

QVariant CWebDavItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    CWebDavDataItem *item =
            static_cast<CWebDavDataItem *>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return item->fileRecord().displayName();
        case 1:
            return item->fileRecord().contentLength();
        }
    }
    else if (role == Qt::DecorationRole && index.column() == 0)
    {
        if (item->fileRecord().isCollection())
        {
            return m_iconProvider.icon(QFileIconProvider::Folder);
        }
        else
        {
            return m_iconProvider.icon(QFileIconProvider::File);
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

    CWebDavDataItem *parentItem = 0;
    if (!parent.isValid())
    {
        parentItem = m_dataModel->rootItem();
    }
    else
    {
        parentItem = static_cast<CWebDavDataItem *>(parent.internalPointer());
    }

    CWebDavDataItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex CWebDavItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    CWebDavDataItem *childItem =
            static_cast<CWebDavDataItem *>(index.internalPointer());
    CWebDavDataItem *parentItem =
            qobject_cast<CWebDavDataItem *>(childItem->parent());

    if (parentItem == m_dataModel->rootItem())
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int CWebDavItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    CWebDavDataItem *parentItem = 0;
    if (!parent.isValid())
    {
        parentItem = m_dataModel->rootItem();
    }
    else
    {
        parentItem = static_cast<CWebDavDataItem *>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int CWebDavItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

void CWebDavItemModel::itemRemoved(CWebDavDataItem *parent, int start, int end)
{
    if (parent == m_dataModel->rootItem())
    {
        beginRemoveRows(QModelIndex(), start, end);
    }
    else
    {
        beginRemoveRows(createIndex(parent->row(), 0, parent), start, end);
    }
    endRemoveRows();
}

void CWebDavItemModel::itemInserted(CWebDavDataItem *parent, int start, int end)
{
    if (parent == m_dataModel->rootItem())
    {
        beginInsertRows(QModelIndex(), start, end);
    }
    else
    {
        beginInsertRows(createIndex(parent->row(), 0, parent), start, end);
    }
    endInsertRows();
}
