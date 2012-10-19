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
#include "dogen/split_project/test_data/package/a_class_td.hpp"
#include "dogen/split_project/test_data/versioned_key_td.hpp"

namespace {

dogen::split_project::versioned_key
create_dogen_split_project_versioned_key(const unsigned int position) {
    return dogen::split_project::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace split_project {
namespace package {

void a_class_generator::
populate(const unsigned int position, result_type& v) {
    v.versioned_key(create_dogen_split_project_versioned_key(position + 0));
}

a_class_generator::result_type
a_class_generator::create(const unsigned int position) {
    a_class r;
    a_class_generator::populate(position, r);
    return r;
}

a_class_generator::result_type
a_class_generator::operator()() {
    return create(position_++);

}

} } }
