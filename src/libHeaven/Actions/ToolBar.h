/*
 * libHeaven - A Qt-based ui framework for strongly modularized applications
 * Copyright (C) 2012 Sascha Cunz <sascha@babbelbox.org>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License (Version 2) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MGV_HEAVEN_TOOLBAR_H
#define MGV_HEAVEN_TOOLBAR_H

#include <QString>
#include <QObject>

class QToolBar;

#include "libHeaven/HeavenApi.h"

namespace Heaven
{

    class Action;
    class ActionContainer;
    class MergePlace;
    class Menu;
    class UiObject;
    class ToolBarPrivate;

    class HEAVEN_API ToolBar : public QObject
    {
        Q_OBJECT
    public:
        ToolBar( QObject* parent );
        ~ToolBar();

    public:
        QToolBar* toolBarFor( QWidget* forParent );

    public:
        void add( Menu* );
        void add( Action* );
        void add( MergePlace* );
        void add( ActionContainer* );
        void addSeparator();

    public:
        UiObject* uiObject();

    private:
        ToolBarPrivate* d;
    };

}

#endif
