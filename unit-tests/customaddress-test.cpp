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
#include <unistd.h>
#include <dbus-cxx.h>
#include <stdlib.h>

int main( int argc, char** argv ){
  std::string dbusAddress = std::string( getenv( "CUSTOM_DBUS_ADDRESS" ) );
  DBus::init();
  std::shared_ptr<DBus::Dispatcher> dispatch = DBus::Dispatcher::create();
  std::shared_ptr<DBus::Connection> conn = dispatch->create_connection( dbusAddress );

  if( conn->is_valid() ) return 0;

  return 1;
}