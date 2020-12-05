#pragma once

template <typename T> class Singleton
{
public:
    static T& GetSingleton( void )
    {  
        static T instance;
        return instance;  
    }
};
