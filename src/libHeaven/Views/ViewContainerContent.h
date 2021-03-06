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

#ifndef MGV_HEAVEN_VIEW_CONTAINER_CONTENT_H
#define MGV_HEAVEN_VIEW_CONTAINER_CONTENT_H

#include "libHeaven/HeavenApi.h"

class QWidget;

namespace Heaven
{

    class ViewContainer;
    class View;

    class HEAVEN_API ViewContainerContent
    {
    public:
        ViewContainerContent( ViewContainer* parent = NULL );
        virtual ~ViewContainerContent();

    public:
        virtual bool isContainer() const = 0;
        virtual View* asView();
        virtual ViewContainer* asContainer();
        virtual QWidget* widget() = 0;

        void setContainer( ViewContainer* parent );
        ViewContainer* container() const;

    private:
        ViewContainer* mParentContainer;
    };

}

#endif
