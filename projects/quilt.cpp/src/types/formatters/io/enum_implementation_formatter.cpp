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
#include "dogen/quilt.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>
#include "dogen/formatters/types/sequence_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string enum_implementation_formatter::static_artefact() {
    return traits::enum_implementation_archetype();
}

std::string enum_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
enum_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(),  cpp::traits::kernel(),
          traits::facet(),
          enum_implementation_formatter::static_artefact());
    return r;
}

std::type_index enum_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::enumeration)));
    return r;
}

inclusion_support_types enum_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(enum_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path enum_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> enum_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::element& e) const {
    auto builder(f.make());

    builder.add(inclusion_constants::std::ostream());
    builder.add(inclusion_constants::std::stdexcept());
    builder.add(inclusion_constants::std::string());

    const auto eh_fn(traits::enum_header_archetype());
    builder.add(e.name(), eh_fn);
    return builder.build();
}

dogen::formatters::artefact enum_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& ye(a.as<yarn::enumeration>(static_artefact(), e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(ye.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << ye.name().simple() << "& v) {" << std::endl;
a.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << ye.name().simple() << "\\\", \" << \"\\\"value\\\": \";" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::string attr;" << std::endl;
a.stream() << "    switch (v) {" << std::endl;
            for (const auto& en : ye.enumerators()) {
a.stream() << "    case " << ye.name().simple() << "::" << en.name().simple() << ":" << std::endl;
a.stream() << "        attr = \"\\\"" << en.name().simple() << "\\\"\";" << std::endl;
a.stream() << "        break;" << std::endl;
            }
a.stream() << "    default:" << std::endl;
a.stream() << "        throw std::invalid_argument(\"Invalid value for " << ye.name().simple() << "\");" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    s << attr << \" }\";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
         } // snf
    } // sbf
    return a.make_artefact();
}

} } } } }
