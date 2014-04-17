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
#include "webdav/qtwebdav.h"
#include <QFile>
#include <QDir>
#include <QDebug>

CTest::CTest(QObject *parent) : QObject(parent)
{
    QFile settings(QDir::homePath() + QDir::separator() + "test.conf");
    settings.open(QIODevice::ReadOnly);
    QString hostname = settings.readLine().trimmed();
    QString username = settings.readLine().trimmed();
    QString password = settings.readLine().trimmed();
    settings.close();
    qDebug() << hostname << username << password;

    QtWebDav *webdav = new QtWebDav(this);
    webdav->setHostname(hostname);
    webdav->setUsername(username);
    webdav->setPassword(password);
    //m_reply = webdav->remove("mydir");
    //connect(m_reply, SIGNAL(finished()), this, SLOT(finished()));
    //m_reply = webdav->mkdir("mydir/my2");
    //connect(m_reply, SIGNAL(finished()), this, SLOT(finished()));
    m_reply = webdav->copy("gori.jpg", "hren.jpg");
    connect(m_reply, SIGNAL(finished()), this, SLOT(finished()));
}

void CTest::finished()
{
    qDebug() << m_reply->readAll();
}
