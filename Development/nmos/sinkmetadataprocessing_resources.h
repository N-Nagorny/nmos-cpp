#ifndef NMOS_SINKMETADATAPROCESSING_RESOURCES_H
#define NMOS_SINKMETADATAPROCESSING_RESOURCES_H

#include "nmos/id.h"
#include "nmos/settings.h"

namespace nmos
{
    struct resource;

    web::json::value make_empty_media_profiles();

    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id);

    nmos::resource make_sinkmetadataprocessing_receiver(const nmos::id& id, const nmos::id& sink_id);

    // See https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/schemas/sink.json
    nmos::resource make_sink(const nmos::id& id, const web::json::value& edid, const utility::string_t& edid_bytes, const nmos::settings& settings);
    nmos::resource make_sink(const nmos::id& id, const utility::string_t& edid_bytes, const nmos::settings& settings);
}

#endif
