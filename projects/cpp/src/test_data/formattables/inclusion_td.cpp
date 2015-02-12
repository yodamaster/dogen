/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/test_data/formattables/inclusion_delimiter_types_td.hpp"
#include "dogen/cpp/test_data/formattables/inclusion_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::formattables::inclusion_delimiter_types
create_dogen_cpp_formattables_inclusion_delimiter_types(const unsigned int position) {
    return dogen::cpp::formattables::inclusion_delimiter_types_generator::create(position);
}

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_generator::inclusion_generator() : position_(0) { }

void inclusion_generator::
populate(const unsigned int position, result_type& v) {
    v.no_inclusion_required(create_bool(position + 0));
    v.inclusion_path(create_boost_filesystem_path(position + 1));
    v.inclusion_delimiter_type(create_dogen_cpp_formattables_inclusion_delimiter_types(position + 2));
}

inclusion_generator::result_type
inclusion_generator::create(const unsigned int position) {
    inclusion r;
    inclusion_generator::populate(position, r);
    return r;
}
inclusion_generator::result_type*
inclusion_generator::create_ptr(const unsigned int position) {
    inclusion* p = new inclusion();
    inclusion_generator::populate(position, *p);
    return p;
}

inclusion_generator::result_type
inclusion_generator::operator()() {
    return create(position_++);
}

} } }