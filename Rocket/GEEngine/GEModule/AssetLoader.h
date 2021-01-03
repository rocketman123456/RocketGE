#pragma once
#include "GECore/Core.h"
#include "GEInterface/IRuntimeModule.h"

namespace Rocket
{
    class Buffer
    {
    public:
        Buffer() = default;

        explicit Buffer(size_t size, size_t alignment = 4) : m_szSize(size) { m_pData = reinterpret_cast<uint8_t *>(new uint8_t[size]); }

        Buffer(const Buffer &rhs) = delete;

        Buffer(Buffer &&rhs) noexcept
        {
            m_pData = rhs.m_pData;
            m_szSize = rhs.m_szSize;
            rhs.m_pData = nullptr;
            rhs.m_szSize = 0;
        }

        Buffer &operator=(const Buffer &rhs) = delete;

        Buffer &operator=(Buffer &&rhs) noexcept
        {
            delete[] m_pData;
            m_pData = rhs.m_pData;
            m_szSize = rhs.m_szSize;
            rhs.m_pData = nullptr;
            rhs.m_szSize = 0;
            return *this;
        }

        ~Buffer()
        {
            if (m_pData != nullptr)
            {
                delete[] m_pData;
            }
        }

        [[nodiscard]] uint8_t *GetData() { return m_pData; };
        [[nodiscard]] const uint8_t *GetData() const { return m_pData; };
        [[nodiscard]] size_t GetDataSize() const { return m_szSize; };

        uint8_t *MoveData()
        {
            uint8_t *tmp = m_pData;
            m_pData = nullptr;
            m_szSize = 0;
            return tmp;
        }

        void SetData(uint8_t *data, size_t size)
        {
            if (m_pData != nullptr)
            {
                delete[] m_pData;
            }
            m_pData = data;
            m_szSize = size;
        }

    protected:
        uint8_t *m_pData{nullptr};
        size_t m_szSize{0};
    };

    // TODO : change all asset loading through this module
    class AssetLoader : implements IRuntimeModule
    {
    public:
        enum AssetOpenMode
        {
            MY_OPEN_TEXT = 0,   /// Open In Text Mode
            MY_OPEN_BINARY = 1, /// Open In Binary Mode
        };

        enum AssetSeekBase
        {
            MY_SEEK_SET = 0, /// SEEK_SET
            MY_SEEK_CUR = 1, /// SEEK_CUR
            MY_SEEK_END = 2  /// SEEK_END
        };

        typedef void *AssetFilePtr;

        ~AssetLoader() override = default;

        bool AddSearchPath(const char *path);
        bool RemoveSearchPath(const char *path);
        void ClearSearchPath();
        bool FileExists(const char *filePath);

        AssetFilePtr OpenFile(const char *name, AssetOpenMode mode);
        void CloseFile(AssetFilePtr &fp);
        size_t GetSize(const AssetFilePtr &fp);
        int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);

        virtual Buffer SyncOpenAndReadText(const char *filePath);
        virtual Buffer SyncOpenAndReadBinary(const char *filePath);
        virtual size_t SyncRead(const AssetFilePtr &fp, Buffer &buf);

        virtual int Initialize() override { return 0; }
        virtual void Finalize() override {}

        virtual int Tick(Timestep ts) override { return 0; }

        inline std::string SyncOpenAndReadTextFileToString(const char *fileName)
        {
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            if (buffer.GetDataSize())
            {
                char *content = reinterpret_cast<char *>(buffer.GetData());

                if (content)
                {
                    result = std::string(content);
                }
            }
            return result;
        }

    private:
        std::vector<std::string> m_strSearchPath;
    };
} // namespace Rocket