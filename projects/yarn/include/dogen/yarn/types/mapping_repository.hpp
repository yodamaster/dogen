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
#ifndef DOGEN_YARN_TYPES_MAPPING_REPOSITORY_HPP
#define DOGEN_YARN_TYPES_MAPPING_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/hash/languages_hash.hpp"
#include "dogen/yarn/serialization/mapping_repository_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class mapping_repository final {
public:
    mapping_repository() = default;
    mapping_repository(const mapping_repository&) = default;
    mapping_repository(mapping_repository&&) = default;
    ~mapping_repository() = default;

public:
    mapping_repository(
        const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id,
        const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::mapping_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::mapping_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id() const;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id();
    void by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v);
    void by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v);

    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id() const;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id();
    void by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v);
    void by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v);

public:
    bool operator==(const mapping_repository& rhs) const;
    bool operator!=(const mapping_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_repository& other) noexcept;
    mapping_repository& operator=(mapping_repository other);

private:
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> > by_upsilon_id_;
    std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> > by_language_agnostic_id_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::mapping_repository& lhs,
    dogen::yarn::mapping_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif