#include "GERender/RenderCommand.h"

namespace Rocket
{
	Scope<RenderAPI> RenderCommand::s_RenderAPI = RenderAPI::Create();
}
