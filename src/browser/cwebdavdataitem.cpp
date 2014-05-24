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
#include "cwebdavdataitem.h"
#include "cwebdavdatamodel.h"

CWebDavDataItem::CWebDavDataItem(CWebDavDataModel *dataModel,
        QObject *parent) : QObject(parent), m_dataModel(dataModel)
{
    m_reply = 0;
}

CWebDavDataItem *CWebDavDataItem::child(int row)
{
    if (m_reply == 0)
    {
        m_reply = dataModel()->webdav()->list(path());
        connect(m_reply, SIGNAL(finished()), this, SLOT(reply_finished()));
    }

    if (row < m_childList.count())
    {
        return m_childList.at(row);
    }

    return 0;
}

void CWebDavDataItem::setFileRecord(const QtWebDavFileRecord &fileRecord)
{
    m_fileRecord = fileRecord;
}

int CWebDavDataItem::row() const
{
    if (m_dataModel != parent())
    {
        CWebDavDataItem *parentItem = qobject_cast<CWebDavDataItem *>(parent());
        return parentItem->childItems().indexOf
                (const_cast<CWebDavDataItem *>(this));
    }

    return 0;
}

QString CWebDavDataItem::path() const
{
    if (m_dataModel != parent())
    {
        return qobject_cast<CWebDavDataItem *>(parent())->path()
                + "/" + m_fileRecord.href();
    }

    return "/";
}

void CWebDavDataItem::reply_finished()
{
    m_dataModel->itemRemove(this, 0, 0);

    foreach (const QtWebDavFileRecord &rec, m_reply->fileList())
    {
        if (rec.href() != path())
        {
            CWebDavDataItem *item = new CWebDavDataItem(m_dataModel, this);
            item->setFileRecord(rec);
            m_childList.push_back(item);
        }
    }

    if (m_childList.count())
    {
        m_dataModel->itemInsert(this, 0, m_childList.count()-1);
    }

    m_reply->deleteLater();
}
