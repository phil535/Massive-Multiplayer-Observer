#include "WebsocketServer.h"
#include "Game.h"

#include <string>

using websocketpp::lib::mutex;
using websocketpp::lib::lock_guard;

WebsocketServer::WebsocketServer()
{
  // disable logging
  server_.clear_access_channels(websocketpp::log::alevel::all);
  server_.clear_error_channels(websocketpp::log::alevel::all);
}

/*--------------------------------------------------------------------------------------------------------------------*/
WebsocketServer::~WebsocketServer()
{
  server_.stop();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::run(int port)
{
  using websocketpp::lib::placeholders::_1;
  using websocketpp::lib::placeholders::_2;
  using websocketpp::lib::bind;

  server_.set_open_handler(bind(&WebsocketServer::onOpen, this, _1));
  server_.set_message_handler(bind(&WebsocketServer::onMessage, this, _1, _2));
  server_.set_close_handler(bind(&WebsocketServer::onClose, this, _1));

  server_.init_asio();
  server_.listen(port);
  server_.start_accept();

  server_.run();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::stop()
{
  server_.stop();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::onOpen(websocketpp::connection_hdl hdl)
{
  lock_guard<mutex> guard(mutex_front_ends_);

  // add new connection
  front_ends_.insert(hdl);

  // update current state
  std::stringstream ss("");

  ss << "boardsize=" << Game::instance().getBoardSize() << "\n";
  server_.send(hdl, ss.str(), websocketpp::frame::opcode::text);

  for(auto & x : Game::instance().)
  {

  }

}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::onMessage(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg)
{
  // ignore all front_end messages
}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::onClose(websocketpp::connection_hdl hdl)
{
  lock_guard<mutex> guard(mutex_front_ends_);
  front_ends_.erase(hdl);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void WebsocketServer::broadcastMessage(std::string msg)
{
  lock_guard<mutex> guard(mutex_front_ends_);
  for(auto &hdl : front_ends_)
    server_.send(hdl, msg, websocketpp::frame::opcode::text);
}