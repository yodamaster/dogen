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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_PROPERTIES_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/serialization/decoration_properties_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Configuration pertaining to file decoration.
 */
class decoration_properties final {
public:
    decoration_properties(const decoration_properties&) = default;
    ~decoration_properties() = default;

public:
    decoration_properties();

public:
    decoration_properties(decoration_properties&& rhs);

public:
    decoration_properties(
        const bool generate_decoration,
        const boost::optional<dogen::formatters::modeline>& modeline,
        const boost::optional<dogen::formatters::licence>& licence,
        const std::string& code_generation_marker);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::decoration_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::decoration_properties& v, unsigned int version);

public:
    /**
     * @brief If set to true, the decoration will be generated.
     */
    /**@{*/
    bool generate_decoration() const;
    void generate_decoration(const bool v);
    /**@}*/

    /**
     * @brief Modeline to use in this file, if any.
     */
    /**@{*/
    const boost::optional<dogen::formatters::modeline>& modeline() const;
    boost::optional<dogen::formatters::modeline>& modeline();
    void modeline(const boost::optional<dogen::formatters::modeline>& v);
    void modeline(const boost::optional<dogen::formatters::modeline>&& v);
    /**@}*/

    /**
     * @brief Licence to use in this file, if any.
     */
    /**@{*/
    const boost::optional<dogen::formatters::licence>& licence() const;
    boost::optional<dogen::formatters::licence>& licence();
    void licence(const boost::optional<dogen::formatters::licence>& v);
    void licence(const boost::optional<dogen::formatters::licence>&& v);
    /**@}*/

    /**
     * @brief Code generation marker to use in this file.
     */
    /**@{*/
    const std::string& code_generation_marker() const;
    std::string& code_generation_marker();
    void code_generation_marker(const std::string& v);
    void code_generation_marker(const std::string&& v);
    /**@}*/

public:
    bool operator==(const decoration_properties& rhs) const;
    bool operator!=(const decoration_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_properties& other) noexcept;
    decoration_properties& operator=(decoration_properties other);

private:
    bool generate_decoration_;
    boost::optional<dogen::formatters::modeline> modeline_;
    boost::optional<dogen::formatters::licence> licence_;
    std::string code_generation_marker_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::decoration_properties& lhs,
    dogen::formatters::decoration_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
