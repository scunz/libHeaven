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

#include "libHeaven/Views/View.h"
#include "libHeaven/Views/ViewContainer.h"

namespace Heaven
{

    View::View( const QString& identifier, ViewTypes type )
        : ViewContainerContent( NULL )
        , mIdentifier( identifier )
        , mType( type )
        , mAction( NULL )
    {
    }

    View::~View()
    {
    }

    bool View::isContainer() const
    {
        return false;
    }

    View* View::asView()
    {
        return this;
    }

    QString View::viewName() const
    {
        return mViewName;
    }

    void View::setViewName( const QString& name )
    {
        if( name != mViewName )
        {
            mViewName = name;
            emit nameChanged( mViewName );
        }
    }

    QString View::identifier() const
    {
        return mIdentifier;
    }


    ViewTypes View::type() const
    {
        return mType;
    }

    void View::aboutToRemove()
    {
    }

    QWidget* View::widget()
    {
        return this;
    }

}
