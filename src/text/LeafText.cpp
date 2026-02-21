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

#include "text/LeafText.hpp"

namespace segment01
{

LeafText::LeafText() : NodeText(), str(U"")
{
    // ctor
}

LeafText::~LeafText() = default;

LeafText::LeafText(const LeafText &other) = default;

LeafText::LeafText(const std::u32string &newStr) : NodeText(), str(newStr) {}

LeafText &LeafText::operator=(const LeafText &rhs) = default;

void LeafText::release()
{
    // Nothing to do
}

NodeText::Type LeafText::getType() const { return Type::LEAF; }

bool LeafText::isEmpty() const { return str.empty(); }

const std::u32string &LeafText::getStr() const { return str; }

std::size_t LeafText::getSize() const { return str.size(); }

bool LeafText::isEqual(const NodeText &right) const
{
    bool res = false;
    if (getType() == right.getType())
    {
        res = str == dynamic_cast<const LeafText *>(&right)->str;
    }
    return res;
}

std::u32string LeafText::toStr() const { return str; }

} // namespace segment01
