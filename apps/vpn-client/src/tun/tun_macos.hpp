#pragma once



#include <string>
#include <cstddef>

class TunMacOS{
    private:
        int _tunFd;
        bool _open = false;
        std::string _interface_name;

    public: 
        TunMacOS();
        ~TunMacOS();

        bool open();
        void close();

        std::size_t read(std::uint8_t* buffer , std::size_t buffer_size);
        std::size_t write(const std::uint8_t* packpacket_byteset , std::size_t packet_size);
        bool is_open() const;

        const std::string& get_interface() const;
};