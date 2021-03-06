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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar.hpp"
#include "dogen/quilt.cpp/types/formatters/stitch_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Generates all files for the supplied entity.
 */
class workflow final {
public:
    workflow(const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& af,
        const dogen::formatters::repository& frp);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::formatters::registrar& registrar();

private:
    formattables::artefact_properties get_artefact_properties(const
        std::unordered_map<std::string, formattables::artefact_properties>&
        artefact_properties, const std::string& archetype) const;

private:
    std::list<dogen::formatters::artefact>
    format(const formattables::model& fm, const yarn::element& e,
        const formattables::element_properties& ep) const;

public:
    std::list<dogen::formatters::artefact>
    execute(const formattables::model& fm) const;

private:
    static std::shared_ptr<cpp::formatters::registrar> registrar_;
    const stitch_formatter stitch_formatter_;
};

} } } }

#endif
