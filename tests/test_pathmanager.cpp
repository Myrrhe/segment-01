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

#include "Func.hpp"
#include "Logger.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("PathManager", "[pathmanager]")
{
    segment01::Logger::setLevel(segment01::LogLevel::NONE);
    segment01::PathManager::read();
    segment01::PathManager::setPath(segment01::Func::str16Tostr8(
        segment01::OsManager::getExecutablePath()));
    segment01::Logger::setLevel(segment01::LogLevel::INFO);

    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::ROOT));
    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::DAT));
    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::IMG));
    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::SHADER));
    static_cast<void>(segment01::PathManager::getPath(
        segment01::PathManager::Dir::SHADER_FRAG));
    static_cast<void>(segment01::PathManager::getPath(
        segment01::PathManager::Dir::SHADER_VERT));
    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::SOUND));
    static_cast<void>(
        segment01::PathManager::getPath(segment01::PathManager::Dir::FONT));
    static_cast<void>(segment01::PathManager::getPath(
        segment01::PathManager::Dir::SCREENSHOT));
}
