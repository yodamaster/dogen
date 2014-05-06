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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/config/io/annotation_settings_io.hpp"
#include "dogen/config/io/cpp_settings_io.hpp"
#include "dogen/config/io/modeling_settings_io.hpp"
#include "dogen/config/io/output_settings_io.hpp"
#include "dogen/config/io/settings_io.hpp"
#include "dogen/config/io/troubleshooting_settings_io.hpp"

namespace dogen {
namespace config {

std::ostream& operator<<(std::ostream& s, const settings& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::config::settings\"" << ", "
      << "\"modeling\": " << v.modeling() << ", "
      << "\"cpp\": " << v.cpp() << ", "
      << "\"troubleshooting\": " << v.troubleshooting() << ", "
      << "\"output\": " << v.output() << ", "
      << "\"annotation\": " << v.annotation() << ", "
      << "\"verbose\": " << v.verbose()
      << " }";
    return(s);
}

} }