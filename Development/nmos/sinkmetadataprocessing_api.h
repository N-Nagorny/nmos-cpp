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
        web::http::experimental::listener::api_router make_sinkmetadataprocessing_api(nmos::node_model& model, slog::base_gate& gate);
    }
}

#endif
