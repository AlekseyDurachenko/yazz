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
#ifndef QTWEBDAV_H
#define QTWEBDAV_H

#include <QNetworkAccessManager>
#include <QUrl>
class QtMakeDirWebDavReply;
class QtRemoveWebDavReply;
class QtCopyWebDavReply;
class QtMoveWebDavReply;
class QtPutWebDavReply;
class QtGetWebDavReply;
class QtGetFreeSpaceWebDavReply;
class QtListWebDavReply;

class QtWebDav : public QNetworkAccessManager
{
    Q_OBJECT
public:
    enum ConnectionType { HTTP, HTTPS };

    explicit QtWebDav(QObject *parent = 0);
    virtual ~QtWebDav();

    inline ConnectionType connectionType() const;
    void setConnectionType(ConnectionType connectionType);

    inline const QString &hostname() const;
    inline int port() const;
    void setHostname(const QString &hostname, int port = -1);

    inline const QString &rootPath() const;
    void setRootPath(const QString &rootPath);

    inline const QString &username() const;
    void setUsername(const QString &username);

    inline const QString &password() const;
    void setPassword(const QString &password);

    QtMakeDirWebDavReply *mkdir(const QString &path);
    QtRemoveWebDavReply *remove(const QString &path);
    QtCopyWebDavReply *copy(const QString &from, const QString &to, bool overwrite = true);
    QtMoveWebDavReply *move(const QString &from, const QString &to, bool overwrite = true);

    QtPutWebDavReply *put(const QString &path, QIODevice *data = 0);
    QtGetWebDavReply *get(const QString &path, QIODevice *data = 0);

    QtGetFreeSpaceWebDavReply *getFreeSpace();
    QtListWebDavReply *list(const QString &path, int depth = 1);

    QNetworkReply *sendCustomRequest(const QNetworkRequest &request, const QByteArray &verb, const QByteArray &data);
signals:
    void authFailed();
public slots:
private slots:
    void authentication(QNetworkReply* reply, QAuthenticator *auth);
protected:
    QUrl createBaseURL() const;
    QUrl createURL(const QString &path) const;
private:
    ConnectionType m_connectionType;
    QString m_hostname;
    int m_port;
    QString m_rootPath;
    QString m_username;
    QString m_password;
    QNetworkReply *m_authReply;
};

QtWebDav::ConnectionType QtWebDav::connectionType() const
{
    return m_connectionType;
}

const QString &QtWebDav::hostname() const
{
    return m_hostname;
}

int QtWebDav::port() const
{
    return m_port;
}

const QString &QtWebDav::rootPath() const
{
    return m_rootPath;
}

const QString &QtWebDav::username() const
{
    return m_username;
}

const QString &QtWebDav::password() const
{
    return m_password;
}

#endif // QTWEBDAV_H
