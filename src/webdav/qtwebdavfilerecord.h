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
#ifndef QTWEBDAVFILERECORD_H
#define QTWEBDAVFILERECORD_H

#include <QString>
#include <QDateTime>
#include <QDebug>

class QtWebDavFileRecord
{
public:
    QtWebDavFileRecord();

    inline const QString &href() const;
    void setHref(const QString &href);

    inline const QString &displayName() const;
    void setDisplayName(const QString &displayName);

    inline bool isCollection() const;
    void setCollectionFlag(bool collectionFlag);

    inline const QString &etag() const;
    void setEtag(const QString &etag);

    inline qint64 contentLength() const;
    void setContentLength(qint64 len);

    inline const QDateTime &creationDateTime() const;
    void setCreationDateTime(const QDateTime &dateTime);

    inline const QDateTime &lastModifiedDateTime() const;
    void setLastModifiedDateTime(const QDateTime &dateTime);
private:
    QString m_href;
    QString m_displayName;
    QString m_etag;
    qint64 m_contentLength;
    bool m_collectionFlag;
    QDateTime m_creationDateTime;
    QDateTime m_lastModifiedDateTime;
};

const QString &QtWebDavFileRecord::href() const
{
    return m_href;
}

const QString &QtWebDavFileRecord::displayName() const
{
    return m_displayName;
}

bool QtWebDavFileRecord::isCollection() const
{
    return m_collectionFlag;
}

const QString &QtWebDavFileRecord::etag() const
{
    return m_etag;
}

qint64 QtWebDavFileRecord::contentLength() const
{
    return m_contentLength;
}

const QDateTime &QtWebDavFileRecord::creationDateTime() const
{
    return m_creationDateTime;
}

const QDateTime &QtWebDavFileRecord::lastModifiedDateTime() const
{
    return m_lastModifiedDateTime;
}

QDebug operator << (QDebug dbg, const QtWebDavFileRecord &c);

#endif // QTWEBDAVFILERECORD_H
