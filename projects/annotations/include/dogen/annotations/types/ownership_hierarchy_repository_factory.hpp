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
#ifndef DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_REPOSITORY_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_OWNERSHIP_HIERARCHY_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"

namespace dogen {
namespace annotations {

class ownership_hierarchy_repository_factory final {
private:
    void validate(const std::list<ownership_hierarchy>& ohs) const;

    void populate_ownership_hierarchies(
        const std::list<ownership_hierarchy>& ohs,
        ownership_hierarchy_repository& rp) const;

    void populate_facet_names_by_model_name(
        ownership_hierarchy_repository& rp) const;

    void populate_formatter_names_by_model_name(
        ownership_hierarchy_repository& rp) const;

public:
    ownership_hierarchy_repository
        make(const std::list<ownership_hierarchy>& ohs) const;
};

} }

#endif