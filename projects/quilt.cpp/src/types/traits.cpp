/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/quilt.cpp/types/traits.hpp"

namespace dogen {
namespace quilt {
namespace cpp {

std::string traits::family() {
    static std::string r("quilt");
    return r;
}

std::string traits::kernel() {
    static std::string r("quilt.cpp");
    return r;
}

std::string traits::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::supported() {
    static std::string r("supported");
    return r;
}

std::string traits::overwrite() {
    static std::string r("overwrite");
    return r;
}

std::string traits::directory() {
    static std::string r("directory");
    return r;
}

std::string traits::postfix() {
    static std::string r("postfix");
    return r;
}

std::string traits::file_path() {
    static std::string r("file_path");
    return r;
}

std::string traits::header_guard() {
    static std::string r("header_guard");
    return r;
}

std::string traits::inclusion_required() {
    static std::string r("inclusion_required");
    return r;
}

std::string traits::primary_inclusion_directive() {
    static std::string r("primary_inclusion_directive");
    return r;
}

std::string traits::secondary_inclusion_directive() {
    static std::string r("secondary_inclusion_directive");
    return r;
}

std::string traits::inclusion_dependency() {
    static std::string r("inclusion_dependency");
    return r;
}

std::string traits::cpp::formatting_style() {
    static std::string r("formatting_style");
    return r;
}

std::string traits::cpp::formatting_input() {
    static std::string r("formatting_input");
    return r;
}

std::string traits::cpp::inclusion_required() {
    static std::string r("quilt.cpp.inclusion_required");
    return r;
}

std::string traits::cpp::header_file_extension() {
    static std::string r("quilt.cpp.header_file_extension");
    return r;
}

std::string traits::cpp::implementation_file_extension() {
    static std::string r("quilt.cpp.implementation_file_extension");
    return r;
}

std::string traits::cpp::include_directory_name() {
    static std::string r("quilt.cpp.include_directory_name");
    return r;
}

std::string traits::cpp::source_directory_name() {
    static std::string r("quilt.cpp.source_directory_name");
    return r;
}

std::string traits::cpp::kernel_directory_name() {
    static std::string r("quilt.cpp.directory");
    return r;
}

std::string traits::cpp::disable_facet_directories() {
    static std::string r("quilt.cpp.disable_facet_directories");
    return r;
}

std::string traits::cpp::helper::family() {
    static std::string r("quilt.cpp.helper.family");
    return r;
}

std::string traits::cpp::streaming::string_conversion_method() {
    static std::string r("quilt.cpp.streaming.string_conversion_method");
    return r;
}

std::string traits::cpp::streaming::requires_quoting() {
    static std::string r("quilt.cpp.streaming.requires_quoting");
    return r;
}

std::string traits::cpp::streaming::remove_unprintable_characters() {
    static std::string r("quilt.cpp.streaming.remove_unprintable_characters");
    return r;
}

std::string traits::cpp::streaming::requires_dereferencing() {
    static std::string r("quilt.cpp.streaming.requires_dereferencing");
    return r;
}

std::string traits::cpp::aspect::disable_complete_constructor() {
    static std::string r("quilt.cpp.aspect.disable_complete_constructor");
    return r;
}

std::string traits::cpp::aspect::disable_xml_serialization() {
    static std::string r("quilt.cpp.aspect.disable_xml_serialization");
    return r;
}

std::string traits::cpp::aspect::requires_manual_default_constructor() {
    static std::string r(
        "quilt.cpp.aspect.requires_manual_default_constructor");
    return r;
}

std::string traits::cpp::aspect::requires_manual_move_constructor() {
    static std::string r("quilt.cpp.aspect.requires_manual_move_constructor");
    return r;
}

std::string traits::cpp::aspect::requires_stream_manipulators() {
    static std::string r("quilt.cpp.aspect.requires_stream_manipulators");
    return r;
}

} } }
