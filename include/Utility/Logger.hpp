#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <format>
#include <ostream>
#include <string>

namespace Utility
{
    class Logger
    {
    private:
        std::ostream& output_stream;
        static constexpr std::string_view INFO = "[INFO]";

    public:
        Logger(std::ostream& output_stream);

        template<typename... Args>
        void info(std::format_string<Args...> fmt, Args&&... args )
        {
            output_stream << INFO << " " << std::format(fmt, args...) << "\n";
        }
    };
}

#endif
