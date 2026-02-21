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

#ifndef BLOCKINFOTEXT_HPP
#define BLOCKINFOTEXT_HPP
#include "text/InfoText.hpp"
#include "text/NodeText.hpp"
#include <array>

namespace segment01
{

class BlockInfoText final : public NodeText
{
public:
    /// Default constructor
    BlockInfoText();
    /// Copy constructor
    /// \param other Object to copy from
    BlockInfoText(const BlockInfoText &other);
    explicit BlockInfoText(const InfoText &newInfoText);
    explicit BlockInfoText(const std::u32string &str);
    /// Assignment operator
    /// \param rhs Object to assign from
    /// \return A reference to this
    BlockInfoText &operator=(const BlockInfoText &rhs);
    /// Default destructor
    ~BlockInfoText() override;

    void release() override;

    Type getType() const override;

    const sf::Font *getFont() const;
    uint64_t getCharSize() const;
    const std::tuple<bool, float32_t> &getLetterSpacing() const;
    float32_t getLineSpacingFactor() const;
    InfoText::Style getStyle() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    float32_t getThickness() const;

    [[nodiscard]] bool isUsed(const uint64_t i) const;
    [[nodiscard]] bool isUsed(const InfoText::Info info) const;
    bool isUseful() const;

    [[nodiscard]] const InfoText &getInfoText() const;

    const std::u32string &getStr() const override;

    bool isEqual(const NodeText &right) const override;

    BlockInfoText &operator+=(const BlockInfoText &right);

    std::u32string toStr() const override;

private:
    void setUsed(const InfoText::Info info, const bool newUsed);

    InfoText infoText;
    std::array<bool, 8> useInfo;

    friend BlockInfoText operator+(const BlockInfoText &left,
                                   const BlockInfoText &right)
    {
        return BlockInfoText(left) += right;
    }

    friend bool operator==(const BlockInfoText &left,
                           const BlockInfoText &right)
    {
        bool res = false;
        if (left.getType() == right.getType())
        {
            res = left.infoText == right.infoText;
            for (uint64_t i = 0; i < InfoText::NbInfo; ++i)
            {
                res = res && (left.useInfo[i] == right.useInfo[i]);
            }
        }
        return res;
    }
    friend bool operator!=(const BlockInfoText &left,
                           const BlockInfoText &right)
    {
        return !(left == right);
    }
};

} // namespace segment01

#endif // BLOCKINFOTEXT_HPP
