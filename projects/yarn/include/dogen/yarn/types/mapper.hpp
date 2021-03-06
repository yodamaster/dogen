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
#ifndef DOGEN_YARN_TYPES_MAPPER_HPP
#define DOGEN_YARN_TYPES_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/mapping_context.hpp"
#include "dogen/yarn/types/mapping_set_repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

class mapper final {
public:
    explicit mapper(const mapping_set_repository& msrp);

private:
    const std::unordered_map<std::string, name>&
    translations_for_language(const mapping_set& ms, const languages from,
        const languages to) const;

    std::unordered_map<std::string, name>
    injections_for_language(const mapping_set& ms, const languages l,
        const intermediate_model& im) const;

    mapping_context create_mapping_context(const mapping_set& ms,
        const languages from, const languages to,
        const intermediate_model& im) const;

private:
    name_tree walk_name_tree(const mapping_context& mc,
        const name_tree& nt, const bool skip_injection = false) const;
    void map_attributes(const mapping_context& mc,
        std::list<attribute>& attrs) const;

public:
    intermediate_model map(const languages from, const languages to,
        const intermediate_model& im) const;

private:
    const mapping_set_repository& mapping_set_repository_;
};

} }

#endif
