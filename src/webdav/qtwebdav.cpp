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
#include "qtmakedirwebdavreply.h"
#include "qtremovewebdavreply.h"
#include "qtcopywebdavreply.h"
#include "qtmovewebdavreply.h"
#include "qtputwebdavreply.h"
#include "qtgetwebdavreply.h"
#include "qtgetfreespacewebdavreply.h"
#include "qtlistwebdavreply.h"
#include <QNetworkReply>
#include <QAuthenticator>
#include <QBuffer>
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
    if (rootPath.isEmpty())
    {
        m_rootPath = "/";
    }
    else
    {
        m_rootPath = rootPath;
    }
}

void QtWebDav::setUsername(const QString &username)
{
    m_username = username;
}

void QtWebDav::setPassword(const QString &password)
{
    m_password = password;
}

QtMakeDirWebDavReply *QtWebDav::mkdir(const QString &path)
{
    return new QtMakeDirWebDavReply(QNetworkAccessManager::sendCustomRequest
            (QNetworkRequest(createURL(path)), "MKCOL"), this);
}

QtRemoveWebDavReply *QtWebDav::remove(const QString &path)
{
    return new QtRemoveWebDavReply(QNetworkAccessManager::sendCustomRequest
            (QNetworkRequest(createURL(path)), "DELETE"), this);
}

QtCopyWebDavReply *QtWebDav::copy(const QString &from,
        const QString &to, bool overwrite)
{
    QNetworkRequest request(createURL(from));
    request.setRawHeader("Destination", createURL(to).toString().toUtf8());
    request.setRawHeader("Depth", "infinity");
    request.setRawHeader("Overwrite", ((overwrite) ? ("T") : ("F")));

    return new QtCopyWebDavReply(QNetworkAccessManager::sendCustomRequest
            (request, "COPY"), this);
}

QtMoveWebDavReply *QtWebDav::move(const QString &from,
        const QString &to, bool overwrite)
{
    QNetworkRequest request(createURL(from));
    request.setRawHeader("Destination", createURL(to).toString().toUtf8());
    request.setRawHeader("Depth", "infinity");
    request.setRawHeader("Overwrite", ((overwrite) ? ("T") : ("F")));

    return new QtMoveWebDavReply(QNetworkAccessManager::sendCustomRequest
            (request, "MOVE"), this);
}

QtPutWebDavReply *QtWebDav::put(const QString &path, QIODevice *data)
{
    QNetworkRequest request(createURL(path));
    // TODO: fill some fileds (?)

    return new QtPutWebDavReply(QNetworkAccessManager::put(request, data), this);
}

QtGetWebDavReply *QtWebDav::get(const QString &path, QIODevice *data)
{
    QNetworkReply *reply = QNetworkAccessManager::get(QNetworkRequest(createURL(path)));
    new QtNetworkReplyProxy(reply, data, this);    
    return new QtGetWebDavReply(reply, this);
}

QtGetFreeSpaceWebDavReply *QtWebDav::getFreeSpace()
{
    QNetworkRequest request(createBaseURL());
    request.setRawHeader("Depth", "0");

    QByteArray data =
            "<D:propfind xmlns:D=\"DAV:\">  "
            "  <D:prop>                     "
            "    <D:quota-available-bytes/> "
            "    <D:quota-used-bytes/>      "
            "  </D:prop>                    "
            "</D:propfind>                  ";

    return new QtGetFreeSpaceWebDavReply(sendCustomRequest
            (request, "PROPFIND", data), this);
}

// Depth == -1 => Depth == infinity (i have no idea, where should it works)
QtListWebDavReply *QtWebDav::list(const QString &path, int depth)
{
    QNetworkRequest request(createURL(path));
    request.setRawHeader("Depth",
            ((depth == -1) ? QString("infinity").toUtf8() :
                             QString::number(depth).toUtf8()));

    QByteArray data =
            "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
            "<D:propfind xmlns:D=\"DAV:\">  "
            "  <D:prop>                     "
            "    <D:creationdate/>          "
            "    <D:getlastmodified/>       "
            "    <D:getcontentlength/>      "
            "    <D:resourcetype/>          "
            "    <D:displayname/>           "
            "  </D:prop>                    "
            "</D:propfind>                  ";

    return new QtListWebDavReply(sendCustomRequest
            (request, "PROPFIND", data), this);
}

QNetworkReply *QtWebDav::sendCustomRequest(const QNetworkRequest &request,
        const QByteArray &verb, const QByteArray &data)
{
    QBuffer *buffer = new QBuffer(this);
    buffer->setData(data);
    buffer->open(QIODevice::ReadOnly);

    QNetworkReply *reply = QNetworkAccessManager::sendCustomRequest(request, verb, buffer);
    connect(reply, SIGNAL(finished()), buffer, SLOT(deleteLater()));

    return reply;
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

QUrl QtWebDav::createURL(const QString &path) const
{
    QUrl url(createBaseURL());

    if (path.startsWith("/"))
    {
        url.setPath(m_rootPath + path.mid(1));
    }
    else
    {
        url.setPath(m_rootPath + path);
    }

    return url;
}
