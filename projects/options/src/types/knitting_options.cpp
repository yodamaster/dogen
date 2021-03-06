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
#include "dogen/options/types/knitting_options.hpp"

namespace dogen {
namespace options {

knitting_options::knitting_options()
    : delete_extra_files_(static_cast<bool>(0)),
      force_write_(static_cast<bool>(0)) { }

knitting_options::knitting_options(knitting_options&& rhs)
    : log_level_(std::move(rhs.log_level_)),
      target_(std::move(rhs.target_)),
      delete_extra_files_(std::move(rhs.delete_extra_files_)),
      force_write_(std::move(rhs.force_write_)),
      ignore_patterns_(std::move(rhs.ignore_patterns_)),
      output_directory_path_(std::move(rhs.output_directory_path_)) { }

knitting_options::knitting_options(
    const std::string& log_level,
    const boost::filesystem::path& target,
    const bool delete_extra_files,
    const bool force_write,
    const std::vector<std::string>& ignore_patterns,
    const boost::filesystem::path& output_directory_path)
    : log_level_(log_level),
      target_(target),
      delete_extra_files_(delete_extra_files),
      force_write_(force_write),
      ignore_patterns_(ignore_patterns),
      output_directory_path_(output_directory_path) { }

void knitting_options::swap(knitting_options& other) noexcept {
    using std::swap;
    swap(log_level_, other.log_level_);
    swap(target_, other.target_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(force_write_, other.force_write_);
    swap(ignore_patterns_, other.ignore_patterns_);
    swap(output_directory_path_, other.output_directory_path_);
}

bool knitting_options::operator==(const knitting_options& rhs) const {
    return log_level_ == rhs.log_level_ &&
        target_ == rhs.target_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        force_write_ == rhs.force_write_ &&
        ignore_patterns_ == rhs.ignore_patterns_ &&
        output_directory_path_ == rhs.output_directory_path_;
}

knitting_options& knitting_options::operator=(knitting_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& knitting_options::log_level() const {
    return log_level_;
}

std::string& knitting_options::log_level() {
    return log_level_;
}

void knitting_options::log_level(const std::string& v) {
    log_level_ = v;
}

void knitting_options::log_level(const std::string&& v) {
    log_level_ = std::move(v);
}

const boost::filesystem::path& knitting_options::target() const {
    return target_;
}

boost::filesystem::path& knitting_options::target() {
    return target_;
}

void knitting_options::target(const boost::filesystem::path& v) {
    target_ = v;
}

void knitting_options::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
}

bool knitting_options::delete_extra_files() const {
    return delete_extra_files_;
}

void knitting_options::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
}

bool knitting_options::force_write() const {
    return force_write_;
}

void knitting_options::force_write(const bool v) {
    force_write_ = v;
}

const std::vector<std::string>& knitting_options::ignore_patterns() const {
    return ignore_patterns_;
}

std::vector<std::string>& knitting_options::ignore_patterns() {
    return ignore_patterns_;
}

void knitting_options::ignore_patterns(const std::vector<std::string>& v) {
    ignore_patterns_ = v;
}

void knitting_options::ignore_patterns(const std::vector<std::string>&& v) {
    ignore_patterns_ = std::move(v);
}

const boost::filesystem::path& knitting_options::output_directory_path() const {
    return output_directory_path_;
}

boost::filesystem::path& knitting_options::output_directory_path() {
    return output_directory_path_;
}

void knitting_options::output_directory_path(const boost::filesystem::path& v) {
    output_directory_path_ = v;
}

void knitting_options::output_directory_path(const boost::filesystem::path&& v) {
    output_directory_path_ = std::move(v);
}

} }
