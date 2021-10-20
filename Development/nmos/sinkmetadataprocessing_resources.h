#ifndef NMOS_SINKMETADATAPROCESSING_RESOURCES_H
#define NMOS_SINKMETADATAPROCESSING_RESOURCES_H

#include "nmos/id.h"
#include "nmos/settings.h"
#include "nmos/type.h"

namespace nmos
{
    struct resource;

    web::json::value make_empty_media_profiles();

    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id, const std::vector<nmos::id>& inputs);

    nmos::resource make_sinkmetadataprocessing_receiver(const nmos::id& id, const std::vector<nmos::id>& outputs);

    // See https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/schemas/input.json
    // and https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/schemas/output.json
    nmos::resource make_io_item(const nmos::id& id, nmos::type type, const web::json::value& edid, const utility::string_t& edid_bytes, const nmos::settings& settings);
    nmos::resource make_io_item(const nmos::id& id, nmos::type type, const utility::string_t& edid_bytes, const nmos::settings& settings);
}

#endif
