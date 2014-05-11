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
#ifndef QTLISTWEBDAVREPLY_H
#define QTLISTWEBDAVREPLY_H

#include "qtabstractwebdavreply.h"
#include "qtwebdavfilerecord.h"
#include <QDomNode>

class QtListWebDavReply : public QtAbstractWebDavReply
{
    Q_OBJECT
public:
    explicit QtListWebDavReply(const QString &path, QNetworkReply *reply, QObject *parent = 0);
    inline const QString &path() const;
    inline const QList<QtWebDavFileRecord> &fileList() const;
protected:
    virtual void processReply();
private:
    QtWebDavFileRecord parseResponse(const QDomNode &node);
private:
    QList<QtWebDavFileRecord> m_fileList;
    QString m_path;
};

const QString &QtListWebDavReply::path() const
{
    return m_path;
}

const QList<QtWebDavFileRecord> &QtListWebDavReply::fileList() const
{
    return m_fileList;
}

#endif // QTLISTWEBDAVREPLY_H
