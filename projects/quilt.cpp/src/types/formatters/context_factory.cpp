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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formatters/building_error.hpp"
#include "dogen/quilt.cpp/types/formatters/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.context_factory"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

const annotations::streaming_annotations_repository
context_factory::empty_streaming_annotations_repository_ =
    annotations::streaming_annotations_repository();
const annotations::element_annotations
context_factory::empty_element_annotations_ = annotations::element_annotations();
const properties::element_properties
context_factory::empty_element_properties_ = properties::element_properties();
const std::unordered_map<
    std::string,
    std::unordered_map<
        std::string,
        std::list<std::shared_ptr<helper_formatter_interface>>>>
    context_factory::
    empty_helpers_ = std::unordered_map<
    std::string,
    std::unordered_map<
        std::string,
        std::list<std::shared_ptr<helper_formatter_interface>>>>();

context_factory::context_factory(
    const annotations::streaming_annotations_repository& ssrp,
    const annotations::element_annotations_repository& esrp,
    const properties::element_properties_repository& eprp,
    const std::unordered_map<
    std::string, std::unordered_map<
    std::string,
    std::list<std::shared_ptr<helper_formatter_interface>>>>& helpers)
    : streaming_annotations_repository_(ssrp), element_annotations_(esrp),
      element_properties_(eprp), formatter_helpers_(helpers) {}

const properties::element_properties& context_factory::
element_properties_for_id(const std::string& n) const {
    const auto& fp(element_properties_.by_id());
    const auto i(fp.find(n));
    if (i == fp.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << n;
        BOOST_THROW_EXCEPTION(
            workflow_error(formatter_properties_not_found + n));
    }
    return i->second;
}

const annotations::element_annotations& context_factory::
element_annotations_for_id(const std::string& n) const {
    const auto& b(element_annotations_.by_id());
    const auto i(b.find(n));
    if (i == b.end()) {
        // FIXME: we will return empty element_annotationss due to the hackery we
        // are doing at the moment in factory.
        return empty_element_annotations_;
    }
    return i->second;
}

context context_factory::make_empty_context() const {
    return context(empty_streaming_annotations_repository_,
        empty_element_annotations_, empty_element_properties_, empty_helpers_);
}

context context_factory::make(const std::string& id) const {
    const auto& ep(element_properties_for_id(id));
    const auto& es(element_annotations_for_id(id));
    const auto& ssrp(streaming_annotations_repository_);
    return context(ssrp, es, ep, formatter_helpers_);
}

} } } }
