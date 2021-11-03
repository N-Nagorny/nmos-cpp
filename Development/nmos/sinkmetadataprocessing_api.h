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
            typedef std::function<void(const nmos::id& sender_id, const web::json::value& media_profiles, web::json::value& source, web::json::value& flow, slog::base_gate& gate)> sinkmetadataprocessing_media_profiles_patch_handler;
            typedef std::function<void(const nmos::id& sender_id, slog::base_gate& gate)> sinkmetadataprocessing_media_profiles_delete_handler;
            typedef std::function<bool(const nmos::id& sender_id, const web::json::value& media_profiles, slog::base_gate& gate)> sinkmetadataprocessing_constraints_validator;
        }

        web::http::experimental::listener::api_router make_sinkmetadataprocessing_api(nmos::node_model& model, details::sinkmetadataprocessing_media_profiles_patch_handler media_profiles_patch_handler, details::sinkmetadataprocessing_media_profiles_delete_handler media_profiles_delete_handler, nmos::experimental::details::sinkmetadataprocessing_constraints_validator constraints_validator, slog::base_gate& gate);
    }
}

#endif
