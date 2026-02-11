/*
 * This file manage the differences between several OS.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
                throw std::runtime_error("Crash");
                oss << "[WARNING] ";
                break;
            case LogLevel::NONE:
                oss << "[NONE] ";
                break;
            default:
                break;
            }

            oss << getCurrentTime() << " - ";
            (oss << ... << args);
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
