#include "NetworkManager.h"
#include "enet/enet.h"
#include <cstdio>
#include <cstring>
#include <string>

bool NetworkManager::connect(const std::string& host, const int port, const uint timeout, const bool compress_data) {
    if (enet_initialize() != 0) {
        printf("[RPC Client]: An error occurred while initializing ENet.\n");
        return false;
    }

    _client = enet_host_create(nullptr, 1, 4, 0, 0);
    if (_client == nullptr) {
        printf("[RPC Client]: An error occurred while trying to create an ENet client host.\n");
        return false;
    }

    enet_address_set_host(&_address, host.c_str());
    _address.port = port;
    _peer = enet_host_connect(_client, &_address, 4, 0);

    if (_peer == nullptr) {
        printf("[RPC Client]: No available peers for initiating an ENet connection.\n");
        return false;
    }

    if (compress_data) {
        enet_host_compress_with_range_coder(_client);
    }

    if (enet_host_service(_client, &_event, timeout) > 0 && _event.type == ENET_EVENT_TYPE_CONNECT) {
        printf("[RPC Client]: Connected!\n");
    } else {
        enet_peer_reset(_peer);
        printf("[RPC Client]: Connection to %s:%i failed.\n", host.c_str(), port);
        return false;
    }

    _connected = true;

    enet_peer_timeout(_peer, timeout, 0, timeout);
    return true;
}

void NetworkManager::send(const void* data, const size_t size, const bool reliable) const
{
    if (!_connected) return;
    if (size == 0) return;

    ENetPacket * packet = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE :
                ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(_peer, 0, packet);
}

void NetworkManager::flush_send() {
    /*for (int i = 0; i < 2; ++i) {
        std::vector<unsigned char> &snd = *(_rpc.get_send(i));
        if (snd.size() > 0) {
            send(snd, false);
            snd.clear();
        }
    }*/
}

void NetworkManager::process(RPC rpc) {
    flush_send();
    while (enet_host_service(_client, &_event, 0) > 0) {
        if (_event.type == ENET_EVENT_TYPE_DISCONNECT) {
            printf("[RPC Client]: server disconnected.\n");
            _connected = false;
        }

        if (_event.type == ENET_EVENT_TYPE_RECEIVE) {
            if (_event.packet->dataLength > 0) {
                //message::Message msg;
                //msg.ParseFromArray(_event.packet->data, _event.packet->dataLength);

                //rpc.proc(&msg, _event);
            }
            enet_packet_destroy(_event.packet);
        }
    }
}

void NetworkManager::disconnect() {
    enet_peer_disconnect_now(_peer, 0);
    enet_host_destroy(_client);
    enet_deinitialize();
    _connected = false;
}
