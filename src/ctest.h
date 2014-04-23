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
#ifndef CTEST_H
#define CTEST_H

#include "webdav/qtwebdav.h"
#include "webdav/qtabstractwebdavreply.h"
#include <QObject>
#include <QNetworkReply>
#include <QFile>

class CTest : public QObject
{
    Q_OBJECT
public:
    explicit CTest(QObject *parent = 0);
signals:
private slots:
    void next();
    void finished();
private:
    QtAbstractWebDavReply *m_davReply;
    QtWebDav *m_webdav;
    QFile *m_dataI;
    QFile *m_dataO;
    QString m_operation;
    int m_n;
};

#endif // CTEST_H
