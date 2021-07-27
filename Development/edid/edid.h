#ifndef EDID_SDP_H
#define EDID_SDP_H

#include "nmos/rational.h" // for now, it depends on nmos
#include <kaitai_edid/edid.h>

namespace edid
{
    struct timing
    {
        timing(unsigned int frame_width, unsigned int frame_height, const nmos::rational& frame_rate)
            : frame_width_(frame_width)
            , frame_height_(frame_height)
            , frame_rate_(frame_rate)
            {}

        unsigned int frame_width_; unsigned int frame_height_; nmos::rational frame_rate_; };

    struct extended_timing : public timing
    {
        extended_timing(unsigned int frame_width, unsigned int frame_height, const nmos::rational& frame_rate, bool is_interlaced)
            : timing(frame_width, frame_height, frame_rate)
            , is_interlaced_(is_interlaced)
            {}

        bool is_interlaced_;
    };

    std::vector<timing> parse_standard_timings(std::vector<edid_t::std_timing_t*> std_timings_info);

    std::vector<extended_timing> parse_established_timings(edid_t::est_timings_info_t est_timings);

    std::vector<extended_timing> parse_detailed_timings(std::vector<edid_t::dtd_timing_t*> dtd_timings_info);

    web::json::value parse_edid(const utility::string_t& edid_bytes);
}

#endif
