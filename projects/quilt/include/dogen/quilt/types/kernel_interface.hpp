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
#ifndef DOGEN_QUILT_TYPES_KERNEL_INTERFACE_HPP
#define DOGEN_QUILT_TYPES_KERNEL_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/quilt/types/kernel_output.hpp"

namespace dogen {
namespace quilt {

/**
 * @brief Responsible for converting a Yarn model into source code
 * according to a well-defined grammar.
 */
class kernel_interface {
public:
    kernel_interface() = default;
    kernel_interface(const kernel_interface&) = delete;
    kernel_interface(kernel_interface&&) = default;
    virtual ~kernel_interface() noexcept = 0;

public:
    /**
     * @brief Returns the identity of this kernel.
     */
    virtual std::string id() const = 0;

    /**
     * @brief The artefact location for the kernel itself.
     *
     * Note that this is not a "true" archetype location, but a
     * location of a container of archetypes (the kernel).
     */
    virtual annotations::archetype_location archetype_location() const = 0;

    /**
     * @brief All archetype locations for the archetypes owned by this
     * kernel, listing all available kernels, facets and archetypes.
     *
     * FIXME: we need a better name for this.
     */
    virtual std::forward_list<annotations::archetype_location>
    archetype_locations() const = 0;

    /**
     * @brief Language supported by this kernel.
     */
    virtual yarn::languages language() const = 0;

    /**
     * @brief Generates the source code for the kernel.
     */
    virtual kernel_output generate(const options::knitting_options& ko,
        const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& agf,
        const dogen::formatters::repository& drp,
        const dogen::formatters::decoration_properties_factory& dpf,
        const bool requires_kernel_directory,
        const yarn::model& m) const = 0;
};

} }

#endif
