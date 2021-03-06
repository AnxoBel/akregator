/*
    This file is part of Akregator.

    Copyright (C) 2008 Frank Osterfeld <osterfeld@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#ifndef AKREGATOR_FEEDLISTMANAGEMENTINTERFACE_H
#define AKREGATOR_FEEDLISTMANAGEMENTINTERFACE_H

#include "akregatorinterfaces_export.h"

class QString;
class QStringList;

namespace Akregator {
class AKREGATORINTERFACES_EXPORT FeedListManagementInterface
{
public:
    static FeedListManagementInterface *instance();
    static void setInstance(FeedListManagementInterface *);

    virtual ~FeedListManagementInterface();

    virtual QStringList categories() const = 0;
    virtual QStringList feeds(const QString &catId) const = 0;
    virtual void addFeed(const QString &url, const QString &catId) = 0;
    virtual void removeFeed(const QString &url, const QString &catId) = 0;
    virtual QString getCategoryName(const QString &catId) const = 0;

private:
    static FeedListManagementInterface *m_instance;
};
}

#endif // AKREGATOR_FEEDLISTMANAGEMENTINTERFACE_H
