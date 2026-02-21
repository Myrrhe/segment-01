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

#ifndef TEXTCOMP_HPP
#define TEXTCOMP_HPP

#include "text/ChainText.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>

namespace segment01
{

class TextComp final : public sf::Drawable, public sf::Transformable
{
public:
    TextComp();
    TextComp(const std::vector<const ChainText *> &chainText,
             const sf::Font &font, const uint32_t characterSize);
    TextComp(const TextComp &right);
    TextComp &operator=(const TextComp &rhs);
    ~TextComp() override;

    void setFont(const sf::Font &font);

    void setCharacterSize(const uint32_t size);

    void setLineSpacing(const float32_t spacingFactor);

    void setLetterSpacing(bool spacingFixed, float32_t spacing);

    void setStyle(const InfoText::Style style);

    void setFillColor(const sf::Color &color);

    void setOutlineColor(const sf::Color &color);

    void setOutlineThickness(const float32_t thickness);

    void setWidthWrap(const float32_t widthWrap);

    const std::vector<const ChainText *> &getChainText() const;

    const sf::Font *getFont() const;

    uint64_t getCharacterSize() const;

    const std::tuple<bool, float32_t> &getLetterSpacing() const;

    float32_t getLineSpacing() const;

    InfoText::Style getStyle() const;

    const sf::Color &getFillColor() const;

    const sf::Color &getOutlineColor() const;

    float32_t getOutlineThickness() const;

    float32_t getWidthWrap() const;

    sf::Vector2<float32_t> findCharacterPos(std::size_t index) const;

    sf::Rect<float32_t> getLocalBounds() const;

    sf::Rect<float32_t> getGlobalBounds() const;

    void setGeometryNeedUpdate();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void ensureGeometryUpdate() const;

    static void addLine(std::vector<sf::Vertex> &vertices,
                        const float32_t lineLength, const float32_t lineTop,
                        const sf::Color &color, const float32_t offset,
                        const float32_t thickness,
                        const float32_t outlineThickness);
    static void addLinePart(std::vector<sf::Vertex> &vertices,
                            const float32_t xInit, const float32_t xFina,
                            const float32_t lineTop, const sf::Color &color,
                            const float32_t offset, const float32_t thickness,
                            const float32_t outlineThickness);
    static void addGlyphQuad(std::vector<sf::Vertex> &vertices,
                             const sf::Vector2<float32_t> position,
                             const sf::Color &color, const sf::Glyph &glyph,
                             const float32_t italicShear,
                             const float32_t outlineThickness);

    std::vector<const ChainText *> m_chainText;

    InfoText m_infoText;
    mutable std::vector<std::tuple<const sf::Font *, uint64_t>> m_fontsSizes;
    float32_t m_widthWrap;

    ///< Vertex array containing the fill geometry
    mutable std::vector<std::vector<sf::Vertex>> m_vertices;
    ///< Vertex array containing the outline geometry
    mutable std::vector<std::vector<sf::Vertex>> m_outlineVertices;
    ///< Bounding rectangle of the text (in local coordinates)
    mutable sf::Rect<float32_t> m_bounds;
    ///< Does the geometry need to be recomputed?
    mutable bool m_geometryNeedUpdate;
    ///< The font texture id
    mutable uint64_t m_fontTextureId;
};

} // namespace segment01

#endif // TEXTCOMP_HPP
