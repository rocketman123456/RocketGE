#include "GERender/Camera.h"
#include "GERender/OrthographicCamera.h"
#include "GERender/PerspectiveCamera.h"
#include "GECore/Core.h"

namespace Rocket {
    Ref<Camera> Camera::Create(CameraType type, std::vector<float> setting)
    {
        int count = setting.size();
        switch(type)
        {
        case CameraType::None: RK_CORE_ASSERT(false, "Unknown Camera Type") return nullptr;
        case CameraType::Orthographic: 
            if(count == 4)
                return CreateRef<OrthographicCamera>(setting[0], setting[1], setting[2], setting[3]);
            else if(count == 6)
                return CreateRef<OrthographicCamera>(setting[0], setting[1], setting[2], setting[3], setting[4], setting[5]);
            else {
                RK_CORE_ASSERT(false, "Error Camera Setting") 
                return nullptr;
            }
        case CameraType::Perspective: 
            if(count == 2)
                return CreateRef<PerspectiveCamera>(setting[0], setting[1]);
            else if(count == 4)
                return CreateRef<PerspectiveCamera>(setting[0], setting[1], setting[2], setting[3]);
            else {
                RK_CORE_ASSERT(false, "Error Camera Setting") 
                return nullptr;
            }
        default: RK_CORE_ASSERT(false, "Unknown Camera Type") return nullptr;
        }
    }
}