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

#ifndef MGV_HEAVEN_TOOL_PRIVATE_H
#define MGV_HEAVEN_TOOL_PRIVATE_H

#include "libHeaven/Actions/ToolBar.h"
#include "libHeaven/Actions/UiContainer.h"

namespace Heaven
{

    class ToolBarPrivate : public UiContainer
    {
        Q_OBJECT
    public:
        ToolBarPrivate( ToolBar* owner );
        ~ToolBarPrivate();

    public:
        QToolBar* createQToolBar( QWidget* forParent );
        QToolBar* getOrCreateQToolBar( QWidget* forParent );

    private slots:
        void qtoolbarDestroyed();
        void reemergeGuiElement();

    public:
        void setContainerDirty( bool value = true );
        UiObjectTypes type() const;

    public:
        bool                mRebuildQueued;
        QSet< QToolBar* >   mToolBars;
    };

}

#endif
