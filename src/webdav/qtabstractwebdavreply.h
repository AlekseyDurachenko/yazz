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
#ifndef QTABSTRACTWEBDAVREPLY_H
#define QTABSTRACTWEBDAVREPLY_H

#include <QNetworkReply>

class QtAbstractWebDavReply : public QObject
{
    Q_OBJECT
public:
    enum Operation { MakeDir, Remove, Copy, Move, Put, Get };
    explicit QtAbstractWebDavReply(Operation operation, QNetworkReply *reply, QObject *parent = 0);
    inline Operation operation() const;
    inline QNetworkReply *reply() const;
signals:
    void finished();
private:
    Operation m_operation;
    QNetworkReply *m_reply;
};

QtAbstractWebDavReply::Operation QtAbstractWebDavReply::operation() const
{
    return m_operation;
}

QNetworkReply *QtAbstractWebDavReply::reply() const
{
    return m_reply;
}

#endif // QTABSTRACTWEBDAVREPLY_H
