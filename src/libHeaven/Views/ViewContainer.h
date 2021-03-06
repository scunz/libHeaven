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

#ifndef HEAVEN_CONTAINER_H
#define HEAVEN_CONTAINER_H

#include <QObject>
#include <QSet>

#include "libHeaven/HeavenApi.h"
#include "libHeaven/Views/ViewContainerContent.h"

class QSplitter;

namespace Heaven
{

    class MultiBarContainer;
    class TabWidget;
    class View;

    class HEAVEN_API ViewContainer : public QObject, public ViewContainerContent
    {
        Q_OBJECT
    public:
        enum Type
        {
            Tab             = 1 << 8,
            Splitter        = 1 << 9,
            MultiBar        = 1 << 10,
            BaseMask        = Tab | Splitter | MultiBar,

            SubTabTop       = 0,
            SubTabBottom    = 1,
            SubTabRight     = 2,
            SubTabLeft      = 3,

            SubSplitVert    = 0,
            SubSplitHorz    = 1,

            SubMask         = 255
        };

    public:
        ViewContainer( Type t, Type s, ViewContainer* parent = NULL );
        ~ViewContainer();

    public:
        Type type() const;

        void clear();

        QList< View* > views() const;
        int numViews() const;
        int addView( View* view );
        QWidget* containerWidget();

        QList< ViewContainer* > containers() const;
        int numContainers() const;
        int addContainer( ViewContainer* container );
        void insertContainer( int pos, ViewContainer* container );

        ViewContainerContent* take( ViewContainerContent* cc );
        ViewContainerContent* takeAt( int index );
        int indexOf( ViewContainerContent* cc ) const;
        QList< ViewContainerContent* > contents() const;

    public:
        bool isContainer() const;
        ViewContainer* asContainer();
        QWidget* widget();

    private:
        Type                            mType;
        QList< ViewContainerContent* >  mContents;

        union
        {
            QWidget*            mContainerWidget;
            QSplitter*          mSpliterWidget;
            TabWidget*          mTabWidget;
            MultiBarContainer*  mMultiBarContainer;
        };
    };

}

#endif
