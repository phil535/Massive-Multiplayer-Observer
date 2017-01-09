#ifndef GAME_WEBSOCKETSERVER_H
#define GAME_WEBSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <set>

class WebsocketServer
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    WebsocketServer();
    ~WebsocketServer();

  private:
    WebsocketServer(const WebsocketServer &rhs);
    WebsocketServer &operator=(const WebsocketServer &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
  public:
    void run(int port);
    void stop(void);

  private:
    void onOpen(websocketpp::connection_hdl hdl);
    void onClose(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
  public:
    void broadcastMessage(std::string msg);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    websocketpp::server<websocketpp::config::asio> server_;
    websocketpp::lib::mutex mutex_front_ends_;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> front_ends_;
};


#endif //GAME_WEBSOCKETSERVER_H
