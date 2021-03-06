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
#include "cwebdavdatamodel.h"

CWebDavDataModel::CWebDavDataModel(QtWebDav *webdav, QObject *parent) :
    QObject(parent), m_webdav(webdav)
{
    m_rootItem = new CWebDavDataItem(this, this);
}

void CWebDavDataModel::itemRemove(CWebDavDataItem *parent, int start, int end)
{
    emit itemRemoved(parent, start, end);
}

void CWebDavDataModel::itemInsert(CWebDavDataItem *parent, int start, int end)
{
    emit itemInserted(parent, start, end);
}
