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

#ifndef NODETEXT_HPP
#define NODETEXT_HPP
#include <cstdint>
#include <string>

namespace segment01
{

class NodeText
{
public:
    enum class Type : uint64_t
    {
        LEAF,
        BLOCK,
        BLOCKINFO,
        BLOCKCLOSING
    };

    /// Default constructor
    NodeText();
    /// Copy constructor
    ///  \param other Object to copy from
    NodeText(const NodeText &other);
    /// Assignment operator
    /// \param rhs Object to assign from
    /// \return A reference to this
    NodeText &operator=(const NodeText &rhs);
    /// Default destructor
    virtual ~NodeText();

    virtual void release() = 0;

    virtual Type getType() const = 0;

    virtual const std::u32string &getStr() const = 0;

    // virtual bool operator==(const NodeText &right) const = 0;
    // virtual bool operator!=(const NodeText &right) const = 0;

    virtual bool isEqual(const NodeText &right) const = 0;

    virtual std::u32string toStr() const = 0;
};

} // namespace segment01

#endif // NODETEXT_HPP
