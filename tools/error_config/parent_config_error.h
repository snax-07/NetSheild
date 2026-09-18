#include <cstring>
#include <string>
#include <iostream>

class parent_config_error {
    private : int error_number;
    private : std::string error_message;


    public : parent_config_error(){
        this->error_message = "Hello this message is from the error.";
    };

    public : void print(std::string message){
        std::cout << "[ERROR] :: " << message;
    }
};