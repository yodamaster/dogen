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
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

std::string odb_options_formatter::static_artefact() {
    return traits::odb_options_archetype();
}

std::string odb_options_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
odb_options_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::facet(), odb_options_formatter::static_artefact());
    return r;
}

std::type_index odb_options_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::odb_options)));
    return r;
}

inclusion_support_types odb_options_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path odb_options_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {
    using namespace dogen::utility::log;
    static logger
        lg(logger_factory("quilt.cpp.formatters.odb.odb_options_formatter"));

        const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path odb_options_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_odb_options(n, static_artefact());
}

std::list<std::string> odb_options_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact odb_options_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& o(a.as<fabric::odb_options>(static_artefact(), e));

    {
        a.make_decoration_preamble();

        const auto model_name(a.get_identifiable_model_name(o.name()));
        const auto product_name(a.get_product_name(o.name()));
        const auto odb_folder(a.get_odb_facet_directory());
a.stream() << "# enable C++11. FIXME: causes ODB crash in options file." << std::endl;
a.stream() << "# --std c++11" << std::endl;
a.stream() << std::endl;
a.stream() << "# target postgres" << std::endl;
a.stream() << "--database pgsql" << std::endl;
a.stream() << std::endl;
a.stream() << "# use the boost profile" << std::endl;
a.stream() << "--profile boost" << std::endl;
a.stream() << std::endl;
a.stream() << "# generate queries and embedded schemas" << std::endl;
a.stream() << "--generate-query" << std::endl;
a.stream() << "--generate-schema" << std::endl;
a.stream() << "--schema-format embedded" << std::endl;
a.stream() << std::endl;
a.stream() << "# use extensions similar to the dogen ones" << std::endl;
a.stream() << "# --ixx-suffix .ipp" << std::endl;
a.stream() << "# --hxx-suffix .hpp" << std::endl;
a.stream() << "--cxx-suffix .cpp" << std::endl;
a.stream() << std::endl;
a.stream() << "# fix domain includes" << std::endl;
a.stream() << "--include-regex '%(.*).hpp%" << product_name << "/" << model_name << "/types/$1.hpp%'" << std::endl;
a.stream() << std::endl;
a.stream() << "# fix odb generated includes" << std::endl;
a.stream() << "--include-regex '%(^[a-zA-Z0-9_]+)-odb.(.*)%" << product_name << "/" << model_name << "/odb/$1-odb.$2%'" << std::endl;
a.stream() << "--include-regex '%" << product_name << "/" << model_name << "/types/(.*)-odb.(.*)%" << product_name << "/" << model_name << "/odb/$1-odb.$2%'" << std::endl;
a.stream() << std::endl;
a.stream() << "# debug regexes" << std::endl;
a.stream() << "# --include-regex-trace" << std::endl;
a.stream() << std::endl;
a.stream() << "# make the header guards similar to dogen ones" << std::endl;
a.stream() << "--guard-prefix " << boost::to_upper_copy(product_name) << "_" << boost::to_upper_copy(model_name) << "_" << boost::to_upper_copy(odb_folder) << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }
