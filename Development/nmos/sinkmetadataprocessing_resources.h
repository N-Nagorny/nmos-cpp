#ifndef NMOS_SINKMETADATAPROCESSING_RESOURCES_H
#define NMOS_SINKMETADATAPROCESSING_RESOURCES_H

#include "nmos/id.h"
#include "nmos/rational.h"
#include "nmos/settings.h"
#include "sdp/json.h"

namespace nmos
{
    typedef web::json::value edid;

    struct resource;

    struct edid_timing { nmos::rational frame_rate; unsigned int frame_width; unsigned int frame_height; };

    web::json::value make_empty_media_profiles();

    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id);

    nmos::resource make_sinkmetadataprocessing_receiver(const nmos::id& id);

    // See https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/schemas/sink.json
    nmos::resource make_sink(const nmos::id& id, const nmos::id& receiver_id, const nmos::edid& edid, const web::json::value& edid_bytes, const nmos::settings& settings);

    // See https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/schemas/edid.json
    nmos::edid make_edid(
        utility::string_t manufacturer,
        unsigned int manufacturer_week,
        unsigned int manufacturer_year,
        unsigned int screen_width,
        unsigned int screen_height,
        float gamma,
        std::vector<sdp::sampling> display_type,
        std::vector<edid_timing> established_timings,
        std::vector<edid_timing> standard_timings,
        std::vector<edid_timing> detailed_timings,
        std::vector<edid_timing> cta_861_timings
    );
}

#endif
