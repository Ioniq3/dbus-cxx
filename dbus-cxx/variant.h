/***************************************************************************
 *   Copyright (C) 2020 by Robert Middleton                                *
 *   robert.middleton@rm5248.com                                           *
 *                                                                         *
 *   This file is part of the dbus-cxx library.                            *
 *                                                                         *
 *   The dbus-cxx library is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The dbus-cxx library is distributed in the hope that it will be       *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#ifndef DBUSCXX_VARIANT_H
#define DBUSCXX_VARIANT_H

#include <dbus-cxx/enums.h>
#include <dbus-cxx/path.h>
#include <dbus-cxx/filedescriptor.h>
#include <dbus-cxx/signature.h>
#include <string>
#include <any>
#include <stdint.h>

namespace DBus {

class MessageIterator;

class Variant {
  public:
    Variant();
    Variant( uint8_t byte );
    Variant( bool b );
    Variant( int16_t i );
    Variant( uint16_t i );
    Variant( int32_t i );
    Variant( uint32_t i );
    Variant( int64_t i );
    Variant( uint64_t i );
    Variant( double i );
    Variant( std::string str );
    explicit Variant( Signature sig );
    explicit Variant( Path path );
    explicit Variant( std::shared_ptr<FileDescriptor> fd );
    Variant( const Variant& other );

    std::string signature() const;

    DataType currentType() const;

    std::any value() const;

    static Variant createFromMessage( MessageIterator iter );

  private:
    DataType m_currentType;
    std::string m_signature;
    std::any m_data;
};

} /* namespace DBus */

#endif /* DBUSCXX_VARIANT_H */