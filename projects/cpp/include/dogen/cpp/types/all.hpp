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
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/boost_model_helper.hpp"
#include "dogen/cpp/types/boost_types.hpp"
#include "dogen/cpp/types/dependency_details.hpp"
#include "dogen/cpp/types/dependency_extractor.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/formatters/class_declaration.hpp"
#include "dogen/cpp/types/formatters/class_implementation.hpp"
#include "dogen/cpp/types/formatters/domain_class_declaration.hpp"
#include "dogen/cpp/types/formatters/domain_class_implementation.hpp"
#include "dogen/cpp/types/formatters/domain_header.hpp"
#include "dogen/cpp/types/formatters/domain_implementation.hpp"
#include "dogen/cpp/types/formatters/doxygen_comments.hpp"
#include "dogen/cpp/types/formatters/enumeration_declaration.hpp"
#include "dogen/cpp/types/formatters/exception_declaration.hpp"
#include "dogen/cpp/types/formatters/facet_includer.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_header.hpp"
#include "dogen/cpp/types/formatters/generator_header.hpp"
#include "dogen/cpp/types/formatters/generator_implementation.hpp"
#include "dogen/cpp/types/formatters/hash_header.hpp"
#include "dogen/cpp/types/formatters/hash_implementation.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/inserter_implementation.hpp"
#include "dogen/cpp/types/formatters/io_header.hpp"
#include "dogen/cpp/types/formatters/io_implementation.hpp"
#include "dogen/cpp/types/formatters/key_class_declaration.hpp"
#include "dogen/cpp/types/formatters/key_class_implementation.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/null_formatter.hpp"
#include "dogen/cpp/types/formatters/odb_header.hpp"
#include "dogen/cpp/types/formatters/odb_options.hpp"
#include "dogen/cpp/types/formatters/production_failure.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/registrar_header.hpp"
#include "dogen/cpp/types/formatters/registrar_implementation.hpp"
#include "dogen/cpp/types/formatters/serialization_header.hpp"
#include "dogen/cpp/types/formatters/serialization_implementation.hpp"
#include "dogen/cpp/types/formatters/src_cmakelists.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/cpp/types/includer.hpp"
#include "dogen/cpp/types/location_request.hpp"
#include "dogen/cpp/types/locator.hpp"
#include "dogen/cpp/types/std_model_helper.hpp"
#include "dogen/cpp/types/std_types.hpp"
#include "dogen/cpp/types/view_models/class_view_model.hpp"
#include "dogen/cpp/types/view_models/cmakelists_view_model.hpp"
#include "dogen/cpp/types/view_models/enumeration_view_model.hpp"
#include "dogen/cpp/types/view_models/enumerator_view_model.hpp"
#include "dogen/cpp/types/view_models/exception_view_model.hpp"
#include "dogen/cpp/types/view_models/file_view_model.hpp"
#include "dogen/cpp/types/view_models/nested_type_view_model.hpp"
#include "dogen/cpp/types/view_models/odb_options_view_model.hpp"
#include "dogen/cpp/types/view_models/parent_view_model.hpp"
#include "dogen/cpp/types/view_models/property_view_model.hpp"
#include "dogen/cpp/types/view_models/registrar_view_model.hpp"
#include "dogen/cpp/types/view_models/sml_to_cpp_view_model.hpp"
#include "dogen/cpp/types/view_models/transformation_error.hpp"
#include "dogen/cpp/types/workflow.hpp"
#include "dogen/cpp/types/workflow_failure.hpp"
