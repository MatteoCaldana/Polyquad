#include "dispatcher_map.hpp"
#include "dispatcher_instances/instances.hpp"

namespace polyquad {
std::map<shape_key, process_fn> ShapeDispatcherMap::map = {
    {{"tri", "double"}, tri_double},
    // { {"quad", "double"}, &process_dispatch<QuadDomain, double> },
    // { {"hex",  "double"}, &process_dispatch<HexDomain,  double> },
    // { {"tet",  "double"}, &process_dispatch<TetDomain,  double> },
    // { {"pri",  "double"}, &process_dispatch<PriDomain,  double> },
    // { {"pyr",  "double"}, &process_dispatch<PyrDomain,  double> },
    // {{"tri", "bfloat"}, &process_dispatch<TriDomain, bfloat>},
    // { {"quad", "bfloat"}, &process_dispatch<QuadDomain, bfloat> },
    // { {"hex",  "bfloat"}, &process_dispatch<HexDomain,  bfloat> },
    // { {"tet",  "bfloat"}, &process_dispatch<TetDomain,  bfloat> },
    // { {"pri",  "bfloat"}, &process_dispatch<PriDomain,  bfloat> },
    // { {"pyr",  "bfloat"}, &process_dispatch<PyrDomain,  bfloat> },
};
}
