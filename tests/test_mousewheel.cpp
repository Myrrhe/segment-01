#include "Constant.hpp"
#include "MouseWheel.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("MouseWheel", "[mousewheel]")
{
    segment01::MouseWheel::initialize();
    REQUIRE(segment01::MouseWheel::getDeltaWheel() == 0);
    segment01::MouseWheel::setDeltaWheel(1);
    REQUIRE_THAT(
        segment01::MouseWheel::getDeltaWheel(),
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
}
