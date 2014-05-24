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
#include "ctestwidget.h"
#include "ui_ctestwidget.h"
#include "cwebdavitemmodel.h"
#include <QFile>
#include <QDir>
#include <QDebug>

CTestWidget::CTestWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::CTestWidget)
{
    ui->setupUi(this);

    QFile settings(QDir::homePath() + QDir::separator() + "test.conf");
    Q_ASSERT(settings.open(QIODevice::ReadOnly));

    QString hostname = settings.readLine().trimmed();
    QString username = settings.readLine().trimmed();
    QString password = settings.readLine().trimmed();
    QString rootpath = settings.readLine().trimmed();

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

    CWebDavDataModel *dataModel = new CWebDavDataModel(m_webdav, this);
    CWebDavItemModel *itemModel = new CWebDavItemModel(dataModel, this);
    ui->treeView->setModel(itemModel);
}

CTestWidget::~CTestWidget()
{
    delete ui;
}
