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
#include "dogen/yarn/test_data/languages_td.hpp"
#include "dogen/yarn/test_data/intermediate_model_td.hpp"
#include "dogen/yarn/test_data/intermediate_model_repository_td.hpp"

namespace {

dogen::yarn::languages
create_dogen_yarn_languages(const unsigned int position) {
    return dogen::yarn::languages_generator::create(position);
}

dogen::yarn::intermediate_model
create_dogen_yarn_intermediate_model(const unsigned int position) {
    return dogen::yarn::intermediate_model_generator::create(position);
}

std::list<dogen::yarn::intermediate_model> create_std_list_dogen_yarn_intermediate_model(unsigned int position) {
    std::list<dogen::yarn::intermediate_model> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_intermediate_model(position + i));
    }
    return r;
}

std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> > create_std_unordered_map_dogen_yarn_languages_std_list_dogen_yarn_intermediate_model(unsigned int position) {
    std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_languages(position + i), create_std_list_dogen_yarn_intermediate_model(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

intermediate_model_repository_generator::intermediate_model_repository_generator() : position_(0) { }

void intermediate_model_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_language(create_std_unordered_map_dogen_yarn_languages_std_list_dogen_yarn_intermediate_model(position + 0));
}

intermediate_model_repository_generator::result_type
intermediate_model_repository_generator::create(const unsigned int position) {
    intermediate_model_repository r;
    intermediate_model_repository_generator::populate(position, r);
    return r;
}

intermediate_model_repository_generator::result_type*
intermediate_model_repository_generator::create_ptr(const unsigned int position) {
    intermediate_model_repository* p = new intermediate_model_repository();
    intermediate_model_repository_generator::populate(position, *p);
    return p;
}

intermediate_model_repository_generator::result_type
intermediate_model_repository_generator::operator()() {
    return create(position_++);
}

} }
