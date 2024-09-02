#pragma once

#include "actions/find.hpp"
#include "actions/iterate.hpp"
#include "actions/eval.hpp"
#include "actions/expand.hpp"

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/eigen.hpp>
#include <boost/program_options.hpp>

namespace mp = boost::multiprecision;
namespace po = boost::program_options;

namespace polyquad {
template <template <typename> class Domain, typename T>
void process_dispatch(const po::variables_map& vm) {
  const std::string& action = vm["action"].as<std::string>();

  if (action == "find")
    process_find<Domain, T>(vm);
  else if (action == "iterate")
    process_iterate<Domain, T>(vm);
  else if (action == "eval")
    process_eval<Domain, T>(vm);
  else if (action == "expand")
    process_expand<Domain, T>(vm);
}

using shape_key = std::pair<std::string, std::string>;
using process_fn = void (*)(const po::variables_map&);

}  // namespace polyquad