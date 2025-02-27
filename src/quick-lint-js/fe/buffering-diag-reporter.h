// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_FE_BUFFERING_DIAG_REPORTER_H
#define QUICK_LINT_JS_FE_BUFFERING_DIAG_REPORTER_H

#include <boost/container/pmr/memory_resource.hpp>
#include <memory>
#include <quick-lint-js/fe/diag-reporter.h>
#include <quick-lint-js/fe/diagnostic-types.h>
#include <quick-lint-js/fe/token.h>

namespace quick_lint_js {
class buffering_diag_reporter final : public diag_reporter {
 public:
  explicit buffering_diag_reporter(boost::container::pmr::memory_resource *);

  buffering_diag_reporter(buffering_diag_reporter &&);
  buffering_diag_reporter &operator=(buffering_diag_reporter &&);

  ~buffering_diag_reporter() override;

  void report_impl(diag_type type, void *diag) override;

  void copy_into(diag_reporter *other) const;
  void move_into(diag_reporter *other);

  bool empty() const noexcept;

  void clear() noexcept;

 private:
  struct impl;

  struct impl_deleter {
    void operator()(impl *) noexcept;
  };

  std::unique_ptr<impl, impl_deleter> impl_;
};
}

#endif

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
