#include "GEUtils/FunctionUtils.h"

#include <cmath>

// 返回值 [0.0f, 1.0f)
float RandXY(float x, float y)
{
     //return fract(cos(x * (12.9898) + y * (4.1414)) * 43758.5453);
     float temp = cos(x * (12.9898) + y * (4.1414)) * 43758.5453;
     float result = temp - floor(temp);
     return result;
}

void ExtractName(const std::string &filepath, std::string &name)
{
     auto lastSlash = filepath.find_last_of("/\\");
     lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
     auto lastDot = filepath.rfind('.');
     auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
     name = filepath.substr(lastSlash, count);
}
