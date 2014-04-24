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
    enum Operation { MakeDir, Remove, Copy, Move, Put,
            Get, GetFreeSpace, List };
    enum Error { NoError = 0 };
    explicit QtAbstractWebDavReply(Operation operation, QNetworkReply *reply, QObject *parent = 0);
    inline Operation operation() const;
    inline QNetworkReply *reply() const;
    inline Error error() const;
    inline const QString &errorString() const;
signals:
    void finished();
private slots:
    virtual void processFinished();
protected:
    void setError(Error error);
    void setErrorString(const QString &str);
private:
    Operation m_operation;
    QNetworkReply *m_reply;
    Error m_error;
    QString m_errorString;
};

QtAbstractWebDavReply::Operation QtAbstractWebDavReply::operation() const
{
    return m_operation;
}

QNetworkReply *QtAbstractWebDavReply::reply() const
{
    return m_reply;
}

QtAbstractWebDavReply::Error QtAbstractWebDavReply::error() const
{
    return m_error;
}

const QString &QtAbstractWebDavReply::errorString() const
{
    return m_errorString;
}

#endif // QTABSTRACTWEBDAVREPLY_H
