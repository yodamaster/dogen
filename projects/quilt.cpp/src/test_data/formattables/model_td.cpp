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
#include "dogen/quilt.cpp/test_data/formattables/model_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/profile_group_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/facet_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/annotations/streaming_annotations_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::annotations::streaming_annotations
create_dogen_quilt_cpp_annotations_streaming_annotations(const unsigned int position) {
    return dogen::quilt::cpp::annotations::streaming_annotations_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::annotations::streaming_annotations> create_std_unordered_map_std_string_dogen_quilt_cpp_annotations_streaming_annotations(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::annotations::streaming_annotations> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_annotations_streaming_annotations(position + i)));
    }
    return r;
}

dogen::quilt::cpp::formattables::formattable
create_dogen_quilt_cpp_formattables_formattable(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formattable_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formattable(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formattable> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_formattable(position + i)));
    }
    return r;
}

dogen::quilt::cpp::formattables::facet_configuration
create_dogen_quilt_cpp_formattables_facet_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::facet_configuration_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_configuration> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_configuration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_facet_configuration(position + i)));
    }
    return r;
}

dogen::quilt::cpp::formattables::profile_group
create_dogen_quilt_cpp_formattables_profile_group(const unsigned int position) {
    return dogen::quilt::cpp::formattables::profile_group_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.streaming_annotations(create_std_unordered_map_std_string_dogen_quilt_cpp_annotations_streaming_annotations(position + 0));
    v.formattables(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formattable(position + 1));
    v.facet_configurations(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(position + 2));
    v.global_profile_group(create_dogen_quilt_cpp_formattables_profile_group(position + 3));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} } } }