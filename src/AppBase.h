/*
Launchy: Application Launcher
Copyright (C) 2007-2009  Josh Karlin, Simon Capewell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#pragma once

#include <QList>
#include <QHash>
#include <QString>
#include <QFileInfo>
#include <QFileIconProvider>
#include <SingleApplication/singleapplication.h>
#include "Directory.h"

namespace launchy {

class CatItem;

class AppBase : public SingleApplication {
public:
    AppBase(int& argc, char** argv);
    virtual ~AppBase();

    QIcon icon(const QFileInfo& info);
    QIcon icon(QFileIconProvider::IconType type);
    virtual void setPreferredIconSize(int size) = 0;

    virtual QList<Directory> getDefaultCatalogDirectories() = 0;
    virtual bool isAlreadyRunning() const;
    virtual void sendInstanceCommand(int command);

    // Need to alter an indexed item?  e.g. .desktop files
    virtual void alterItem(CatItem* item);
    virtual QHash<QString, QList<QString>> getDirectories() = 0;
    virtual QString expandEnvironmentVars(QString txt) = 0;

    virtual bool supportsAlphaBorder() const;
    virtual bool getComputers(QStringList& computers) const;

protected:
    QFileIconProvider* m_iconProvider;
};

QApplication* createApplication(int& argc, char** argv);

}