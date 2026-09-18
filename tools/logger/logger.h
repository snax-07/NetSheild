#include <tools/error_config/parent_config_error.h>
#include <string>
#include <iostream>

class logger{

    private : parent_config_error* error_parent;
    public : logger(){
        this->error_parent = new parent_config_error();
    }

    public :void print_error(std::string message){
        error_parent->print(message.length() <= 0 ? "CONFIG ERROR." : message);
    }

    public : void print_info(std::string message){
        std::cout << "[INFO] :: " << message;
    }

    public: void print_log(std::string message){
        std::cout << '[LOG] :: ' << message;
    }
};