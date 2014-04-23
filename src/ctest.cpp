// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "ctest.h"
#include "webdav/qtmakedirwebdavreply.h"
#include "webdav/qtremovewebdavreply.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

CTest::CTest(QObject *parent) :
        QObject(parent), m_reply(0), m_davReply(0),  m_n(0)
{
    QFile settings(QDir::homePath() + QDir::separator() + "test.conf");
    Q_ASSERT(settings.open(QIODevice::ReadOnly));

    m_dataI = new QFile(QDir::homePath() + QDir::separator() + "in.jpg", this);
    Q_ASSERT(m_dataI->open(QIODevice::ReadOnly));

    m_dataO = new QFile(QDir::homePath() + QDir::separator() + "out.jpg", this);
    Q_ASSERT(m_dataO->open(QIODevice::WriteOnly));

    QString hostname = settings.readLine().trimmed();
    QString username = settings.readLine().trimmed();
    QString password = settings.readLine().trimmed();
    QString rootpath = settings.readLine().trimmed();;

    qDebug() << "---------------------------------------";
    qDebug() << "Hostname: " << hostname;
    qDebug() << "Username: " << username;
    qDebug() << "Password: " << password;
    qDebug() << "RootPath: " << rootpath;
    qDebug() << "---------------------------------------";

    m_webdav = new QtWebDav(this);
    m_webdav->setHostname(hostname);
    m_webdav->setUsername(username);
    m_webdav->setPassword(password);
    m_webdav->setRootPath(rootpath);

    QMetaObject::invokeMethod(this, "next", Qt::QueuedConnection);
}

void CTest::next()
{
    switch (m_n++)
    {
    case 0:
        m_reply = m_webdav->getFreeSpace();
        m_operation = "Get free space";
        break;
    case 1:
        m_reply = m_webdav->list("/", 1);
        m_operation = "Get list";
        break;
    case 2:
        m_davReply = m_webdav->mkdir("people");
        m_operation = "Create directory";
        break;
    case 3:
        m_reply = m_webdav->copy("people", "people2");
        m_operation = "Copy directory";
        break;
    case 4:
        m_davReply = m_webdav->remove("people");
        m_operation = "Remove directory";
        break;
    case 5:
        m_reply = m_webdav->move("people2", "new_people");
        m_operation = "Move directory";
        break;
    case 6:
        m_reply = m_webdav->put("new_people/file.jpg", m_dataI);
        m_operation = "Put file";
        break;
    case 7:
        m_reply = m_webdav->get("new_people/file.jpg", m_dataO);
        m_operation = "Get file";
        break;
    default:
        qApp->quit();
    }

    if (m_reply)
    {
        connect(m_reply, SIGNAL(finished()), this, SLOT(finished()));
        connect(m_reply, SIGNAL(finished()), m_reply, SLOT(deleteLater()));
    }
    if (m_davReply)
    {
        connect(m_davReply, SIGNAL(finished()), this, SLOT(finished()));
        connect(m_davReply, SIGNAL(finished()), m_davReply, SLOT(deleteLater()));
    }
}

void CTest::finished()
{
    if (m_n != 3 && m_n != 5)
    {
        qDebug() << "Operation  : " << m_operation;
        qDebug() << "---------------------------------------";
        qDebug() << "Error      : " << m_reply->error() << m_reply->errorString();
        qDebug() << "Status Code: " << m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Phase attr : " << m_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();
        qDebug() << "---------------------------------------";
        qDebug() << m_reply->readAll();
        qDebug() << "---------------------------------------";
    }
    else
    {
        qDebug() << "Operation  : " << m_operation;
        qDebug() << "---------------------------------------";
        qDebug() << "Error      : " << m_davReply->reply()->error() << m_davReply->reply()->errorString();
        qDebug() << "Status Code: " << m_davReply->reply()->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Phase attr : " << m_davReply->reply()->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();
        qDebug() << "---------------------------------------";
        qDebug() << m_davReply->reply()->readAll();
        qDebug() << "---------------------------------------";
    }

    m_reply = 0;
    m_davReply = 0;

    QMetaObject::invokeMethod(this, "next", Qt::QueuedConnection);
}
