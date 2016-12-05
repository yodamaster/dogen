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
#ifndef DOGEN_QUILT_TYPES_WORKFLOW_HPP
#define DOGEN_QUILT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/quilt/types/backend_registrar.hpp"
#include "dogen/quilt/types/backend_interface.hpp"

namespace dogen {
namespace quilt {

/**
 * @brief Manages the entire backend workflow.
 */
class workflow {
public:
    workflow(const options::knitting_options& o,
        const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& agf);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static backend_registrar& registrar();

    /**
     * @brief Returns all of the available archetype locations across
     * all backends.
     */
    static std::list<annotations::archetype_location>
    archetype_locations();

public:
    /**
     * @brief Returns all directories managed by all backends.
     */
    std::forward_list<boost::filesystem::path>
    managed_directories(const yarn::model& m) const;

    /**
     * @brief Generates files for the supplied model using all
     * registered backends.
     */
    std::forward_list<formatters::artefact>
    execute(const yarn::model& m) const;

private:
    static std::shared_ptr<backend_registrar> registrar_;
    const options::knitting_options knitting_options_;
    const annotations::type_repository& repository_;
    const annotations::annotation_groups_factory& annotation_factory_;
};

} }

#endif
