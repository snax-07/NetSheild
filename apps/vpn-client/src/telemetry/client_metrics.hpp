#pragma once

#include <cstdint>

class ClientMetrics {
    struct packetMeta {
        std::uint64_t recv;
        std::uint64_t sent;
    };

    struct byteMeta{
        std::uint64_t recv;
        std::uint64_t sent;
    };

    struct connMeta{
        std::uint64_t conn_attempt;
        std::uint64_t conn_successful;
        std::uint64_t conn_failed;
        std::uint64_t conn_reconnects;
    };

    
    private:
    packetMeta _packet;
    byteMeta _byte;
    connMeta _conn;
    std::uint64_t error_count;
    
    public:

        ClientMetrics();

        void record_packet_sent(std::uint64_t packet_size);
        void record_packet_received(std::uint64_t packet_size);
        void record_connection_attempt();
        void record_connection_success();
        void record_connection_failure();
        void record_reconnect();
        void record_error();


        const packetMeta& get_packet_meta() const;
        const byteMeta& get_byte_meta() const;
        const connMeta& get_conn_meta() const;
        const std::uint64_t get_errors_count() const;
};