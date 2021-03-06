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

#ifndef HIC_PROPERTY_H
#define HIC_PROPERTY_H

#include <QVariant>

enum HICPropertyTypes
{
    HICP_Any = -1,
    HICP_NULL,
    HICP_String,
    HICP_TRString,
    HICP_Boolean,
    HICP_Integer
};

class HICProperty
{
public:
    HICProperty( const QVariant& v, HICPropertyTypes type );
    HICProperty();

    QVariant value() const;
    HICPropertyTypes type() const;

private:
    QVariant mValue;
    HICPropertyTypes mType;
};

#endif
