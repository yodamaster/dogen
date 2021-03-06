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
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

std::string registrar_implementation_formatter::static_artefact() {
    return traits::registrar_implementation_archetype();
}

std::string registrar_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
registrar_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(),  cpp::traits::kernel(),
          traits::facet(),
          registrar_implementation_formatter::static_artefact());
    return r;
}

std::type_index registrar_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::registrar)));
    return r;
}

inclusion_support_types registrar_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path registrar_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(registrar_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path registrar_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> registrar_implementation_formatter::
inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto arch(static_artefact());
    const auto& rg(assistant::as<fabric::registrar>(arch, e));
    auto builder(f.make());

    const auto rh_fn(traits::registrar_header_archetype());
    builder.add(rg.name(), rh_fn);

    using ic = inclusion_constants;
    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    // XML serialisation
    builder.add(ic::boost::archive::xml_iarchive());
    builder.add(ic::boost::archive::xml_oarchive());

    const auto ch_fn(traits::class_header_archetype());
    builder.add(rg.leaves(), ch_fn);

    const auto carch(traits::canonical_archetype());
    builder.add(rg.registrar_dependencies(), carch);
    return builder.build();
}

dogen::formatters::artefact registrar_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& rg(a.as<fabric::registrar>(static_artefact(), e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(rg.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto deps(rg.model_dependencies());
            const auto carch(traits::canonical_archetype());
            const auto leaves(a.names_with_enabled_archetype(carch, rg.leaves()));
            const bool has_types(!deps.empty() || !leaves.empty());
            const std::string arg_name(has_types ? " ar" : "");
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void register_types(Archive&" << arg_name << ") {" << std::endl;
            if (has_types) {
                for (const auto& d : deps) {
                    const auto dqn(a.get_qualified_name(d));
a.stream() << "    " << dqn << "::register_types(ar);" << std::endl;
                }

                if (!deps.empty() && !leaves.empty())
a.stream() << std::endl;
                for (const auto l : leaves) {
                    const auto lqn(a.get_qualified_name(l));
a.stream() << "    ar.template register_type<" << lqn << ">();" << std::endl;
                }
            }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "template void register_types(boost::archive::polymorphic_oarchive&" << arg_name << ");" << std::endl;
a.stream() << "template void register_types(boost::archive::polymorphic_iarchive&" << arg_name << ");" << std::endl;
a.stream() << std::endl;
a.stream() << "template void register_types(boost::archive::text_oarchive&" << arg_name << ");" << std::endl;
a.stream() << "template void register_types(boost::archive::text_iarchive&" << arg_name << ");" << std::endl;
a.stream() << std::endl;
a.stream() << "template void register_types(boost::archive::binary_oarchive&" << arg_name << ");" << std::endl;
a.stream() << "template void register_types(boost::archive::binary_iarchive&" << arg_name << ");" << std::endl;
a.stream() << std::endl;
a.stream() << "template void register_types(boost::archive::xml_oarchive&" << arg_name << ");" << std::endl;
a.stream() << "template void register_types(boost::archive::xml_iarchive&" << arg_name << ");" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}

} } } } }
