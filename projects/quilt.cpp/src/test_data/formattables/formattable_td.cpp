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
#include <sstream>
#include "dogen/quilt.cpp/test_data/formattables/enum_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/class_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/concept_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/origin_types_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/visitor_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/includers_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/primitive_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/registrar_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/cmakelists_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/odb_options_info_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/forward_declarations_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::formattables::origin_types
create_dogen_quilt_cpp_formattables_origin_types(const unsigned int position) {
    return dogen::quilt::cpp::formattables::origin_types_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void formattable_generator::
populate(const unsigned int position, result_type& v) {
    v.identity(create_std_string(position + 0));
    v.origin_type(create_dogen_quilt_cpp_formattables_origin_types(position + 1));
    v.id(create_std_string(position + 2));
}

formattable_generator::result_type*
formattable_generator::create_ptr(const unsigned int position) {
    if ((position % 9) == 0)
        return dogen::quilt::cpp::formattables::cmakelists_info_generator::create_ptr(position);
    if ((position % 9) == 1)
        return dogen::quilt::cpp::formattables::concept_info_generator::create_ptr(position);
    if ((position % 9) == 2)
        return dogen::quilt::cpp::formattables::enum_info_generator::create_ptr(position);
    if ((position % 9) == 3)
        return dogen::quilt::cpp::formattables::forward_declarations_info_generator::create_ptr(position);
    if ((position % 9) == 4)
        return dogen::quilt::cpp::formattables::includers_info_generator::create_ptr(position);
    if ((position % 9) == 5)
        return dogen::quilt::cpp::formattables::odb_options_info_generator::create_ptr(position);
    if ((position % 9) == 6)
        return dogen::quilt::cpp::formattables::primitive_info_generator::create_ptr(position);
    if ((position % 9) == 7)
        return dogen::quilt::cpp::formattables::registrar_info_generator::create_ptr(position);
    if ((position % 9) == 8)
        return dogen::quilt::cpp::formattables::visitor_info_generator::create_ptr(position);
    return dogen::quilt::cpp::formattables::class_info_generator::create_ptr(position);
}

} } } }
