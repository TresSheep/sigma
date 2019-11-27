#pragma once

#include <string>

namespace Frontend
{
    namespace Driver
    {
        class Error
        {
        public:
            Error();
            Error(std::string message, uint32_t line);
            ~Error();

            std::string Message;
            uint32_t Line;
        };
    }
}