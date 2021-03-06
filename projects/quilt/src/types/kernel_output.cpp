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
#include "dogen/quilt/types/kernel_output.hpp"

namespace dogen {
namespace quilt {

kernel_output::kernel_output(
    const std::list<dogen::formatters::artefact>& artefacts,
    const std::list<boost::filesystem::path>& managed_directories)
    : artefacts_(artefacts),
      managed_directories_(managed_directories) { }

void kernel_output::swap(kernel_output& other) noexcept {
    using std::swap;
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
}

bool kernel_output::operator==(const kernel_output& rhs) const {
    return artefacts_ == rhs.artefacts_ &&
        managed_directories_ == rhs.managed_directories_;
}

kernel_output& kernel_output::operator=(kernel_output other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::formatters::artefact>& kernel_output::artefacts() const {
    return artefacts_;
}

std::list<dogen::formatters::artefact>& kernel_output::artefacts() {
    return artefacts_;
}

void kernel_output::artefacts(const std::list<dogen::formatters::artefact>& v) {
    artefacts_ = v;
}

void kernel_output::artefacts(const std::list<dogen::formatters::artefact>&& v) {
    artefacts_ = std::move(v);
}

const std::list<boost::filesystem::path>& kernel_output::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& kernel_output::managed_directories() {
    return managed_directories_;
}

void kernel_output::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void kernel_output::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

} }
