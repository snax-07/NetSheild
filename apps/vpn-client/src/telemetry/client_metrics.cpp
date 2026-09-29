#include "client_metrics.hpp"

ClientMetrics::ClientMetrics(){
    _packet = {0,0};
    _byte = {0,0};
    _conn = {0,0,0,0};
    error_count = 0;
};

void ClientMetrics::record_packet_sent(std::uint64_t packet_size){
    if(packet_size <= 0){
        _packet.sent++;
        return;
    }
    _byte.sent += packet_size;
    _packet.sent++;
}

void ClientMetrics::record_packet_received(std::uint64_t packet_size){
    if(packet_size <= 0){
        _packet.recv++;
        return;
    }

    _packet.recv++;
    _byte.recv+= packet_size;
}

void ClientMetrics::record_connection_attempt(){
    _conn.conn_attempt++;
}

void ClientMetrics::record_connection_success(){
    _conn.conn_successful++;
}

void ClientMetrics::record_connection_failure(){
    _conn.conn_failed++;
}

void ClientMetrics::record_reconnect(){
    _conn.conn_reconnects++;
}

void ClientMetrics::record_error(){
    error_count++;
}

//=========GETTER=========


        const ClientMetrics::packetMeta& ClientMetrics::get_packet_meta() const{
            return _packet;
        }
        const ClientMetrics::byteMeta& ClientMetrics::get_byte_meta() const{
            return _byte;
        };
        const ClientMetrics::connMeta& ClientMetrics::get_conn_meta() const{
            return _conn;
        };
        const std::uint64_t ClientMetrics::get_errors_count() const{
            return error_count;
        };
