#ifndef NMOS_SINKMETADATAPROCESSING_API_H
#define NMOS_SINKMETADATAPROCESSING_API_H

#include "nmos/api_utils.h"
#include "nmos/slog.h"

// Sink Metadata Processing API implementation
// See https://github.com/AMWA-TV/nmos-sink-metadata-processing/blob/v1.0-dev/APIs/SinkMetadataProcessingAPI.raml
namespace nmos
{
    struct node_model;

    namespace experimental
    {
        namespace details
        {
            typedef std::function<void(const nmos::id& sender_id, const web::json::value& media_profiles, slog::base_gate& gate)> sinkmetadataprocessing_media_profiles_handler;
        }

        web::http::experimental::listener::api_router make_sinkmetadataprocessing_api(nmos::node_model& model, details::sinkmetadataprocessing_media_profiles_handler media_profiles_handler, slog::base_gate& gate);
    }
}

#endif
