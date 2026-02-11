#include "Constant.hpp"
#include "Quaternion.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Quaternion", "[quaternion]")
{
    REQUIRE_THAT(
        segment01::Quaternion(std::complex<segment01::float64_t>(1.0, 2.0),
                              std::complex<segment01::float64_t>(3.0, 4.0))
            .y,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).y,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(segment01::Quaternion(1.0, 2.0, 3.0, 4.0)).y,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    auto q1 = segment01::Quaternion(1.0, 2.0, 3.0, 4.0);
    q1 = segment01::Quaternion(2.0, 3.0, 4.0, 5.0);
    REQUIRE_THAT(
        q1.x,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)[0],
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)[1],
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)[2],
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)[3],
        Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    const auto q2 = segment01::Quaternion(1.0, 2.0, 3.0, 4.0);
    REQUIRE_THAT(
        q2[0],
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q2[1],
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q2[2],
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q2[3],
        Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (+segment01::Quaternion(1.0, 2.0, 3.0, 4.0)).y,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (-segment01::Quaternion(1.0, 2.0, 3.0, 4.0)).y,
        Catch::Matchers::WithinAbs(-2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)++.x,
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (++segment01::Quaternion(1.0, 2.0, 3.0, 4.0)).x,
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0)--.x,
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (--segment01::Quaternion(1.0, 2.0, 3.0, 4.0)).x,
        Catch::Matchers::WithinAbs(0.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) +=
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) -=
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) *=
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .x,
        Catch::Matchers::WithinAbs(-8.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) /=
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(0.5, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getNormSquare(),
        Catch::Matchers::WithinAbs(30.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(2.0, 2.0, 2.0, 2.0).getNorm(),
        Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getConjugation().y,
        Catch::Matchers::WithinAbs(-2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getReciprocal().z,
        Catch::Matchers::WithinAbs(-0.1, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(2.0, 2.0, 2.0, 2.0).setNorm(8.0).x,
        Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).conjugate().y,
        Catch::Matchers::WithinAbs(-2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).reciproc().z,
        Catch::Matchers::WithinAbs(-0.1, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getX(),
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getY(),
        Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getZ(),
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getT(),
        Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getXY().real(),
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        segment01::Quaternion(1.0, 2.0, 3.0, 4.0).getZT().real(),
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    auto q = segment01::Quaternion(1.0, 2.0, 3.0, 4.0);
    q.setX(2.0);
    q.setY(3.0);
    q.setZ(4.0);
    q.setT(5.0);
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(2.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(4.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(5.0, segment01::Constant::m_epsilon));
    q.setXY(6.0, 7.0);
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(6.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(7.0, segment01::Constant::m_epsilon));
    q.setXY(std::complex<segment01::float64_t>(8.0, 9.0));
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(8.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(9.0, segment01::Constant::m_epsilon));
    q.setZT(10.0, 11.0);
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(10.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(11.0, segment01::Constant::m_epsilon));
    q.setZT(std::complex<segment01::float64_t>(12.0, 13.0));
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(12.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(13.0, segment01::Constant::m_epsilon));
    q.setXYZT(14.0, 15.0, 16.0, 17.0);
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(14.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(15.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(16.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(17.0, segment01::Constant::m_epsilon));
    q.setXYZT(std::complex<segment01::float64_t>(18.0, 19.0),
              std::complex<segment01::float64_t>(20.0, 21.0));
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(18.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(19.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(20.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(21.0, segment01::Constant::m_epsilon));
    q.setXYZT(segment01::Quaternion(22.0, 23.0, 24.0, 25.0));
    REQUIRE_THAT(
        q.x, Catch::Matchers::WithinAbs(22.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.y, Catch::Matchers::WithinAbs(23.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.z, Catch::Matchers::WithinAbs(24.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        q.t, Catch::Matchers::WithinAbs(25.0, segment01::Constant::m_epsilon));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) ==
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) !=
            segment01::Quaternion(1.0, 2.0, 3.0, 5.0));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) !=
            segment01::Quaternion(1.0, 2.0, 4.0, 4.0));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) !=
            segment01::Quaternion(1.0, 3.0, 3.0, 4.0));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) !=
            segment01::Quaternion(2.0, 2.0, 3.0, 4.0));
    REQUIRE(segment01::Quaternion(2.0, 3.0, 4.0, 5.0) >
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0));
    REQUIRE(!(segment01::Quaternion(2.0, 3.0, 4.0, 4.0) >
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(2.0, 3.0, 3.0, 5.0) >
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(2.0, 2.0, 4.0, 4.0) >
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 3.0, 4.0, 4.0) >
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(segment01::Quaternion(0.0, 1.0, 2.0, 3.0) <
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0));
    REQUIRE(!(segment01::Quaternion(1.0, 1.0, 2.0, 3.0) <
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(0.0, 2.0, 2.0, 3.0) <
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(0.0, 1.0, 3.0, 3.0) <
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(0.0, 1.0, 2.0, 4.0) <
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) >=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0));
    REQUIRE(!(segment01::Quaternion(0.0, 2.0, 3.0, 4.0) >=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 1.0, 3.0, 4.0) >=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 2.0, 2.0, 4.0) >=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 2.0, 3.0, 3.0) >=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(segment01::Quaternion(1.0, 2.0, 3.0, 4.0) <=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0));
    REQUIRE(!(segment01::Quaternion(2.0, 2.0, 3.0, 4.0) <=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 3.0, 3.0, 4.0) <=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 2.0, 4.0, 4.0) <=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE(!(segment01::Quaternion(1.0, 2.0, 3.0, 5.0) <=
            segment01::Quaternion(1.0, 2.0, 3.0, 4.0)));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) +
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(3.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) -
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(1.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) *
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .x,
        Catch::Matchers::WithinAbs(-8.0, segment01::Constant::m_epsilon));
    REQUIRE_THAT(
        (segment01::Quaternion(1.0, 2.0, 3.0, 4.0) /
         segment01::Quaternion(1.0, 1.0, 1.0, 1.0))
            .y,
        Catch::Matchers::WithinAbs(0.5, segment01::Constant::m_epsilon));
}
