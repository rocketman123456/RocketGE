/* Copyright (C) Scott Bilas, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */
#pragma once

/* Sample Usage
class TextureMgr : public Singleton <TextureMgr>
{
public:
    Texture* GetTexture( const char* name );
    // ...
};

#define g_TextureMgr TextureMgr::GetSingleton()

void SomeFunction( void )
{
    Texture* stone1 = TextureMgr::GetSingleton().GetTexture( "stone1" );
    Texture* wood6 = g_TextureMgr.GetTexture( "wood6" );
    // ...
}
*/

template <typename T> class Singleton
{
    static T* s_Singleton;

public:
    Singleton( void )
    {
        assert( !s_Singleton );
        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
        s_Singleton = (T*)((int)this + offset);
    }
    ~Singleton( void )
        {  assert( s_Singleton );  s_Singleton = 0;  }
    static T& GetSingleton( void )
        {  assert( s_Singleton );  return ( *s_Singleton );  }
    static T* GetSingletonPtr( void )
        {  return ( s_Singleton );  }
};

template <typename T> T* Singleton <T>::s_Singleton = 0;
