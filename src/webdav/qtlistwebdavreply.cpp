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
#include "qtlistwebdavreply.h"
#include <QtXml>

QtListWebDavReply::QtListWebDavReply(const QString &path, QNetworkReply *reply,
        QObject *parent) : QtAbstractWebDavReply(List, reply, parent)
{
    m_path = path;
}

void QtListWebDavReply::processReply()
{
    if (error() == MultiStatus)
    {
        QDomDocument doc;
        doc.setContent(reply()->readAll());

        QDomNode response = doc.documentElement().firstChild();
        while (!response.isNull())
        {
            m_fileList.push_back(parseResponse(response));
            response = response.nextSibling();
        }
    }
}

QtWebDavFileRecord QtListWebDavReply::parseResponse(const QDomNode &response)
{
    QtWebDavFileRecord fileRecord;
    QDomNode node = response.firstChild();
    while (!node.isNull())
    {
        QDomElement elem = node.toElement();
        if (elem.tagName() == "d:href")
        {
            fileRecord.setHref(elem.text().trimmed());
        }
        else if (elem.tagName() == "d:propstat")
        {
            QDomNode propstats = node.firstChild();
            while (!propstats.isNull())
            {
                QDomElement elem = propstats.toElement();
                if (elem.tagName() == "d:prop")
                {
                    QDomNode props = propstats.firstChild();
                    while (!props.isNull())
                    {
                        QDomElement elem = props.toElement();
                        if (elem.tagName() == "d:resourcetype")
                        {
                            if (props.hasChildNodes())
                            {
                                fileRecord.setCollectionFlag(true);
                            }
                        }
                        else if (elem.tagName() == "d:getlastmodified")
                        {
                            QString str = elem.text().trimmed();
                            QLocale locale(QLocale::English, QLocale::UnitedStates);
                            QDateTime dt = locale.toDateTime
                                    (str.mid(5, 20), "d MMM yyyy hh:mm:ss");
                            dt.setTimeSpec(Qt::UTC);
                            fileRecord.setLastModifiedDateTime(dt);
                        }
                        else if (elem.tagName() == "d:displayname")
                        {
                            fileRecord.setDisplayName(elem.text().trimmed());
                        }
                        else if (elem.tagName() == "d:creationdate")
                        {
                            fileRecord.setCreationDateTime
                                    (QDateTime::fromString
                                        (elem.text().trimmed(), Qt::ISODate));
                        }
                        else if (elem.tagName() == "d:getcontentlength")
                        {
                            fileRecord.setContentLength
                                    (elem.text().trimmed().toLongLong());
                        }
                        else if (elem.tagName() == "d:getetag")
                        {
                            fileRecord.setEtag(elem.text().trimmed());
                        }
                        else
                        {
                            qDebug() << "Unknow porp: "
                                     << elem.tagName() << elem.text()
                                     << elem.attributes().count();
                        }
                        props = props.nextSibling();
                    }
                }
                propstats = propstats.nextSibling();
            }
        }

        node = node.nextSibling();
    }

    return fileRecord;
}
