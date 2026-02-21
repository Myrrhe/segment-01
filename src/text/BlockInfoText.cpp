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

#include "text/BlockInfoText.hpp"
#include "Constant.hpp"
#include "Func.hpp"

namespace segment01
{

BlockInfoText::BlockInfoText() : NodeText(), infoText(), useInfo()
{
    // ctor
}

BlockInfoText::~BlockInfoText() = default;

BlockInfoText::BlockInfoText(const BlockInfoText &other) = default;

BlockInfoText::BlockInfoText(const InfoText &newInfoText)
    : NodeText(), infoText(newInfoText), useInfo()
{
    useInfo.fill(true);
}

BlockInfoText::BlockInfoText(const std::u32string &str)
    : NodeText(), infoText(), useInfo()
{
    infoText = InfoText(str);
    useInfo.fill(false);
    std::vector<std::u32string> vecStr = Func::split(str, U',');
    const std::size_t vecStrSize = vecStr.size();
    for (std::size_t i = 0; i < vecStrSize; ++i)
    {
        const auto [key, _val] = Func::getKeyValueLine(vecStr[i]);
        for (std::size_t j = 1; j <= InfoText::NbInfo; ++j)
        {
            if (key == InfoText::Keys32[j])
            {
                useInfo[j] = true;
            }
        }
    }
}

BlockInfoText &BlockInfoText::operator=(const BlockInfoText &rhs) = default;

void BlockInfoText::release()
{
    // Nothing to do
}

NodeText::Type BlockInfoText::getType() const { return Type::BLOCKINFO; }

const sf::Font *BlockInfoText::getFont() const { return infoText.getFont(); }

uint64_t BlockInfoText::getCharSize() const { return infoText.getCharSize(); }

const std::tuple<bool, float32_t> &BlockInfoText::getLetterSpacing() const
{
    return infoText.getLetterSpacing();
}

float32_t BlockInfoText::getLineSpacingFactor() const
{
    return infoText.getLineSpacingFactor();
}

InfoText::Style BlockInfoText::getStyle() const { return infoText.getStyle(); }

sf::Color BlockInfoText::getFillColor() const
{
    return infoText.getFillColor();
}

sf::Color BlockInfoText::getOutlineColor() const
{
    return infoText.getOutlineColor();
}

float32_t BlockInfoText::getThickness() const
{
    return infoText.getThickness();
}

bool BlockInfoText::isUsed(const uint64_t i) const { return useInfo[i]; }

bool BlockInfoText::isUsed(const InfoText::Info info) const
{
    return useInfo[static_cast<std::size_t>(info)];
}

void BlockInfoText::setUsed(const InfoText::Info info, const bool newUsed)
{
    useInfo[static_cast<std::size_t>(info)] = newUsed;
}

const InfoText &BlockInfoText::getInfoText() const { return infoText; }

bool BlockInfoText::isUseful() const
{
    bool useful = false;
    for (InfoText::Info i = InfoText::Info::INFO_BEGIN;
         i < InfoText::Info::NB_INFO; ++i)
    {
        useful = useful || isUsed(i);
    }
    return useful;
}

bool BlockInfoText::isEqual(const NodeText &right) const
{
    bool res = false;
    if (getType() == right.getType())
    {
        const auto *const rightP = dynamic_cast<const BlockInfoText *>(&right);
        res = infoText == rightP->infoText;
        for (uint64_t i = 0; i < InfoText::NbInfo; ++i)
        {
            res = res && (useInfo[i] == rightP->useInfo[i]);
        }
    }
    return res;
}

BlockInfoText &BlockInfoText::operator+=(const BlockInfoText &right)
{
    if (right.isUsed(InfoText::Info::FONT))
    {
        infoText.setInfo<InfoText::Info::FONT>(
            right.getInfoText().getInfo<InfoText::Info::FONT>());
        setUsed(InfoText::Info::FONT, true);
    }
    if (right.isUsed(InfoText::Info::CHAR_SIZE))
    {
        infoText.setInfo<InfoText::Info::CHAR_SIZE>(
            right.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        setUsed(InfoText::Info::CHAR_SIZE, true);
    }
    if (right.isUsed(InfoText::Info::LETTER_SPACING))
    {
        infoText.setInfo<InfoText::Info::LETTER_SPACING>(
            right.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        setUsed(InfoText::Info::LETTER_SPACING, true);
    }
    if (right.isUsed(InfoText::Info::LINE_SPACING_FACTOR))
    {
        infoText.setInfo<InfoText::Info::LINE_SPACING_FACTOR>(
            right.getInfoText().getInfo<InfoText::Info::LINE_SPACING_FACTOR>());
        setUsed(InfoText::Info::LINE_SPACING_FACTOR, true);
    }
    if (right.isUsed(InfoText::Info::STYLE))
    {
        infoText.setInfo<InfoText::Info::STYLE>(
            right.getInfoText().getInfo<InfoText::Info::STYLE>());
        setUsed(InfoText::Info::STYLE, true);
    }
    if (right.isUsed(InfoText::Info::FILL_COLOR))
    {
        infoText.setInfo<InfoText::Info::FILL_COLOR>(
            right.getInfoText().getInfo<InfoText::Info::FILL_COLOR>());
        setUsed(InfoText::Info::FILL_COLOR, true);
    }
    if (right.isUsed(InfoText::Info::OUTLINE_COLOR))
    {
        infoText.setInfo<InfoText::Info::OUTLINE_COLOR>(
            right.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>());
        setUsed(InfoText::Info::OUTLINE_COLOR, true);
    }
    if (right.isUsed(InfoText::Info::THICKNESS))
    {
        infoText.setInfo<InfoText::Info::THICKNESS>(
            right.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        setUsed(InfoText::Info::THICKNESS, true);
    }
    return *this;
}

const std::u32string &BlockInfoText::getStr() const
{
    return Constant::EmptyStr32;
}

std::u32string BlockInfoText::toStr() const
{
    std::u32string res = U"";
    if (isUseful())
    {
        res = U"<";
        for (InfoText::Info i = InfoText::Info::INFO_BEGIN;
             i < InfoText::Info::NB_INFO; ++i)
        {
            if (isUsed(i))
            {
                if (res != U"<")
                {
                    res += InfoText::Separator;
                }
                res += InfoText::getKeyStr32(i) + U"=" + infoText.getValStr(i);
            }
        }
        res += U'>';
    }
    return res;
}

} // namespace segment01
