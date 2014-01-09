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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/om/types/utility.hpp"
#include "dogen/om/types/indent_filter.hpp"
#include "dogen/om/types/formatting_error.hpp"
#include "dogen/om/types/cpp_file_boilerplate_formatter.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.cpp_types_main_header_file_formatter"));

const std::string empty;
const std::string missing_helper_ptr("Helper pointer is null");
const std::string parent_not_found("Type is a child but parent not found");
const std::string multiple_inheritance_found(
    "Multiple inheritance is not supported");
const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

const std::string scope_operator("::");
const std::string algorithm_include("algorithm");
const std::string iosfwd_include("iosfwd");

}

namespace dogen {
namespace om {

/**
 * @brief Provides a set of utility functions to help with
 * formatting.
 *
 * All parameters passed in to the helper must have a lifetime
 * greater than (or equal to) the helper itself as it keeps
 * references to them.
 */
class cpp_types_main_header_file_formatter::helper : private sml::type_visitor {
public:
    helper() = delete;
    helper(const helper&) = delete;
    helper(helper&&) = delete;
    helper& operator=(const helper&) = delete;

private:
    static bool is_true(const boost::property_tree::ptree& meta_data,
        const std::string& key) {
        sml::meta_data_reader reader(meta_data);
        return reader.is_true(key);
    }

public:
    ~helper() noexcept { }

    helper(const sml::model& m, const boost::property_tree::ptree& meta_data,
        const annotation& a, const bool legacy_mode)
        : model_(m), utility_(stream_),
          boilerplate_(is_true(meta_data, sml::tags::generate_preamble),
              is_true(meta_data,
                  sml::tags::cpp::types::header_file::generate_header_guards)),
          annotation_(a), legacy_mode_(legacy_mode) {

        sml::meta_data_reader reader(meta_data);
        using types = sml::tags::cpp::types;
        const auto& fn(types::header_file::file_name);
        relative_file_path_ = reader.get(fn);

        dogen::om::indent_filter::push(stream_, 4);
        stream_.push(string_stream_);
    }

private:
    /**
     * @brief Processes all includes for relationships of type rt.
     */
    void includes_for_relationship(const sml::object& o,
        const sml::relationship_types rt);

private:
    using sml::type_visitor::visit;
    void visit(const sml::object& o) override;

public:
    /**
     * @brief Stream to which the formatted output will be sent.
     */
    std::ostream& stream() { return stream_; }

    /**
     * @brief Returns the contents of the stream.
     */
    std::string contents() const { return string_stream_.str(); }

    /**
     * @brief Formatting utility methods.
     */
    om::utility& utility() { return utility_; }

    /**
     * @brief Relative path of the element being formatted.
     */
    boost::filesystem::path relative_file_path() { return relative_file_path_; }

public:
    /**
     * @brief Computes the include files for this header file.
     */
    void compute_includes(const sml::type& t) { t.accept(*this); }

    /**
     * @brief Uses the boilerplate formatter to format the start of
     * the boilerplate.
     */
    void format_begin() {
        boilerplate_.format_begin(stream_, annotation_, includes_,
            relative_file_path_);
        utility_.managed_blank_line();
    }

    /**
     * @brief Uses the boilerplate formatter to format the end of
     * the boilerplate.
     */
    void format_end() {
        boilerplate_.format_end(stream_, annotation_, relative_file_path_);
    }

private:
    const sml::model& model_;
    boost::iostreams::filtering_ostream stream_;
    om::utility utility_;
    cpp_includes includes_;
    cpp_file_boilerplate_formatter boilerplate_;
    const annotation annotation_;
    boost::filesystem::path relative_file_path_;
    std::ostringstream string_stream_;
    const bool legacy_mode_;
};

void cpp_types_main_header_file_formatter::helper::
includes_for_relationship(const sml::object& o,
    const sml::relationship_types rt) {

    auto i(o.relationships().find(rt));
    if (i == o.relationships().end())
        return;

    for (const auto& qn : i->second) {
        const auto j(model_.objects().find(qn));
        if (j == model_.objects().end())
            continue; // not an object

        sml::meta_data_reader reader(j->second.meta_data());
        using types = sml::tags::cpp::types;
        const auto fn_key(
            rt == sml::relationship_types::weak_associations ?
            types::forward_declarations_file::file_name :
            types::header_file::file_name);
        const auto fn(reader.get(fn_key));

        const auto fn_system_key(types::header_file::is_system);
        const auto is_system(reader.is_true(fn_system_key));

        if (is_system)
            includes_.system().push_back(fn);
        else
            includes_.user().push_back(fn);
    }
}

void cpp_types_main_header_file_formatter::helper::
visit(const sml::object& o) {
    sml::meta_data_reader reader(o.meta_data());
    using bs = sml::tags::cpp::serialization::boost;
    if (reader.is_true(bs::enabled)) {
        const auto fn(reader.get(bs::forward_declarations_file::file_name));
        includes_.user().push_back(fn);
    }

    // associations
    using sml::relationship_types;
    includes_for_relationship(o, relationship_types::regular_associations);
    includes_for_relationship(o, relationship_types::weak_associations);
    includes_for_relationship(o, relationship_types::visited_by);
    includes_for_relationship(o, relationship_types::parents);

    // hard-coded includes
    using types = sml::tags::cpp::types;

    if (legacy_mode_)
        includes_.system().push_back(algorithm_include);
    else {
        if (reader.is_true(types::generate_external_swap))
            includes_.system().push_back(algorithm_include);
    }

    if (reader.is_true(types::generate_to_stream) ||
        reader.is_true(types::generate_external_inserter))
        includes_.system().push_back(iosfwd_include);
}

cpp_types_main_header_file_formatter::cpp_types_main_header_file_formatter(
    const sml::model& model, const boost::filesystem::path& include_directory,
    const bool legacy_mode)
    : model_(model), include_directory_(include_directory),
      doxygen_next_(
          !start_on_first_line,
          use_documentation_tool_markup,
          !documenting_previous_identifier,
          comment_styles::c_style,
          !last_line_is_blank),
      doxygen_previous_(
          start_on_first_line,
          use_documentation_tool_markup,
          documenting_previous_identifier,
          comment_styles::cpp_style,
          !last_line_is_blank),
      legacy_mode_(legacy_mode) { }

std::list<std::string> cpp_types_main_header_file_formatter::
namespaces(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    return r;
}

void cpp_types_main_header_file_formatter::ensure_non_null_helper() const {
    if (helper_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_helper_ptr;
    BOOST_THROW_EXCEPTION(formatting_error(missing_helper_ptr));
}

file cpp_types_main_header_file_formatter::
build_file(const boost::property_tree::ptree& meta_data) const {
    ensure_non_null_helper();
    file r;
    sml::meta_data_reader reader(meta_data);
    r.contents(helper_->contents());
    r.relative_path(helper_->relative_file_path());
    r.absolute_path(include_directory_ / helper_->relative_file_path());
    r.overwrite(reader.is_true(sml::tags::cpp::types::header_file::overwrite));
    return r;
}

void cpp_types_main_header_file_formatter::
open_class(const sml::object& o) const {
    if (!o.documentation().empty())
        doxygen_next_.format(helper_->stream(), o.documentation());

    helper_->stream() << "class " << o.name().simple_name();

    if (!o.is_parent())
        helper_->stream() << " final";

    if (o.is_child()) {
        const auto i(o.relationships().find(sml::relationship_types::parents));
        if (i == o.relationships().end() || i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found;
            BOOST_THROW_EXCEPTION(formatting_error(parent_not_found));
        }

        if (i->second.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance_found;
            BOOST_THROW_EXCEPTION(formatting_error(multiple_inheritance_found));
        }

        const std::string parent_simple_name(i->second.front().simple_name());
        helper_->stream() << " :";
        helper_->stream() << " public ";

        if (!legacy_mode_)
            helper_->stream() << parent_simple_name;

        const auto j(model_.objects().find(i->second.front()));
        if (j == model_.objects().end()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found;
            BOOST_THROW_EXCEPTION(formatting_error(parent_not_found));
        }
        sml::meta_data_reader reader(j->second.meta_data());
        const auto pqn(reader.get(
                sml::tags::cpp::types::qualified_name));
        helper_->stream() << pqn;
    }
    helper_->stream() << " {" << std::endl;
}

void cpp_types_main_header_file_formatter::close_class() const {
    helper_->stream() << "};" << std::endl;
}

void cpp_types_main_header_file_formatter::
explicitly_defaulted_functions(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_defaulted_functions))
        return;

    helper_->utility().public_access_specifier();

    const auto& sn(o.name().simple_name());
    if (reader.is_false(types::generate_explicit_default_constructor))
        helper_->stream() << sn << "() = default;" << std::endl;

    helper_->stream() << sn << "(const " << sn << "&) = default;" << std::endl;

    if (reader.is_false(types::generate_explicit_move_constructor))
        helper_->stream() << sn << "(" << sn << "&&) = default;" << std::endl;

    if (!o.is_parent() && !o.is_child())
        helper_->stream() << "~" << sn << "() = default;" << std::endl;

    if (o.is_immutable()) {
        helper_->stream() << sn << "& operator=(const " << sn << "&) = delete;"
                         << std::endl;
    } else {
        const auto p(o.all_properties());
        if (p.empty()) {
            helper_->stream() << sn << "& operator=(const "
                             << sn << "&) = default;"
                             << std::endl;
        }
    }
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
default_constructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_default_constructor))
        return;

    helper_->utility().public_access_specifier();
    helper_->stream() << o.name().simple_name() << "();" << std::endl;
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
complete_constructor(const sml::object& o) const {
    {
        sml::meta_data_reader reader(o.meta_data());
        using types = sml::tags::cpp::types;
        if (reader.is_false(types::generate_complete_constructor))
            return;
    }

    const auto& props(o.all_properties());
    if (props.empty())
        return;

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    if (props.size() == 1) {
        const auto p(*props.begin());
        sml::meta_data_reader reader(p.meta_data());
        using types = sml::tags::cpp::types;
        helper_->stream() << "explicit " << sn << "(const "
                         << reader.get(types::complete_name);

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " " << p.name() << ");" << std::endl;
        helper_->utility().managed_blank_line();
        return;
    }

    helper_->stream() << sn << "(";
    {
        positive_indenter_scope s(helper_->stream());
        bool is_first(true);
        for (const auto p : props) {
            helper_->stream() << (is_first ? "" : ",") << std::endl;

            sml::meta_data_reader reader(p.meta_data());
            using types = sml::tags::cpp::types;
            helper_->stream() << "const " << reader.get(types::complete_name);

            if (!reader.is_true(types::is_simple_type))
                helper_->stream() << "&";

            helper_->stream() << " " << p.name();
            is_first = false;
        }
        helper_->stream() << ");" << std::endl;
    }
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
move_constructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_explicit_move_constructor))
        return;

    const auto& props(o.all_properties());
    if (props.empty())
        return;

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    helper_->stream() << sn << "(" << sn << "&& rhs);" << std::endl;
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
destructor(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (!reader.is_true(types::generate_explicit_destructor))
        return;

    if (!legacy_mode_)
        helper_->utility().public_access_specifier();

    const auto sn(o.name().simple_name());
    if (reader.is_true(types::destructor_is_pure_virtual)) {
        helper_->stream() << "virtual ~" << sn
                         << "() noexcept = 0;" << std::endl;
    } else {
        helper_->stream() << "virtual ~" << sn
                         << "() noexcept { }" << std::endl;
    }
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
friends(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (reader.is_false(types::generate_friends))
        return;

    helper_->utility().private_access_specifier();
    const auto sn(o.name().simple_name());
    helper_->stream() << "template<typename Archive>" << std::endl
                     << "friend void boost::serialization::save(Archive& ar"
                     << ", const " << sn << "& v, unsigned int version);"
                     << std::endl;
    helper_->utility().blank_line();

    helper_->stream() << "template<typename Archive>" << std::endl
                     << "friend void boost::serialization::load(Archive& ar"
                     << ", " << sn << "& v, unsigned int version);"
                     << std::endl;
    helper_->utility().managed_blank_line();

}

void cpp_types_main_header_file_formatter::simple_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());
    if (!doc.empty())
        doxygen_next_.format(helper_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(helper_->stream(), doc);

    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    helper_->stream() << cn << " " << p.name() << "() const;" << std::endl;

    if (!p.is_immutable()) {
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";

        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(helper_->stream(), doc);
}

void cpp_types_main_header_file_formatter::compound_type_getter_and_setter(
    const std::string& owner_name, const sml::property& p) const {
    const auto doc(p.documentation());

    if (!doc.empty())
        doxygen_next_.format(helper_->stream(), doc);

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_start_block(helper_->stream(), doc);

    // const getter
    sml::meta_data_reader reader(p.meta_data());
    using types = sml::tags::cpp::types;
    const auto cn(reader.get(types::complete_name));
    helper_->stream() << "const " << cn << "& " << p.name() << "() const;"
                     << std::endl;

    if (!p.is_immutable()) {
        // Popsicle immutability
        helper_->stream() << "" << cn << "& " << p.name() << "();" << std::endl;

        // traditional setter
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";
        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&";

        helper_->stream() << " v);" << std::endl;

        // move setter
        if (p.is_fluent())
            helper_->stream() << owner_name << "& ";
        else
            helper_->stream() << "void ";
        helper_->stream() << p.name() << "(const " << cn;

        if (!reader.is_true(types::is_simple_type))
            helper_->stream() << "&&";

        helper_->stream() << " v);" << std::endl;
    }

    if (!p.is_immutable())
        doxygen_next_.format_doxygen_end_block(helper_->stream(), doc);
}

void cpp_types_main_header_file_formatter::
getters_and_setters(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    helper_->utility().public_access_specifier();
    bool is_first(true);
    for (const auto p : o.local_properties()) {
        if (!is_first)
            helper_->utility().blank_line();

        sml::meta_data_reader reader(p.meta_data());
        if (reader.is_true(sml::tags::cpp::types::is_simple_type))
            simple_type_getter_and_setter(o.name().simple_name(), p);
        else
            compound_type_getter_and_setter(o.name().simple_name(), p);
        is_first = false;
    }
    helper_->utility().managed_blank_line();

}

void cpp_types_main_header_file_formatter::
member_variables(const sml::object& o) const {
    if (o.local_properties().empty())
        return;

    if (legacy_mode_)
        helper_->utility().blank_line();

    helper_->utility().private_access_specifier();
    for (const auto p : o.local_properties()) {
        sml::meta_data_reader reader(p.meta_data());
        helper_->stream() << reader.get(sml::tags::cpp::types::complete_name)
                         << " "
                         << helper_->utility().as_member_variable(p.name())
                         << ";"
                         << std::endl;
    }
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
internal_equality(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_equality))
        return;

    const auto sn(o.name().simple_name());
    if (o.is_parent()) {
        // equality is only public in leaf classes - MEC++-33
        helper_->utility().protected_access_specifier();
        helper_->stream() << "bool compare(const " << sn << "& rhs) const;"
                         << std::endl;
    } else {
        helper_->utility().public_access_specifier();
        helper_->stream() << "bool operator==(const " << sn
                         << "& rhs) const;" << std::endl;
        helper_->stream() << "bool operator!=(const " << sn << "& rhs) const ";

        helper_->utility().open_scope(padding_types::new_line);
        {
            positive_indenter_scope s(helper_->stream());
            helper_->stream() << "return !this->operator==(rhs);" << std::endl;
        }
        const auto nl(padding_types::new_line);
        helper_->utility().close_scope(nl);
        helper_->utility().managed_blank_line();
    }

    if (!o.is_parent() && !o.is_child())
        return;

    if (!legacy_mode_)
        helper_->utility().blank_line();

    helper_->utility().public_access_specifier();
    using types = sml::tags::cpp::types;
    if (o.is_parent() && !o.is_child()) {
        helper_->stream() << "virtual bool equals(const " << sn
                         <<  "& other) const = 0;"
                         << std::endl;
    } else if (o.is_parent()) {
        helper_->stream() << "virtual bool equals(const "
                         << reader.get(types::qualified_original_parent_name)
                         <<  "& other) const = 0;"
                         << std::endl;
    } else {
        helper_->stream() << "bool equals(const "
                         << reader.get(types::qualified_original_parent_name)
                         <<  "& other) const override;"
                         << std::endl;
    }
    helper_->utility().managed_blank_line();

}

void cpp_types_main_header_file_formatter::
to_stream(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_to_stream))
        return;

    helper_->utility().public_access_specifier();
    if (o.is_parent()) {
        helper_->stream() << "virtual void to_stream("
                         << "std::ostream& s) const;"
                         << std::endl;
    } else {
        helper_->stream() << "void to_stream(std::ostream& s) "
                         << "const override;"
                         << std::endl;
    }
    helper_->utility().managed_blank_line();

}

void cpp_types_main_header_file_formatter::
internal_swap(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_internal_swap))
        return;

    // swap is only public in leaf classes - MEC++-33
    if (o.is_parent())
        helper_->utility().protected_access_specifier();
    else
        helper_->utility().public_access_specifier();

    const auto sn(o.name().simple_name());
    helper_->stream() << "void swap(" << sn << "& other) noexcept;"
                     << std::endl;

    if (legacy_mode_)
        helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
internal_assignment(const sml::object& o) const {
    // assignment is only available in leaf classes - MEC++-33
    const auto props(o.all_properties());
    if (props.empty() || o.is_parent() || o.is_immutable())
        return;

    const auto sn(o.name().simple_name());

    if (legacy_mode_)
        helper_->utility().public_access_specifier();

    helper_->stream() << sn << "& operator=(" << sn << " other);" << std::endl;
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
visitor_method(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_accept))
        return;

    helper_->utility().public_access_specifier();
    const auto sn(o.name().simple_name());
    using types = sml::tags::cpp::types;
    const auto opn(reader.get(types::qualified_original_parent_name));

    if (reader.is_true(sml::tags::cpp::types::accept_is_pure_virtual)) {
        helper_->stream() << "virtual void accept(const " << sn
                         << "_visitor& v) const = 0;" << std::endl;
        helper_->stream() << "virtual void accept("
                         << sn << "_visitor& v) const = 0;" << std::endl;
        helper_->stream() << "virtual void accept(const " << sn
                         << "_visitor& v) = 0;" << std::endl;
        helper_->stream() << "virtual void accept("
                         << sn << "_visitor& v) = 0;" << std::endl;
        helper_->utility().blank_line();
        return;
    }

    helper_->utility().public_access_specifier();
    helper_->stream() << "virtual void accept(const "
                     << opn << "_visitor& v) const override {"
                     << std::endl;

    {
        positive_indenter_scope s(helper_->stream());
        helper_->stream() << "v.visit(*this);" << std::endl;
    }
    helper_->stream() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << "virtual void accept("  << opn
                     << "_visitor& v) const override {" << std::endl;

    {
        positive_indenter_scope s(helper_->stream());
        helper_->stream() << "v.visit(*this);" << std::endl;
    }
    helper_->stream() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << "virtual void accept(const "
                     << opn << "_visitor& v) override {" << std::endl;

    {
        positive_indenter_scope s(helper_->stream());
        helper_->stream() << "v.visit(*this);" << std::endl;
    }
    helper_->stream() << "}" << std::endl;
    helper_->utility().blank_line();
    helper_->stream() << "virtual void accept(" << opn
                     << "_visitor& v) override {" << std::endl;

    {
        positive_indenter_scope s(helper_->stream());
        helper_->stream() << "v.visit(*this);" << std::endl;
    }
    helper_->stream() << "}" << std::endl;
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
external_equality(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_equality) ||
        !o.is_parent())
        return;

    const auto nl(padding_types::new_line);
    const auto sn(o.name().simple_name());
    helper_->stream() << "inline bool operator==(const "
                     << sn << "& lhs, const " << sn << "& rhs) ";
    helper_->utility().open_scope(nl);
    {
        positive_indenter_scope s(helper_->stream());
        helper_->stream() << "return lhs.equals(rhs);" << std::endl;
    }
    helper_->utility().close_scope(nl);
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
external_swap(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (reader.is_false(sml::tags::cpp::types::generate_external_swap))
        return;

    {
        const auto std_ns(std::list<std::string> { "std" });
        cpp_formatters::namespace_helper ns(helper_->stream(), std_ns);
        helper_->utility().blank_line();

        const auto nl(padding_types::new_line);
        helper_->stream() << "template<>" << std::endl
                         << "inline void swap(" << std::endl;
        {
            positive_indenter_scope s(helper_->stream());
            const auto n(reader.get(sml::tags::cpp::types::qualified_name));
            helper_->stream() << n << "& lhs," << std::endl
                             << n << "& rhs) ";

            helper_->utility().open_scope(nl);
            helper_->stream() << "lhs.swap(rhs);" << std::endl;
        }
        helper_->utility().close_scope(nl);
        helper_->utility().blank_line();
    }
    helper_->utility().blank_line();
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
external_inserter(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    if (!reader.is_true(sml::tags::cpp::types::generate_external_inserter))
        return;

    helper_->stream() << "std::ostream& operator<<(std::ostream& s, "
                      << "const " << o.name().simple_name() << "& v);"
                      << std::endl;
    helper_->utility().managed_blank_line();
}

void cpp_types_main_header_file_formatter::
destructor_implementation(const sml::object& o) const {
    sml::meta_data_reader reader(o.meta_data());
    using types = sml::tags::cpp::types;
    if (!reader.is_true(types::generate_explicit_destructor))
        return;

    if (reader.is_true(sml::tags::cpp::types::destructor_is_pure_virtual)) {
        const auto sn(o.name().simple_name());
        helper_->stream() << "inline " << sn << "::~"<< sn << "() noexcept { }"
                         << std::endl;
        helper_->utility().managed_blank_line();
    }
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::enumeration& e) const {
    ensure_non_null_helper();

    BOOST_LOG_SEV(lg, debug) << "Formatting enumeration: " << e.name();
    {
        const auto ns(namespaces(e.name()));
        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();

        doxygen_next_.format(helper_->stream(), e.documentation());
        helper_->stream() << "enum class " << e.name().simple_name()
                         << " : unsigned int ";

        const auto nl(padding_types::new_line);
        helper_->utility().open_scope(nl);
        {
            positive_indenter_scope pis(helper_->stream());
            bool is_first(true);
            std::ostringstream assignment;
            std::ostringstream comment;
            for (const auto& enumerator : e.enumerators()) {
                if (!is_first) {
                    const auto c(comment.str());
                    helper_->stream() << assignment.str() << ",";
                    if (!c.empty())
                        helper_->stream() << " " << c;
                    assignment.str(empty);
                    comment.str(empty);
                }
                assignment << enumerator.name() << " = " << enumerator.value();
                doxygen_previous_.format(comment, e.documentation());
                is_first = false;
            }

            helper_->stream() << assignment.str();
            const auto c(comment.str());
            if (!c.empty())
                helper_->stream() << " " << c;
        }
        helper_->stream() << "};" << std::endl;
        helper_->utility().blank_line();
    }
    helper_->utility().blank_line();
    helper_->utility().managed_blank_line();
}


void cpp_types_main_header_file_formatter::
format_non_specialised_object(const sml::object& o) const {
    ensure_non_null_helper();
    {
        const auto ns(namespaces(o.name()));
        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();
        open_class(o);
        {
            positive_indenter_scope s(helper_->stream());
            explicitly_defaulted_functions(o);
            default_constructor(o);
            destructor(o);
            move_constructor(o);
            complete_constructor(o);
            friends(o);
            visitor_method(o);
            to_stream(o);
            getters_and_setters(o);
            internal_equality(o);
            internal_swap(o);
            internal_assignment(o);
            member_variables(o);
        }

        if (legacy_mode_) {
            if (o.local_properties().empty())
                helper_->utility().blank_line();
        }

        close_class();
        helper_->utility().blank_line();
        destructor_implementation(o);
        external_inserter(o);
        external_equality(o);
    }
    helper_->utility().blank_line();
    helper_->utility().managed_blank_line();
    external_swap(o);
}

void cpp_types_main_header_file_formatter::
visit(const dogen::sml::object& o) const {
    using sml::object_types;
    switch(o.object_type()) {
    case object_types::entity:
    case object_types::keyed_entity:
    case object_types::user_defined_value_object:
        format_non_specialised_object(o);
        break;

    default:
        return;
    }
}

bool cpp_types_main_header_file_formatter::
generate(const boost::property_tree::ptree& meta_data) const {
    sml::meta_data_reader reader(meta_data);
    const auto& gen(sml::tags::cpp::types::header_file::generate);
    return reader.is_true(gen);
}

file cpp_types_main_header_file_formatter::
format(const sml::module& module, const annotation& a) const {
    const auto md(module.meta_data());
    helper_ = std::make_shared<helper>(model_, md, a, legacy_mode_);
    helper_->format_begin();
    const auto ns(namespaces(module.name()));

    if (!ns.empty()) {

        cpp_formatters::namespace_helper nsh(helper_->stream(), ns);
        helper_->utility().blank_line();

        cpp_formatters::namespace_formatter nsf(helper_->stream());
        doxygen_next_.format(helper_->stream(), module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();

        helper_->stream() << " ";
    } else {
        cpp_formatters::namespace_formatter nsf(helper_->stream());
        doxygen_next_.format(helper_->stream(), module.documentation());
        nsf.format_start(module.name().simple_name());
        nsf.format_end();
    }
    helper_->utility().blank_line();
    helper_->utility().managed_blank_line();
    helper_->format_end();

    const file r(build_file(module.meta_data()));
    helper_ = std::shared_ptr<helper>();
    return r;
}

file cpp_types_main_header_file_formatter::
format(const sml::type& t, const annotation& a) const {
    helper_ = std::make_shared<helper>(model_, t.meta_data(), a, legacy_mode_);
    helper_->compute_includes(t);
    helper_->format_begin();
    t.accept(*this);
    helper_->format_end();

    const file r(build_file(t.meta_data()));
    helper_ = std::shared_ptr<helper>();
    return r;
}

} }
