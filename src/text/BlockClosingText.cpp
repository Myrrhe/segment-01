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

#include "text/BlockClosingText.hpp"
#include "Constant.hpp"

namespace segment01
{

BlockClosingText::BlockClosingText() : NodeText()
{
    // ctor
}

BlockClosingText::~BlockClosingText() = default;

BlockClosingText::BlockClosingText(const BlockClosingText &other) = default;

BlockClosingText &
BlockClosingText::operator=(const BlockClosingText &rhs) = default;

void BlockClosingText::release()
{
    // Nothing to do
}

NodeText::Type BlockClosingText::getType() const { return Type::BLOCKCLOSING; }

bool BlockClosingText::isEqual(const NodeText &right) const
{
    return getType() == right.getType();
}

const std::u32string &BlockClosingText::getStr() const
{
    return Constant::EmptyStr32;
}

std::u32string BlockClosingText::toStr() const { return U"</>"; }

} // namespace segment01
