#pragma once   

class LinuxNetworkManager{
    private:
        bool _initialized = false;
    
    public:
        LinuxNetworkManager();
        ~LinuxNetworkManager();


        bool initialize();
        void shutdown();
        bool is_initialized() const;
};