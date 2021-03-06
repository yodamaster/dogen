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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/name_tree_td.hpp"
#include "dogen/yarn/test_data/decomposition_result_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::pair<std::string, dogen::yarn::name>
create_std_pair_std_string_dogen_yarn_name(unsigned int position) {
    std::pair<std::string, dogen::yarn::name> r(
        create_std_string(position),
        create_dogen_yarn_name(position));
    return r;
}

std::list<std::pair<std::string, dogen::yarn::name> > create_std_list_std_pair_std_string_dogen_yarn_name(unsigned int position) {
    std::list<std::pair<std::string, dogen::yarn::name> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_dogen_yarn_name(position + i));
    }
    return r;
}

dogen::yarn::name_tree
create_dogen_yarn_name_tree(const unsigned int position) {
    return dogen::yarn::name_tree_generator::create(position);
}

std::pair<std::string, dogen::yarn::name_tree>
create_std_pair_std_string_dogen_yarn_name_tree(unsigned int position) {
    std::pair<std::string, dogen::yarn::name_tree> r(
        create_std_string(position),
        create_dogen_yarn_name_tree(position));
    return r;
}

std::list<std::pair<std::string, dogen::yarn::name_tree> > create_std_list_std_pair_std_string_dogen_yarn_name_tree(unsigned int position) {
    std::list<std::pair<std::string, dogen::yarn::name_tree> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_dogen_yarn_name_tree(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

decomposition_result_generator::decomposition_result_generator() : position_(0) { }

void decomposition_result_generator::
populate(const unsigned int position, result_type& v) {
    v.names(create_std_list_std_pair_std_string_dogen_yarn_name(position + 0));
    v.name_trees(create_std_list_std_pair_std_string_dogen_yarn_name_tree(position + 1));
}

decomposition_result_generator::result_type
decomposition_result_generator::create(const unsigned int position) {
    decomposition_result r;
    decomposition_result_generator::populate(position, r);
    return r;
}

decomposition_result_generator::result_type*
decomposition_result_generator::create_ptr(const unsigned int position) {
    decomposition_result* p = new decomposition_result();
    decomposition_result_generator::populate(position, *p);
    return p;
}

decomposition_result_generator::result_type
decomposition_result_generator::operator()() {
    return create(position_++);
}

} }
