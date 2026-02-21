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

#ifndef LEAFTEXT_HPP
#define LEAFTEXT_HPP
#include "text/NodeText.hpp"
#include <string>

namespace segment01
{

class LeafText final : public NodeText
{
public:
    /// Default constructor
    LeafText();
    /// Copy constructor
    /// \param other Object to copy from
    LeafText(const LeafText &other);
    explicit LeafText(const std::u32string &newStr);
    /// Assignment operator
    /// \param rhs Object to assign from
    /// \return A reference to this
    LeafText &operator=(const LeafText &rhs);
    /// Default destructor
    ~LeafText() override;

    void release() override;

    Type getType() const override;

    [[nodiscard]] bool isEmpty() const;

    const std::u32string &getStr() const override;

    [[nodiscard]] std::size_t getSize() const;

    bool isEqual(const NodeText &right) const override;

    std::u32string toStr() const override;

private:
    std::u32string str;

    friend bool operator==(const LeafText &left, const LeafText &right)
    {
        bool res = false;
        if (left.getType() == right.getType())
        {
            res = left.str == right.str;
        }
        return res;
    }

    friend bool operator!=(const LeafText &left, const LeafText &right)
    {
        return !(left == right);
    }
};

} // namespace segment01

#endif // LEAFTEXT_HPP
