#include "OsManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Osmanager", "[osmanager]")
{
    static_cast<void>(segment01::OsManager::getMonitorSize());
    static_cast<void>(segment01::OsManager::getWallpaperStyle());
    segment01::OsManager::setProcessDPIAware();
}
