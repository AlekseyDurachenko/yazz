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
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
    connect(this, SIGNAL(destroyed()), this, SLOT(deleteLater()));
}

void QtAbstractWebDavReply::replyFinished()
{
    int code = m_reply->attribute
            (QNetworkRequest::HttpStatusCodeAttribute).toInt();
    m_errorString = m_reply->attribute
            (QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();

    switch (code)
    {
    case 201:
    case 200:
        m_error = NoError;
        break;
    case 204:
        if (m_operation != Remove)
            m_error = NoError;
        else
            m_error = NoContent;
        break;
    case 207:
        m_error = MultiStatus;
        break;
    case 401:
        m_error = AccessDenied;
        break;
    case 403:
        m_error = Forbidden;
        break;
    case 404:
        m_error = NotFound;
        break;
    case 405:
        m_error = MethodNotAllowed;
        break;
    case 409:
        m_error = Conflict;
        break;
    case 412:
        m_error = PreconditionFailed;
        break;
    case 415:
        m_error = UnsupportedMediaType;
        break;
    case 423:
        m_error = Locked;
        break;
    case 502:
        m_error = BadGateway;
        break;
    case 507:
        m_error = InsufficientStorage;
        break;
    default:
        m_error = UnknowError;
    }

    // before the finished we need to process the reply data (e.g. xml)
    processReply();

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

void QtAbstractWebDavReply::processReply()
{
}
