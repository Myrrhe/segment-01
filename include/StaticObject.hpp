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

#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP

namespace segment01
{
////////////////////////////////////////////////////////////
/// \brief Mother class for static classes
///
////////////////////////////////////////////////////////////
class StaticObject
{
public:
    StaticObject() = delete;
    StaticObject(const StaticObject &rhs) = delete;
    StaticObject(StaticObject &&rhs) = delete;
    StaticObject &operator=(const StaticObject &rhs) = delete;
    StaticObject &operator=(StaticObject &&rhs) = delete;
    ~StaticObject() = delete;
};

} // namespace segment01

#endif // STATICOBJECT_HPP
