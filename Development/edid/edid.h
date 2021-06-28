#ifndef EDID_SDP_H
#define EDID_SDP_H

#include "nmos/rational.h" // for now, it depends on nmos
#include "third_party/kaitai_edid/edid.h"

namespace edid
{
    struct timing { unsigned int frame_width; unsigned int frame_height; nmos::rational frame_rate; };

    std::vector<timing> parse_standard_timings(std::vector<edid_t::std_timing_t*> std_timings_info);

    std::vector<timing> parse_established_timings(edid_t::est_timings_info_t est_timings_info);

    web::json::value parse_edid(const utility::string_t& edid_bytes);
}

#endif
