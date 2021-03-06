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
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/element.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::element>& lhs,
const boost::shared_ptr<dogen::yarn::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {

model::model()
    : has_generatable_types_(static_cast<bool>(0)),
      input_language_(static_cast<dogen::yarn::languages>(0)),
      output_language_(static_cast<dogen::yarn::languages>(0)) { }

model::model(
    const dogen::yarn::name& name,
    const std::vector<boost::shared_ptr<dogen::yarn::element> >& elements,
    const dogen::yarn::module& root_module,
    const std::unordered_set<std::string>& module_ids,
    const bool has_generatable_types,
    const dogen::yarn::languages input_language,
    const dogen::yarn::languages output_language)
    : name_(name),
      elements_(elements),
      root_module_(root_module),
      module_ids_(module_ids),
      has_generatable_types_(has_generatable_types),
      input_language_(input_language),
      output_language_(output_language) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(elements_, other.elements_);
    swap(root_module_, other.root_module_);
    swap(module_ids_, other.module_ids_);
    swap(has_generatable_types_, other.has_generatable_types_);
    swap(input_language_, other.input_language_);
    swap(output_language_, other.output_language_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        elements_ == rhs.elements_ &&
        root_module_ == rhs.root_module_ &&
        module_ids_ == rhs.module_ids_ &&
        has_generatable_types_ == rhs.has_generatable_types_ &&
        input_language_ == rhs.input_language_ &&
        output_language_ == rhs.output_language_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& model::name() const {
    return name_;
}

dogen::yarn::name& model::name() {
    return name_;
}

void model::name(const dogen::yarn::name& v) {
    name_ = v;
}

void model::name(const dogen::yarn::name&& v) {
    name_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::yarn::element> >& model::elements() const {
    return elements_;
}

std::vector<boost::shared_ptr<dogen::yarn::element> >& model::elements() {
    return elements_;
}

void model::elements(const std::vector<boost::shared_ptr<dogen::yarn::element> >& v) {
    elements_ = v;
}

void model::elements(const std::vector<boost::shared_ptr<dogen::yarn::element> >&& v) {
    elements_ = std::move(v);
}

const dogen::yarn::module& model::root_module() const {
    return root_module_;
}

dogen::yarn::module& model::root_module() {
    return root_module_;
}

void model::root_module(const dogen::yarn::module& v) {
    root_module_ = v;
}

void model::root_module(const dogen::yarn::module&& v) {
    root_module_ = std::move(v);
}

const std::unordered_set<std::string>& model::module_ids() const {
    return module_ids_;
}

std::unordered_set<std::string>& model::module_ids() {
    return module_ids_;
}

void model::module_ids(const std::unordered_set<std::string>& v) {
    module_ids_ = v;
}

void model::module_ids(const std::unordered_set<std::string>&& v) {
    module_ids_ = std::move(v);
}

bool model::has_generatable_types() const {
    return has_generatable_types_;
}

void model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

dogen::yarn::languages model::input_language() const {
    return input_language_;
}

void model::input_language(const dogen::yarn::languages v) {
    input_language_ = v;
}

dogen::yarn::languages model::output_language() const {
    return output_language_;
}

void model::output_language(const dogen::yarn::languages v) {
    output_language_ = v;
}

} }
