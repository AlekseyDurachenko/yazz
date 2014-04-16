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
#include "qtwebdav.h"
#include <QNetworkReply>
#include <QAuthenticator>
#include <QDebug>

// QNetworkReply::read() -> QIODevice::write()
class QtNetworkReplyProxy : public QObject
{
    Q_OBJECT
public:
    QtNetworkReplyProxy(QNetworkReply *reply, QIODevice *data, QObject *parent = 0);
private slots:
    void slot_readyRead();
private:
    QNetworkReply *m_reply;
    QIODevice *m_data;
};
#include "qtwebdav.moc"

QtNetworkReplyProxy::QtNetworkReplyProxy(QNetworkReply *reply, QIODevice *data,
        QObject *parent) : QObject(parent), m_reply(reply), m_data(data)
{
    if (reply && data)
    {
        connect(reply, SIGNAL(readyRead()), this, SLOT(slot_readyRead()));
        connect(reply, SIGNAL(finished()), this, SLOT(deleteLater()));
    }
    else
    {
        deleteLater();
    }
}

void QtNetworkReplyProxy::slot_readyRead()
{
    m_data->write(m_reply->readAll());
}



QtWebDav::QtWebDav(QObject *parent) : QNetworkAccessManager(parent)
{
    m_connectionType = HTTPS;
    m_hostname  = "";
    m_port      = -1;
    m_rootPath  = "/";
    m_username  = "";
    m_password  = "";
    m_authReply = 0;

    connect(this, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(authentication(QNetworkReply*,QAuthenticator*)));
}

QtWebDav::~QtWebDav()
{
}

void QtWebDav::setConnectionType(QtWebDav::ConnectionType connectionType)
{
    m_connectionType = connectionType;
}

void QtWebDav::setHostname(const QString &hostname, int port)
{
    m_hostname = hostname;
    m_port = port;
}

void QtWebDav::setRootPath(const QString &rootPath)
{
    m_rootPath = rootPath;
}

void QtWebDav::setUsername(const QString &username)
{
    m_username = username;
}

void QtWebDav::setPassword(const QString &password)
{
    m_password = password;
}

QNetworkReply *QtWebDav::mkdir(const QString &path)
{
    QUrl reqURL(createBaseURL());
    reqURL.setPath(m_rootPath + path);
    return sendCustomRequest(QNetworkRequest(reqURL), "MKCOL");
}

QNetworkReply *QtWebDav::remove(const QString &path)
{
    QUrl reqURL(createBaseURL());
    reqURL.setPath(m_rootPath + path);
    return sendCustomRequest(QNetworkRequest(reqURL), "DELETE");
}

void QtWebDav::authentication(QNetworkReply *reply, QAuthenticator *auth)
{
    if (reply == m_authReply)
    {
        reply->abort();
        reply->deleteLater();
        reply = 0;
        emit authFailed();
    }

    m_authReply = reply;

    auth->setUser(m_username);
    auth->setPassword(m_password);
}

QUrl QtWebDav::createBaseURL() const
{
    QUrl baseURL;

    switch (m_connectionType)
    {
    case HTTP:
        baseURL.setScheme("http");
        break;
    case HTTPS:
        baseURL.setScheme("https");
    default:
        break;
    }

    baseURL.setHost(m_hostname);
    baseURL.setPath(m_rootPath);
    baseURL.setPort(m_port);

    return baseURL;
}
