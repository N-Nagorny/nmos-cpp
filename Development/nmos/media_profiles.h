#ifndef NMOS_MEDIA_PROFILES_H
#define NMOS_MEDIA_PROFILES_H

#include "cpprest/json_ops.h" // for web::json::value, web::json::as, etc.
#include "nmos/model.h"

namespace nmos
{
    struct node_model;

    namespace experimental
    {
        bool match_video_flow_media_profile(const web::json::value& video_flow, const web::json::value& media_profile);
        bool match_audio_source_flow_media_profile(const web::json::value& audio_source, const web::json::value& audio_flow, const web::json::value& media_profile);
        bool match_media_profiles(nmos::node_model& model, const nmos::id& sender_id);
    }
}

#endif
