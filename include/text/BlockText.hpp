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

#ifndef BLOCKTEXT_HPP
#define BLOCKTEXT_HPP
#include "text/InfoText.hpp"
#include "text/NodeText.hpp"
#include <vector>

namespace segment01
{

class BlockText final : public NodeText
{
public:
    /// Default constructor
    BlockText();
    /// Copy constructor
    /// \param other Object to copy from
    explicit BlockText(const std::u32string_view &str);
    BlockText(const BlockText &other);
    /// Assignment operator
    /// \param rhs Object to assign from
    /// \return A reference to this
    BlockText &operator=(const BlockText &rhs);
    /// Default destructor
    ~BlockText() override;

    void release() override;

    Type getType() const override;

    const std::u32string &getStr() const override;

    bool isEqual(const NodeText &right) const override;

    std::u32string toStr() const override;

private:
    InfoText infoText;
    std::vector<NodeText *> blocks;

    friend bool operator==(const BlockText &left, const BlockText &right)
    {
        bool res = false;
        if (left.getType() == right.getType())
        {
            res = left.infoText == right.infoText;
            const std::size_t blocksSize = left.blocks.size();
            for (std::size_t i = 0; i < blocksSize; ++i)
            {
                res = res && (*const_cast<const NodeText *>(left.blocks[i]))
                                 .isEqual(right);
            }
        }
        return res;
    }
    friend bool operator!=(const BlockText &left, const BlockText &right)
    {
        return !(left == right);
    }
};

} // namespace segment01

#endif // BLOCKTEXT_HPP
