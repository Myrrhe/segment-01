#include "WindowManager.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Windowmanager", "[windowmanager]")
{
    segment01::WindowManager::getMonitorSize();
    REQUIRE(segment01::WindowManager::getRenderWindow() == nullptr);
    segment01::WindowManager::setUiView(0, 0, 200, 200);
    segment01::WindowManager::setOffsetX(0);
    segment01::WindowManager::setOffsetY(0);
    REQUIRE(!segment01::WindowManager::isTextEntered());
    REQUIRE(!segment01::WindowManager::isKeyPressed());
    REQUIRE(!segment01::WindowManager::isAltEntered());
    REQUIRE(!segment01::WindowManager::isControlEntered());
    REQUIRE(!segment01::WindowManager::isShiftEntered());
    REQUIRE(!segment01::WindowManager::isSystemEntered());

    auto renderTexture = sf::RenderTexture(sf::Vector2<uint32_t>(600, 600));

    segment01::WindowManager::pushStateView(
        segment01::WindowManager::IdView::MAIN);
    segment01::WindowManager::setViewTarget(renderTexture);
    segment01::WindowManager::popStateView();

    segment01::WindowManager::pushStateView(
        segment01::WindowManager::IdView::UI);
    segment01::WindowManager::setViewTarget(renderTexture);
    segment01::WindowManager::popStateView();

    segment01::WindowManager::pushStateView(
        segment01::WindowManager::IdView::SHAKE);
    segment01::WindowManager::setViewTarget(renderTexture);
    segment01::WindowManager::popStateView();

    segment01::WindowManager::pushStateView(
        segment01::WindowManager::IdView::WHOLE);
    segment01::WindowManager::setViewTarget(renderTexture);
    segment01::WindowManager::popStateView();

    REQUIRE(segment01::WindowManager::getCharEntered() == 0);
    REQUIRE(segment01::WindowManager::getKeyPressed() == sf::Keyboard::Key::A);
}
