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
#ifndef CWEBDAVDATAITEM_H
#define CWEBDAVDATAITEM_H

#include <QObject>
#include "qtlistwebdavreply.h"

class CWebDavDataModel;
class CWebDavDataItem : public QObject
{
    Q_OBJECT
public:
    explicit CWebDavDataItem(CWebDavDataModel *dataModel, QObject *parent = 0);
    inline CWebDavDataModel *dataModel() const;

    inline int childCount() const;
    inline const QList<CWebDavDataItem *> childItems() const;
    CWebDavDataItem *child(int row);

    inline const QtWebDavFileRecord &fileRecord() const;
    void setFileRecord(const QtWebDavFileRecord &fileRecord);

    int row() const;
    QString path() const;
private slots:
    void reply_finished();
private:
    CWebDavDataModel *m_dataModel;
    QList<CWebDavDataItem *> m_childList;
    QtListWebDavReply *m_reply;
    QtWebDavFileRecord m_fileRecord;
};

CWebDavDataModel *CWebDavDataItem::dataModel() const
{
    return m_dataModel;
}

int CWebDavDataItem::childCount() const
{
    if (m_reply == 0 && (m_fileRecord.isCollection() || m_fileRecord.isNull()))
    {
        return 1;
    }
    else
    {
        return m_childList.count();
    }
}

const QList<CWebDavDataItem *> CWebDavDataItem::childItems() const
{
    return m_childList;
}

const QtWebDavFileRecord &CWebDavDataItem::fileRecord() const
{
    return m_fileRecord;
}

#endif // CWEBDAVDATAITEM_H
