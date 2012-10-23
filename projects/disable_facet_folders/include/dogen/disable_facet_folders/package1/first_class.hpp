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
#ifndef DOGEN_DISABLE_FACET_FOLDERS_PACKAGE1_FIRST_CLASS_HPP
#define DOGEN_DISABLE_FACET_FOLDERS_PACKAGE1_FIRST_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/disable_facet_folders/package1/first_class_fwd_ser.hpp"
#include "dogen/disable_facet_folders/versioned_key.hpp"

namespace dogen {
namespace disable_facet_folders {
namespace package1 {

class first_class_serializer;

class first_class final {
public:
    first_class(const first_class&) = default;
    first_class(first_class&&) = default;
    ~first_class() = default;

public:
    first_class();

public:
    first_class(
        const int public_attribute,
        const int private_attribute,
        const dogen::disable_facet_folders::versioned_key& versioned_key);

public:
    friend class dogen::disable_facet_folders::package1::first_class_serializer;

public:
    int public_attribute() const {
        return public_attribute_;
    }

    void public_attribute(const int v) {
        public_attribute_ = v;
    }

    int private_attribute() const {
        return private_attribute_;
    }

    void private_attribute(const int v) {
        private_attribute_ = v;
    }

    dogen::disable_facet_folders::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::disable_facet_folders::versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const first_class& rhs) const;
    bool operator!=(const first_class& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(first_class& other) noexcept;
    first_class& operator=(first_class other);

private:
    int public_attribute_;
    int private_attribute_;
    dogen::disable_facet_folders::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::disable_facet_folders::package1::first_class& lhs,
    dogen::disable_facet_folders::package1::first_class& rhs) {
    lhs.swap(rhs);
}

}

#endif
