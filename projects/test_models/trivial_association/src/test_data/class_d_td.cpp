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
#include "dogen/test_models/trivial_association/test_data/class_d_td.hpp"

namespace dogen {
namespace test_models {
namespace trivial_association {

class_d_generator::class_d_generator() : position_(0) { }

void class_d_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

class_d_generator::result_type
class_d_generator::create(const unsigned int/*position*/) {
    class_d r;
    return r;
}
class_d_generator::result_type*
class_d_generator::create_ptr(const unsigned int position) {
    class_d* p = new class_d();
    class_d_generator::populate(position, *p);
    return p;
}

class_d_generator::result_type
class_d_generator::operator()() {
    return create(position_++);
}

} } }
