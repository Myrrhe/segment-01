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

#ifndef BLOCKCLOSINGTEXT_HPP
#define BLOCKCLOSINGTEXT_HPP
#include "text/NodeText.hpp"

namespace segment01
{

class BlockClosingText final : public NodeText
{
public:
    /// Default constructor
    BlockClosingText();
    /// Copy constructor
    /// \param other Object to copy from
    BlockClosingText(const BlockClosingText &other);
    /// Assignment operator
    /// \param rhs Object to assign from
    /// \return A reference to this
    BlockClosingText &operator=(const BlockClosingText &rhs);
    /// Default destructor
    ~BlockClosingText() override;

    void release() override;

    Type getType() const override;

    const std::u32string &getStr() const override;

    bool isEqual(const NodeText &right) const override;

    std::u32string toStr() const override;

private:
    friend bool operator==(const BlockClosingText &left,
                           const BlockClosingText &right)
    {
        return left.getType() == right.getType();
    }
    friend bool operator!=(const BlockClosingText &left,
                           const BlockClosingText &right)
    {
        return !(left == right);
    }
};

} // namespace segment01

#endif // BLOCKCLOSINGTEXT_HPP
