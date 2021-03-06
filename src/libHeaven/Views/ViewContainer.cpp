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

#include <QDebug>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QSplitter>

#include "libHeaven/Views/Decorator.h"
#include "libHeaven/Views/ViewContainer.h"
#include "libHeaven/Views/View.h"

#include "libHeaven/MultiBar/MultiBarContainer.hpp"

#include "Widgets/MiniSplitter.h"
#include "Widgets/TabWidget.h"

namespace Heaven
{

    ViewContainer::ViewContainer( Type t, Type s, ViewContainer* parent )
        : QObject( parent )
        , mType( Type( t | s ) )
        , mContainerWidget( NULL )
    {
        switch( t & BaseMask )
        {
        case Tab:
            mTabWidget = new TabWidget;
            switch( s )
            {
            case SubTabLeft:    mTabWidget->setTabPos( TabBar::West );  break;
            case SubTabRight:   mTabWidget->setTabPos( TabBar::East );  break;
            case SubTabTop:     mTabWidget->setTabPos( TabBar::North ); break;
            case SubTabBottom:  mTabWidget->setTabPos( TabBar::South ); break;
            default: break;
            }

            break;

        case MultiBar:
            mMultiBarContainer = new MultiBarContainer;
            switch( s )
            {
            case SubTabLeft:    mMultiBarContainer->setBarPos( MultiBarContainer::West );   break;
            case SubTabRight:   mMultiBarContainer->setBarPos( MultiBarContainer::East );   break;
            case SubTabTop:     mMultiBarContainer->setBarPos( MultiBarContainer::North );  break;
            case SubTabBottom:  mMultiBarContainer->setBarPos( MultiBarContainer::South );  break;
            default: break;
            }

            break;

        case Splitter:
            mSpliterWidget = new MiniSplitter( s == SubSplitHorz ? Qt::Horizontal : Qt::Vertical );
            break;

        default:
            Q_ASSERT( false );
            break;
        }
    }

    ViewContainer::~ViewContainer()
    {
    }

    ViewContainer::Type ViewContainer::type() const
    {
        return mType;
    }

    void ViewContainer::clear()
    {
        while( mContents.count() )
        {
            if( mContents[ 0 ]->isContainer() )
            {
                ViewContainer* child = mContents[ 0 ]->asContainer();
                takeAt( 0 );
                child->clear();
                child->deleteLater();
            }
            else
            {
                View* child = mContents[ 0 ]->asView();
                takeAt( 0 );
                child->deleteLater();
            }
        }
    }

    QList< View* > ViewContainer::views() const
    {
        QList< View* > r;

        for( int j = 0; j < mContents.count(); j++ )
        {
            if( !mContents[ j ]->isContainer() )
            {
                r.append( mContents[ j ]->asView() );
            }
        }

        return r;
    }

    int ViewContainer::numViews() const
    {
        int n = 0;

        for( int j = 0; j < mContents.count(); j++ )
        {
            if( !mContents[ j ]->isContainer() )
            {
                n++;
            }
        }

        return n;
    }

    QList< ViewContainer* > ViewContainer::containers() const
    {
        QList< ViewContainer* > r;

        for( int j = 0; j < mContents.count(); j++ )
        {
            if( mContents[ j ]->isContainer() )
            {
                r.append( mContents[ j ]->asContainer() );
            }
        }

        return r;
    }

    int ViewContainer::numContainers() const
    {
        int n = 0;

        for( int j = 0; j < mContents.count(); j++ )
        {
            if( mContents[ j ]->isContainer() )
            {
                n++;
            }
        }

        return n;
    }

    int ViewContainer::addView( View* view )
    {
        if( view->container() )
        {
            view->container()->take( view );
        }
        mContents.append( view );
        view->setContainer( this );

        switch( mType & BaseMask )
        {
        case Tab:
            return mTabWidget->addTab( view, view->viewName() );

        case MultiBar:
            return mMultiBarContainer->addView( view );

        case Splitter:
            {
                QWidget* wrapper = new QWidget;
                QVBoxLayout* l = new QVBoxLayout;
                l->setSpacing( 0 );
                l->setMargin( 0 );
                l->addWidget( new Decorator( view ) );
                l->addWidget( view );
                wrapper->setLayout( l );
                mSpliterWidget->addWidget( wrapper );
            }
            return mContents.count() - 1;

        default:
            Q_ASSERT( false );
            return -1;
        }
    }

    int ViewContainer::addContainer( ViewContainer* container )
    {
        int pos = mContents.count();
        insertContainer( pos, container );
        return pos;
    }

    void ViewContainer::insertContainer( int pos, ViewContainer* container )
    {
        mContents.insert( pos, container );

        switch( mType & BaseMask )
        {
        case Tab:
            qDebug() << "libHeaven: Inserting container into another container...";
            mTabWidget->insertTab( pos, container->containerWidget(), trUtf8( "Container" ) );
            return;

        case MultiBar:
            qDebug() << "libHeaven: Inserting container into another container...";
            mMultiBarContainer->insertView( pos, container );
            break;

        case Splitter:
            mSpliterWidget->insertWidget( pos, container->containerWidget() );
            return;

        default:
            Q_ASSERT( false );
            return;
        }
    }

    int ViewContainer::indexOf( ViewContainerContent* cc ) const
    {
        return mContents.indexOf( cc );
    }

    ViewContainerContent* ViewContainer::take( ViewContainerContent* cc )
    {
        if( !cc )
        {
            return NULL;
        }

        Q_ASSERT( !cc->isContainer() );

        int i = indexOf( cc );
        Q_ASSERT( i != -1 );

        ViewContainerContent* cc2 = takeAt( i );
        Q_ASSERT( cc2 == cc );
        return cc2;
    }

    ViewContainerContent* ViewContainer::takeAt( int index )
    {
        ViewContainerContent* cc = mContents[ index ];
        mContents.removeAt( index );

        if( !cc )
        {
            return NULL;
        }

        cc->setContainer( NULL );
        QWidget* w = cc->widget();

        switch( mType & BaseMask )
        {
        case Tab:
            w->hide();
            w->setParent( NULL );
            mTabWidget->removeTab( index );
            break;

        case MultiBar:
            w->hide();
            w->setParent( NULL );
            mMultiBarContainer->takeView( index );
            break;

        case Splitter:
            if( mSpliterWidget->indexOf( w ) == -1 )
            {
                w = w->parentWidget();
                Q_ASSERT( mSpliterWidget->indexOf( w ) != -1 );
                w->hide();
                w->setParent( NULL );
                w->deleteLater();
            }
            else
            {
                w->hide();
                w->setParent( NULL );
            }
            break;

        default:
            Q_ASSERT( false );
            return NULL;
        }

        return cc;
    }

    QWidget* ViewContainer::containerWidget()
    {
        return mContainerWidget;
    }

    bool ViewContainer::isContainer() const
    {
        return true;
    }

    ViewContainer* ViewContainer::asContainer()
    {
        return this;
    }

    QList< ViewContainerContent* > ViewContainer::contents() const
    {
        return mContents;
    }

    QWidget* ViewContainer::widget()
    {
        return mContainerWidget;
    }

}
