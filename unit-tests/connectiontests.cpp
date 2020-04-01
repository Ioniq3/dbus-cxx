/***************************************************************************
 *   Copyright (C) 2019 by Robert Middleton                                *
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
#include <dbus-cxx.h>

#include "test_macros.h"

std::shared_ptr<DBus::Dispatcher> dispatch;

bool connection_create_int_signal(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::signal<int>> signal = conn->create_signal<int>( "/some/path", "signal.type", "Member" );

    return true;
}

bool connection_create_void_signal(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::signal<>> signal = conn->create_signal<>( "/some/path", "signal.type", "Member" );

    return true;
}

bool connection_create_signal_proxy(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::signal_proxy<>> proxy = conn->create_signal_proxy<>( 
        DBus::SignalMatchRule::create()
          .setInterface("interface.name")
          .setMember("myname") );

    DBus::Connection::ProxySignals map = conn->get_signal_proxies();
    TEST_ASSERT_RET_FAIL( map.size() == 1 );

    DBus::Connection::ProxySignals by_iface_name = conn->get_signal_proxies("interface.name");
    TEST_ASSERT_RET_FAIL( by_iface_name.size() == 1 );

    DBus::Connection::ProxySignals by_iface_and_member = conn->get_signal_proxies("interface.name", "myname");
    TEST_ASSERT_RET_FAIL( by_iface_and_member.size() == 1 );

    return true;
}

bool connection_get_signal_proxy_by_iface(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::signal_proxy<>> proxy = conn->create_signal_proxy<>( 
        DBus::SignalMatchRule::create()
          .setInterface("interface.name")
          .setMember("myname") );

    DBus::Connection::ProxySignals signals = conn->get_signal_proxies("interface.name");
    TEST_ASSERT_RET_FAIL( signals.size() == 1 );

    return true;
}

bool connection_get_signal_proxy_by_iface_and_name(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::signal_proxy<>> proxy = conn->create_signal_proxy<>( 
        DBus::SignalMatchRule::create()
          .setInterface("interface.name")
          .setMember("myname") );


    DBus::Connection::ProxySignals signals = conn->get_signal_proxies("interface.name", "myname");
    TEST_ASSERT_RET_FAIL( signals.size() == 1 );
    TEST_ASSERT_RET_FAIL( signals.front() == proxy );

    return true;
}

static double add(double a, double b){
    return a + b;
}

bool connection_test_method_2arg(){
    std::shared_ptr<DBus::Connection> conn = dispatch->create_connection(DBus::BusType::SESSION);

    std::shared_ptr<DBus::Object> object = conn->create_object("/dbuscxx/example/Calculator", DBus::ThreadForCalling::DispatcherThread );

    object->create_method<double(double,double)>("Calculator.Basic", "add", sigc::ptr_fun(add) );

    return true;
}

#define ADD_TEST(name) do{ if( test_name == STRINGIFY(name) ){ \
  ret = connection_##name();\
} \
} while( 0 )

int main(int argc, char** argv){
  if(argc < 1)
    return 1;

  std::string test_name = argv[1];
  bool ret = false;

  DBus::setLoggingFunction( DBus::logStdErr );
  DBus::setLogLevel( SL_TRACE );
  dispatch = DBus::Dispatcher::create();

  ADD_TEST(create_signal_proxy);
  ADD_TEST(get_signal_proxy_by_iface);
  ADD_TEST(get_signal_proxy_by_iface_and_name);
  ADD_TEST(create_void_signal);
  ADD_TEST(create_int_signal);

  return !ret;
}
