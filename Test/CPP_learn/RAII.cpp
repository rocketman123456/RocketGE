#include "GEUtils/RAII.h"

int main(int argc, char** argv)
{
    
    std::mutex m;
    scope_lock<std::mutex> lock(m);

    ptr_handle_t<int> p1 = new int;
    arr_ptr_handle_t<int> p2 = new int [2];

    *p1 = 0xDEADBEEF;
    p2[1] = 0x8BADF00D;

    return 1;
}