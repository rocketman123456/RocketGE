#include <iostream>

#define MY_ENUM \
    X(V1)       \
    X(V2)       \
    X(V3)

#define X(name) name,

#define MY_ENUM_NAME MyEnum

enum class MY_ENUM_NAME : char
{
    MY_ENUM
};

#undef X

constexpr const char *MyEnumToString(MyEnum e) noexcept
{
#define X(name)                \
    case (MY_ENUM_NAME::name): \
        return #name;
    switch (e)
    {
        MY_ENUM
    }
#undef X
}

int main(int argc, char **argv)
{
    std::cout << MyEnumToString(MyEnum::V1) << std::endl;
    std::cout << MyEnumToString(MyEnum::V2) << std::endl;
    std::cout << MyEnumToString(MyEnum::V3) << std::endl;
    return 1;
}