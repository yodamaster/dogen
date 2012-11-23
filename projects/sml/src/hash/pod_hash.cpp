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
#include "dogen/sml/hash/category_types_hash.hpp"
#include "dogen/sml/hash/pod_hash.hpp"
#include "dogen/sml/hash/pod_types_hash.hpp"
#include "dogen/sml/hash/property_hash.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_vector_dogen_sml_property(const std::vector<dogen::sml::property>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_sml_qualified_name(const boost::optional<dogen::sml::qualified_name>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_dogen_sml_qualified_name(const std::list<dogen::sml::qualified_name>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t pod_hasher::hash(const pod&v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_vector_dogen_sml_property(v.properties()));
    combine(seed, hash_boost_optional_dogen_sml_qualified_name(v.parent_name()));
    combine(seed, hash_boost_optional_dogen_sml_qualified_name(v.original_parent_name()));
    combine(seed, hash_std_list_dogen_sml_qualified_name(v.leaves()));
    combine(seed, v.generate());
    combine(seed, v.is_parent());
    combine(seed, v.category_type());
    combine(seed, v.pod_type());
    combine(seed, v.documentation());
    combine(seed, v.number_of_type_arguments());

    return seed;
}

} }
