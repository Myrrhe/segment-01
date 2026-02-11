#include "Func.hpp"
#include "Logger.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Func", "[func]")
{
    REQUIRE(segment01::Func::printVideoMode(sf::VideoMode({800, 600}, 32)) ==
            "(800 px, 600 px, 32 bpp)");

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 200;
    bmi.bmiHeader.biHeight = 200;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void *bits = nullptr;
    const HDC hdc = ::GetDC(nullptr);
    const HBITMAP hBitmap =
        ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    static_cast<void>(::ReleaseDC(nullptr, hdc));
    // BGRA
    auto *const pixels = static_cast<uint8_t *const>(bits);
    pixels[0] = 0x00; // B
    pixels[1] = 0x00; // G
    pixels[2] = 0xFF; // R
    pixels[3] = 0xFF; // A
    const sf::Image image = segment01::Func::hBITMAPToImage(hBitmap);
    REQUIRE(image.getSize() == sf::Vector2<uint32_t>(200, 200));

    REQUIRE(segment01::Func::colorBalance(sf::Color(0, 0, 0, 255),
                                          sf::Color(255, 255, 255, 255), 0.5) ==
            sf::Color(127, 127, 127, 255));
    REQUIRE(segment01::Func::colorDistanceSquared(
                sf::Color(0, 0, 0, 255), sf::Color(255, 255, 255, 255)) ==
            195'075);

    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    REQUIRE(segment01::Func::getDir("error").size() == 0);
    segment01::Logger::setLevel(segment01::LogLevel::INFO);
    REQUIRE(segment01::Func::getDir(".").size() > 0);
    const std::vector<std::string> dirContent = segment01::Func::getDir(".");
    for (std::size_t i = 0; i < dirContent.size(); ++i)
    {
        std::cout << dirContent[i] << std::endl;
    }
    // REQUIRE(segment01::Func::fileExist("tests.exe"));

    REQUIRE(segment01::Func::getKeyWordLine("error") == "");
    REQUIRE(segment01::Func::getKeyWordLine("key=value") == "key");
    REQUIRE(segment01::Func::getKeyWordLine(U"error") == U"");
    REQUIRE(segment01::Func::getKeyWordLine(U"key=value") == U"key");

    const std::array<std::string, 3> fontExtensions = {
        {".ttf", ".otf", ".woff"}};
    REQUIRE(segment01::Func::hasSuffixInList("font.otf", fontExtensions.begin(),
                                             fontExtensions.end()));
    REQUIRE(!segment01::Func::hasSuffixInList(
        "font.woff2", fontExtensions.begin(), fontExtensions.end()));
}
