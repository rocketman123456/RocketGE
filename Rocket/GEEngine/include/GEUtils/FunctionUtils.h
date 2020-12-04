#pragma once
#include "GECore/Core.h"

// 返回值 [0.0f, 1.0f)
float RandXY(float x, float y);
// Extract Name From Path
void ExtractName(const std::string& filepath, std::string& name);
