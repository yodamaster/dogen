/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CLASS_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CLASS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/tuple/tuple.hpp>
#include "dogen/generator/backends/cpp/view_models/property_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/parent_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class class_view_model {
public:
    class_view_model(const class_view_model&) = default;
    ~class_view_model() = default;
    class_view_model(class_view_model&&) = default;
    class_view_model& operator=(const class_view_model&) = default;

public:
    class_view_model() : has_primitive_properties_(false),
                         requires_stream_manipulators_(false),
                         is_parent_(false) { }

    explicit class_view_model(const std::string& name)
        : name_(name),
          has_primitive_properties_(false),
          requires_stream_manipulators_(false),
          requires_manual_move_constructor_(false),
          is_parent_(false) { }

public:
    /**
     * @brief List of all namespaces containing the class.
     */
    /**@{*/
    std::list<std::string> namespaces() const { return namespaces_; }
    void namespaces(const std::list<std::string>& value) {
        namespaces_ = value;
    }
    /**@}*/

    /**
     * @brief Name of the class.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(const std::string& value) { name_ = value; }
    /**@}*/

    /**
     * @brief Properties of the class itself (e.g. excludes inherited
     * properties).
     */
    /**@{*/
    std::list<property_view_model> properties() const {
        return properties_;
    }
    void properties(std::list<property_view_model> value) {
        properties_ = value;
    }
    /**@}*/

    /**
     * @brief All properties of the class including inherited.
     */
    /**@{*/
    std::list<property_view_model> all_properties() const {
        return all_properties_;
    }
    void all_properties(std::list<property_view_model> value) {
        all_properties_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class has at least one property which is a
     * primitive, false otherwise.
     */
    /**@{*/
    bool has_primitive_properties() const {
        return(has_primitive_properties_);
    }
    void has_primitive_properties(bool value) {
        has_primitive_properties_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class has member variables which require
     * changing the stream with manipulators, false otherwise.
     *
     * Examples are boolean variables, which should be outputted as
     * true or false and as such require boolalpha.
     */
    /**@{*/
    bool requires_stream_manipulators() const {
        return(requires_stream_manipulators_);
    }
    void requires_stream_manipulators(bool value) {
        requires_stream_manipulators_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class requires a manually generated move
     * constructor, false otherwise.
     */
    /**@{*/
    bool requires_manual_move_constructor() const {
        return(requires_manual_move_constructor_);
    }
    void requires_manual_move_constructor(bool value) {
        requires_manual_move_constructor_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class requires a manually generated default
     * constructor, false otherwise.
     */
    /**@{*/
    bool requires_manual_default_constructor() const {
        return(requires_manual_default_constructor_);
    }
    void requires_manual_default_constructor(bool value) {
        requires_manual_default_constructor_ = value;
    }
    /**@}*/

    /**
     * @brief Parents for this class.
     */
    /**@{*/
    std::list<parent_view_model> parents() const {
        return parents_;
    }
    void parents(const std::list<parent_view_model>& value) {
        parents_ = value;
    }
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes,
     * false otherwise.
     */
    /**@{*/
    bool is_parent() const { return is_parent_; }
    void is_parent(bool value) { is_parent_ = value; }
    /**@}*/

    /**
     * @brief Documentation for the property
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& v) { documentation_ = v; }
    /**@}*/

    /**
     * @brief Parent at the root of a class hierarchy, if any.
     */
    /**@{*/
    std::string original_parent_name() const { return original_parent_name_; }
    void original_parent_name(const std::string& v) {
        original_parent_name_ = v;
    }
    /**@}*/

    /**
     * @brief If the class is abstract, list of concrete types that
     * descend from it. Names are in identifiable name format.
     */
    /**@{*/
    std::list<std::string> leaves() const { return leaves_; }
    void leaves(const std::list<std::string>& v) { leaves_ = v; }
    /**@}*/

    /*
     * @brief Parameters associated with the pod.
     */
    /**@{*/
    std::vector<std::pair<std::string, std::string> >
    implementation_specific_parameters() const {
        return implementation_specific_parameters_;
    }
    void implementation_specific_parameters(
        const std::vector<std::pair<std::string, std::string> >& v) {
        implementation_specific_parameters_ = v;
    }
    /**@}*/

private:
    std::list<std::string> namespaces_;
    std::list<property_view_model> properties_;
    std::list<property_view_model> all_properties_;
    std::list<parent_view_model> parents_;
    std::string original_parent_name_;
    std::list<std::string> leaves_;
    std::string name_;
    bool has_primitive_properties_;
    bool requires_stream_manipulators_;
    bool requires_manual_move_constructor_;
    bool requires_manual_default_constructor_;
    std::string schema_name_;
    bool is_parent_;
    std::string documentation_;
    std::vector<std::pair<std::string, std::string> >
    implementation_specific_parameters_;
};

} } } } }

#endif
