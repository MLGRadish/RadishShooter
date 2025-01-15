#pragma once
#include <string>
#include <iostream>

#include <enet/enet.h>

#include "rpc.h"

class NetworkManager {
public:
    [[nodiscard]] bool connected() const
    { return _connected; }
    NetworkManager(): _client_id(0), _address(), _event()
    {
        _client = nullptr;
        _peer = nullptr;
        _connected = false;
    }

    [[nodiscard]] uint get_id() const
    { return _client_id; }

    bool connect(const std::string& host, int port, uint timeout = 5000, bool compress_data = false);
    void send(const void* data, size_t size, bool reliable = true) const;

    static void flush_send();
    void process(RPC rpc);
    void disconnect();

private:
    uint _client_id; // server side id of this client
    ENetHost * _client;
    ENetAddress _address;
    ENetEvent _event;
    ENetPeer *_peer;
    bool _connected;
};
