#pragma once
#include "GERender/Buffer.h"

namespace Rocket
{
    template <typename T>
    class OpenGLInstanceBuffer : implements InstanceBuffer<T>
    {
    public:
        OpenGLInstanceBuffer(T *data, uint32_t count);

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
} // namespace Rocket