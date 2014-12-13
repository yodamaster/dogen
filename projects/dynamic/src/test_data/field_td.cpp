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
#include "dogen/dynamic/test_data/field_td.hpp"
#include "dogen/dynamic/test_data/name_td.hpp"
#include "dogen/dynamic/test_data/value_td.hpp"

namespace {

dogen::dynamic::value*
create_dogen_dynamic_value_ptr(const unsigned int position) {
    return dogen::dynamic::value_generator::create_ptr(position);
}

boost::shared_ptr<dogen::dynamic::value>
create_boost_shared_ptr_dogen_dynamic_value(unsigned int position) {
    boost::shared_ptr<dogen::dynamic::value> r(
        create_dogen_dynamic_value_ptr(position));
    return r;
}

dogen::dynamic::name
create_dogen_dynamic_name(const unsigned int position) {
    return dogen::dynamic::name_generator::create(position);
}

}

namespace dogen {
namespace dynamic {

field_generator::field_generator() : position_(0) { }

void field_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_boost_shared_ptr_dogen_dynamic_value(position + 0));
    v.name(create_dogen_dynamic_name(position + 1));
}

field_generator::result_type
field_generator::create(const unsigned int position) {
    field r;
    field_generator::populate(position, r);
    return r;
}
field_generator::result_type*
field_generator::create_ptr(const unsigned int position) {
    field* p = new field();
    field_generator::populate(position, *p);
    return p;
}

field_generator::result_type
field_generator::operator()() {
    return create(position_++);
}

} }
