#include "GECommon/CameraController.h"
#include "GECommon/OrthographicCameraController.h"
#include "GECommon/PerspectiveCameraController.h"

namespace Rocket {
    Ref<CameraController> CameraControllerCreate(CameraControllerType type, float aspectRatio)
    {
        switch(type)
        {
        case CameraControllerType::None: RK_CORE_ASSET(false, "Unknown Camera Controller Type") return nullptr;
        case CameraControllerType::Orthographic: return CreateRef<OrthographicCameraController>(aspectRatio);
        case CameraControllerType::Perspective: return CreateRef<PerspectiveCameraController>(aspectRatio);
        default: RK_CORE_ASSET(false, "Unknown Camera Controller Type") return nullptr;
        }
    }
}