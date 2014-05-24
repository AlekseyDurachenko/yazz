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
#ifndef CTESTWIDGET_H
#define CTESTWIDGET_H

#include <QWidget>
#include "qtwebdav.h"

namespace Ui {
class CTestWidget;
}

class CTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTestWidget(QWidget *parent = 0);
    ~CTestWidget();

private:
    Ui::CTestWidget *ui;
    QtWebDav *m_webdav;
};

#endif // CTESTWIDGET_H
