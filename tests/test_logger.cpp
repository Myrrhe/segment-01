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
    // REQUIRE(oss.str().empty());
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
