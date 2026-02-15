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
