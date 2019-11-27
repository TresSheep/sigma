#include "Error.h"

namespace Frontend
{
    namespace Driver
    {
        Error::Error()
        {
        }

        Error::Error(std::string message, uint32_t line) :
            Message(message), Line(line)
        {
        }

        Error::~Error()
        {
        }
    }
}