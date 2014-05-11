// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#include "qtwebdavfilerecord.h"

QtWebDavFileRecord::QtWebDavFileRecord()
{
    m_contentLength = 0;
    m_collectionFlag = false;
}

void QtWebDavFileRecord::setHref(const QString &href)
{
    m_href = href;
}

void QtWebDavFileRecord::setDisplayName(const QString &displayName)
{
    m_displayName = displayName;
}

void QtWebDavFileRecord::setCollectionFlag(bool collectionFlag)
{
    m_collectionFlag = collectionFlag;
}

void QtWebDavFileRecord::setEtag(const QString &etag)
{
    m_etag = etag;
}

void QtWebDavFileRecord::setContentLength(qint64 len)
{
    m_contentLength = len;
}

void QtWebDavFileRecord::setCreationDateTime(const QDateTime &dateTime)
{
    m_creationDateTime = dateTime;
}

void QtWebDavFileRecord::setLastModifiedDateTime(const QDateTime &dateTime)
{
    m_lastModifiedDateTime = dateTime;
}

QDebug operator << (QDebug dbg, const QtWebDavFileRecord &c)
{
    dbg.nospace() << "(";
    dbg.nospace() << "href = " << c.href() << " , ";
    dbg.nospace() << "displayName = " << c.displayName() << " , ";
    dbg.nospace() << "isCollection = " << c.isCollection() << " , ";
    dbg.nospace() << "etag = " << c.etag() << " , ";
    dbg.nospace() << "createionDateTime = " << c.creationDateTime() << " , ";
    dbg.nospace() << "lastModifiedDateTime = " << c.lastModifiedDateTime() << " , ";
    dbg.nospace() << ")";

    return dbg.space();
}
