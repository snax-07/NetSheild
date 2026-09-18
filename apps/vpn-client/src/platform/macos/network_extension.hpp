#pragma once 

class MacOsNetworkExtension{
    private:
        bool _initialized = false;
    
    public:
        MacOsNetworkExtension();
        ~MacOsNetworkExtension();


        bool initialize();
        void shutdown();
        bool is_initialized() const;
};