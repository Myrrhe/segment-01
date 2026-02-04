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

#include "Logger.hpp"

namespace segment01
{
Logger::Logger() : m_mtx(std::mutex()), m_output(std::cout) {}
Logger::Logger(std::ostream& out) : m_mtx(std::mutex()), m_output(out) {}

std::string Logger::getCurrentTime() const
{
    std::ostringstream oss;
    // Utilisation de localtime_s (Windows)
    const std::time_t now = std::time(nullptr);
    if (std::tm localTime; 0 == ::localtime_s(&localTime, &now))
    {
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    }
    return oss.str();
}

Logger::~Logger() = default;

} // namespace segment01
