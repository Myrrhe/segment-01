////////////////////////////////////////////////////////////
// A basic function library.
// Copyright (C) 2026  Myrrhe <email>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace segment01
{
enum class LogLevel : uint64_t
{
    INFO,
    ERRORS,
    WARNING,
    NONE,
};

template <typename T, typename = void>
struct IsOstreamInsertable : public std::false_type {};

template <typename T>
struct IsOstreamInsertable<
    T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>
> : public std::true_type {};

template <typename T>
inline constexpr bool is_ostream_insertable_v =
    IsOstreamInsertable<T>::value;

template <typename T>
void appendToStream(std::ostringstream& oss, const T& value)
{
    static constexpr char32_t twoPowerSevenMinusOne = 0x7F;
    if constexpr (is_ostream_insertable_v<T>)
    {
        oss << value;
    }
    else if constexpr (std::is_same_v<T, std::u32string>)
    {
        // Conversion UTF-32 → UTF-8
        std::string converted;
        for (char32_t c : value)
        {
            if (c <= twoPowerSevenMinusOne)
            {
                converted += static_cast<char>(c);
            }
            else
            {
                // fallback
                converted += '?';
            }
        }
        oss << converted;
    }
    else
    {
        oss << "[UNSUPPORTED_TYPE]";
    }
}

class Logger final
{
public:
    Logger();
    explicit Logger(std::ostream &out);
    ~Logger();

    template <typename... Args> Logger &info(const Args &...args)
    {
        return logging(LogLevel::INFO, args...);
    }

    template <typename... Args>
    Logger &logging(const LogLevel level, const Args &...args)
    {
        if (level >= s_level.load(std::memory_order_relaxed))
        {
            const std::scoped_lock lock(m_mtx);
            std::ostringstream oss;

            switch (level)
            {
            case LogLevel::INFO:
                oss << "[INFO] ";
                break;
            case LogLevel::ERRORS:
                oss << "[ERRORS] ";
                break;
            case LogLevel::WARNING:
                oss << "[WARNING] ";
                break;
            case LogLevel::NONE:
                oss << "[NONE] ";
                break;
            default:
                break;
            }

            oss << getCurrentTime() << " - ";
            // (oss << ... << args);
            (appendToStream(oss, args), ...);
            m_output << oss.str() << '\n';
        }
        return *this;
    }

    static void setLevel(const LogLevel level);
    static LogLevel getLevel();

private:
    std::mutex m_mtx;
    std::ostream &m_output;

    static std::atomic<LogLevel> s_level;

    std::string getCurrentTime() const;
};

} // namespace segment01

#endif // LOGGER_HPP
