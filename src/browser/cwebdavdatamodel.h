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
#ifndef CWEBDAVDATAMODEL_H
#define CWEBDAVDATAMODEL_H

#include "cwebdavdataitem.h"
#include "qtwebdav.h"
#include <QObject>

class CWebDavDataModel : public QObject
{
    Q_OBJECT
    friend class CWebDavDataItem;
public:
    explicit CWebDavDataModel(QtWebDav *webdav, QObject *parent = 0);
    inline QtWebDav *webdav() const;
    inline CWebDavDataItem *rootItem() const;
signals:
    void itemInserted(CWebDavDataItem *parent, int start, int end);
    void itemRemoved(CWebDavDataItem *parent, int start, int end);
private:
    void itemRemove(CWebDavDataItem *parent, int start, int end);
    void itemInsert(CWebDavDataItem *parent, int start, int end);
private:
    QtWebDav *m_webdav;
    CWebDavDataItem *m_rootItem;
};

QtWebDav *CWebDavDataModel::webdav() const
{
    return m_webdav;
}

CWebDavDataItem *CWebDavDataModel::rootItem() const
{
    return m_rootItem;
}

#endif // CWEBDAVDATAMODEL_H
