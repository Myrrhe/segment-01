#include "ScreenConnected.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Screenconnected", "[screenconnected]")
{
    segment01::ScreenConnected::initialize();
    auto screen1 = segment01::ScreenConnected();
    auto screen2 = segment01::ScreenConnected(
        L"test",
        sf::Rect<segment01::float32_t>(
            sf::Vector2<segment01::float32_t>(1, 2),
            sf::Vector2<segment01::float32_t>(10, 10)),
        60, sf::Vector2<uint32_t>(96, 96));
    REQUIRE(screen1.name.empty());
    REQUIRE(screen2.name == L"test");
    screen1 = screen2;
    REQUIRE(screen1.name == L"test");
    screen2 = std::move(screen1);
    REQUIRE(screen2.name == L"test");
    auto screen3 = segment01::ScreenConnected(screen2);
    auto screen4 = std::move(screen2);
    REQUIRE(screen3.name == L"test");
    REQUIRE(screen4.name == L"test");
    segment01::ScreenConnected::deleteAll();
}
