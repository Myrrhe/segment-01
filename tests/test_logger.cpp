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

#include "Logger.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Logger", "[logger]")
{
    std::ostringstream oss;
    auto logger = segment01::Logger(oss);
    REQUIRE(segment01::Logger::getLevel() == segment01::LogLevel::INFO);
    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    REQUIRE(segment01::Logger::getLevel() == segment01::LogLevel::NONE);
    static_cast<void>(
        logger.logging(segment01::LogLevel::INFO, "This is an info message"));
    REQUIRE(oss.str().empty());
    segment01::Logger::setLevel(segment01::LogLevel::INFO);

    static_cast<void>(
        logger.logging(segment01::LogLevel::ERRORS, "test1"));
    REQUIRE(oss.str().substr(oss.str().size() - 6) == "test1\n");
    static_cast<void>(
        logger.logging(segment01::LogLevel::WARNING, "test2"));
    REQUIRE(oss.str().substr(oss.str().size() - 6) == "test2\n");
    static_cast<void>(
        logger.logging(segment01::LogLevel::NONE, "test3"));
    REQUIRE(oss.str().substr(oss.str().size() - 6) == "test3\n");
    static_cast<void>(
        logger.info("test4"));
    REQUIRE(oss.str().substr(oss.str().size() - 6) == "test4\n");

    const auto logger2 = segment01::Logger();
}
