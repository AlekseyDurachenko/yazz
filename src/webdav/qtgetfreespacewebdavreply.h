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
#ifndef QTGETFREESPACEWEBDAVREPLY_H
#define QTGETFREESPACEWEBDAVREPLY_H

#include "qtabstractwebdavreply.h"

class QtGetFreeSpaceWebDavReply : public QtAbstractWebDavReply
{
    Q_OBJECT
public:
    explicit QtGetFreeSpaceWebDavReply(QNetworkReply *reply, QObject *parent = 0);
    inline qint64 usedBytes() const;
    inline qint64 avaibleBytes() const;
protected:
    virtual void processReply();
private:
    qint64 m_usedBytes;
    qint64 m_avaibleBytes;
};

qint64 QtGetFreeSpaceWebDavReply::usedBytes() const
{
    return m_usedBytes;
}

qint64 QtGetFreeSpaceWebDavReply::avaibleBytes() const
{
    return m_avaibleBytes;
}


#endif // QTGETFREESPACEWEBDAVREPLY_H
