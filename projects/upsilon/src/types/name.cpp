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
#include "dogen/upsilon/types/name.hpp"

namespace dogen {
namespace upsilon {

name::name(
    const std::string& id,
    const std::string& value,
    const std::string& schema_name)
    : id_(id),
      value_(value),
      schema_name_(schema_name) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(value_, other.value_);
    swap(schema_name_, other.schema_name_);
}

bool name::operator==(const name& rhs) const {
    return id_ == rhs.id_ &&
        value_ == rhs.value_ &&
        schema_name_ == rhs.schema_name_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& name::id() const {
    return id_;
}

std::string& name::id() {
    return id_;
}

void name::id(const std::string& v) {
    id_ = v;
}

void name::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::string& name::value() const {
    return value_;
}

std::string& name::value() {
    return value_;
}

void name::value(const std::string& v) {
    value_ = v;
}

void name::value(const std::string&& v) {
    value_ = std::move(v);
}

const std::string& name::schema_name() const {
    return schema_name_;
}

std::string& name::schema_name() {
    return schema_name_;
}

void name::schema_name(const std::string& v) {
    schema_name_ = v;
}

void name::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

} }
