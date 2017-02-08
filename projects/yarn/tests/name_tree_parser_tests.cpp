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
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "../src/types/name_tree_parser_impl.hpp"

#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/languages.hpp"

/*
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/merging_error.hpp"
#include "dogen/yarn/types/name_tree_parser.hpp"
#include "dogen/yarn/types/merger.hpp"*/
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("yarn");
const std::string test_suite("name_tree_parser_tests");

const dogen::yarn::languages cpp(dogen::yarn::languages::cpp);

const auto top_level_modules = std::unordered_set<std::string>();
const auto model_location = dogen::yarn::location();



struct test_dummy_builder
{

};

bool applied = false;
name_tree_listener<test_dummy_builder> listener;

template<>
void name_tree_listener<test_dummy_builder>::apply()
{
    applied = true;
}

bool check_parse(const std::string & s)
{
    applied = false;
    grammar<std::string::const_iterator, test_dummy_builder> g(listener, cpp);

    std::string::const_iterator i(s.begin());
    std::string::const_iterator end(s.end());
    const bool ok(boost::spirit::qi::phrase_parse(i, end, g, ascii::space));

    return ok && (i != end);
}

}
using dogen::yarn::parsing_error;

BOOST_AUTO_TEST_SUITE(name_tree_parser_tests)

BOOST_AUTO_TEST_CASE(parsing_string_with_many_nested_scopes_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_many_nested_scopes_produces_expected_name");
 
    {
        custom_type_grammar<std::string::const_iterator, test_dummy_builder> ctg{&listener, cpp};
        
        listener.type_name.clear();
        std::string s = "abc";
        auto itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "abc");

        listener.type_name.clear();
        s = "a1::b2:: _c";
        itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "a1::b2::_c");

        listener.type_name.clear();
        s = "__a";
        itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "__a");

        s = "-a";
        itr = s.cbegin();
        BOOST_CHECK(!boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr != s.cend());

        s = "a::9::a";
        itr = s.cbegin();
        BOOST_CHECK(!boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr != s.cend());
    }
    BOOST_TEST_PASSPOINT();
    BOOST_CHECK(check_parse("a::b::c::z"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK(listener.type_name == "a::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);


}

/*
BOOST_AUTO_TEST_CASE(parsing_string_without_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_without_scope_operator_produces_expected_name");
    const std::string s("zeta");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_factory nf;
    const auto e(make(nf.build_element_name(s)));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_one_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_one_scope_operator_produces_expected_name");
    const std::string s("a::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_factory nf;
    const auto e(make(nf.build_element_name("a", "z")));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_colon_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_colon_fails_to_parse");
    const std::string s("a:z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(all_builtin_types_are_valid) {
    SETUP_TEST_LOG("all_builtin_types_are_valid");

    BOOST_CHECK(test_builtin("char"));
    BOOST_CHECK(test_builtin("unsigned char"));
    BOOST_CHECK(test_builtin("wchar_t"));
    BOOST_CHECK(test_builtin("unsigned wchar_t"));
    BOOST_CHECK(test_builtin("bool"));
    BOOST_CHECK(test_builtin("short"));
    BOOST_CHECK(test_builtin("unsigned short"));
    BOOST_CHECK(test_builtin("int"));
    BOOST_CHECK(test_builtin("unsigned int"));
    BOOST_CHECK(test_builtin("long"));
    BOOST_CHECK(test_builtin("unsigned long"));
    BOOST_CHECK(test_builtin("long long"));
    BOOST_CHECK(test_builtin("unsigned long long"));
    BOOST_CHECK(test_builtin("void"));
    BOOST_CHECK(test_builtin("float"));
    BOOST_CHECK(test_builtin("double"));
}

BOOST_AUTO_TEST_CASE(unsignable_types_cannot_be_unsigned) {
    SETUP_TEST_LOG("unsignable_types_cannot_be_unsigned");
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse("unsigned bool"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned x"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned float"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned double"), parsing_error);
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_template_argument_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("abc"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("type<abc>");
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_two_template_argument_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("abc"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("cde"));

    e.children(std::list<dogen::yarn::name_tree> { c, d });

    const std::string s("type<abc,cde>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_string_produces_expected_name_trees");
    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<std::string>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_builtin_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_builtin_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("unsigned int"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<unsigned int>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_unordered_map_produces_expected_name_trees");

    dogen::yarn::name_tree e;

    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "unordered_map"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("my", "type"));

    e.children(std::list<dogen::yarn::name_tree> { c, d });

    const std::string s1("std::unordered_map<std::string,my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s1;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a1(ntp.parse(s1));
    BOOST_CHECK(asserter::assert_equals(e, a1));

    const std::string s2("std::unordered_map<std::string,    my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s2;

    const auto a2(ntp.parse(s2));
    BOOST_CHECK(asserter::assert_equals(e, a2));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_shared_ptr_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "shared_ptr"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("std", "string"));

    c.children(std::list<dogen::yarn::name_tree> { d });
    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<std::shared_ptr<std::string>>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_builtins_produce_expected_name_tree) {
    SETUP_TEST_LOG("names_that_partially_match_builtins_produce_expected_name_tree");

    BOOST_CHECK(test_builtin("character"));
    BOOST_CHECK(test_builtin("cha"));
    BOOST_CHECK(test_builtin("wchar_test"));
    BOOST_CHECK(test_builtin("wcha"));
    BOOST_CHECK(test_builtin("boolean"));
    BOOST_CHECK(test_builtin("boo"));
    BOOST_CHECK(test_builtin("shorter"));
    BOOST_CHECK(test_builtin("shor"));
    BOOST_CHECK(test_builtin("integer"));
    BOOST_CHECK(test_builtin("in"));
    BOOST_CHECK(test_builtin("voidest"));
    BOOST_CHECK(test_builtin("voi"));
    BOOST_CHECK(test_builtin("floating"));
    BOOST_CHECK(test_builtin("floa"));
    BOOST_CHECK(test_builtin("doubler"));
    BOOST_CHECK(test_builtin("doubl"));
    BOOST_CHECK(test_builtin("unsigneder"));
    BOOST_CHECK(test_builtin("longer"));
}*/

BOOST_AUTO_TEST_SUITE_END()
