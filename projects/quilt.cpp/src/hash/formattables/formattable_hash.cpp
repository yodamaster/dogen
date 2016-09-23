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
#include "dogen/yarn/hash/element_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/formattable_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/element_configuration_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_element(const boost::shared_ptr<dogen::yarn::element>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::size_t formattable_hasher::hash(const formattable& v) {
    std::size_t seed(0);

    combine(seed, hash_boost_shared_ptr_dogen_yarn_element(v.element()));
    combine(seed, v.configuration());

    return seed;
}

} } } }