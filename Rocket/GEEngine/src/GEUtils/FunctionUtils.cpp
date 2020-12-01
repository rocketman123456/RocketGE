#include "GEUtils/FunctionUtils.h"

#include <cmath>
#include <glad/glad.h>

// 返回值 [0.0f, 1.0f)
float RandXY(float x, float y){
     //return fract(cos(x * (12.9898) + y * (4.1414)) * 43758.5453);
     float temp = cos(x * (12.9898) + y * (4.1414)) * 43758.5453;
     float result = temp - floor(temp);
     return result;
}
