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
#include "qtabstractwebdavreply.h"

QtAbstractWebDavReply::QtAbstractWebDavReply(Operation operation,
        QNetworkReply *reply, QObject *parent) : QObject(parent),
        m_operation(operation), m_reply(reply), m_error(NoError)
{
    connect(reply, SIGNAL(finished()), this, SLOT(processFinished()));
    connect(this, SIGNAL(destroyed()), this, SLOT(deleteLater()));
}

void QtAbstractWebDavReply::processFinished()
{
    emit finished();
}

void QtAbstractWebDavReply::setError(QtAbstractWebDavReply::Error error)
{
    m_error = error;
}

void QtAbstractWebDavReply::setErrorString(const QString &str)
{
    m_errorString = str;
}
