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
#include "dogen/dia/test_data/layer_sequence.hpp"
#include "dogen/dia/test_data/object_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

layer_generator::result_type
layer_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::object> objects;
    object_sequence sequence;

    if (position == 0) {
        objects.push_back(sequence());
        return dogen::dia::layer("layer0", true, true, objects);
    } else if (position == 1) {
        objects.push_back(sequence());
        return dogen::dia::layer("layer1", true, false, objects);
    }
    objects.push_back(sequence());
    return dogen::dia::layer("layer2", false, false, objects);
}

} } } }
