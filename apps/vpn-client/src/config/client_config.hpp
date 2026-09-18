#include <arpa/inet.h>
#include <string>
class ClientConfig{

    ClientConfig(){}

    public :  std::string  get_udp_server_address(){}
    
    public : uint16_t get_udp_port(){}

    public : std::string get_tunnel_address(){}

    public : std::string get_dns_server_address(){}

    public : uint16_t get_mtu(){}
};