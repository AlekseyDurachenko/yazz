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
#include "qtgetfreespacewebdavreply.h"
#include <QtXml>
#include <QDebug>

QtGetFreeSpaceWebDavReply::QtGetFreeSpaceWebDavReply(QNetworkReply *reply,
        QObject *parent) : QtAbstractWebDavReply(GetFreeSpace, reply, parent)
{
    m_usedBytes = 0;
    m_avaibleBytes = 0;
}

void QtGetFreeSpaceWebDavReply::processReply()
{
    if (error() == MultiStatus)
    {
        // TODO: This code is very simple parser. It must be changed
        //       in the future
        QXmlStreamReader xml (reply());
        while (!xml.atEnd())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "quota-used-bytes")
                {
                    if (xml.readNext() == QXmlStreamReader::Characters)
                    {
                        m_usedBytes = xml.text().toString().toLongLong();
                    }
                }
                else if (xml.name() == "quota-available-bytes")
                {
                    if (xml.readNext() == QXmlStreamReader::Characters)
                    {
                        m_avaibleBytes = xml.text().toString().toLongLong();
                    }
                }
            }
        }
        if (xml.hasError())
        {
            qDebug() << "The xml reading error:" << xml.errorString();
        }
    }
}
