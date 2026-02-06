#include <catch2/catch_test_macros.hpp>
#include "Func.hpp"

// TEST_CASE("Colors", "[colors]") {
//     REQUIRE(segment01::Func::colorBalance(sf::Color(0, 0, 0, 255), sf::Color(255, 255, 255, 255), 0.5) == sf::Color(127, 127, 127, 255));
// }

TEST_CASE("Sanity", "[sanity]") {
    REQUIRE(2 + 2 == 4);
}
