#include <map>
#include "nmos/format.h"
#include "nmos/json_fields.h"
#include "nmos/media_profiles.h"
#include "nmos/model.h"
#include "nmos/sdp_utils.h"

namespace nmos {
    namespace experimental {
        bool match_video_flow_media_profile(const web::json::value& video_flow, const web::json::value& media_profile)
        {
            using web::json::value;

            static const std::map<utility::string_t, std::function<bool(const web::json::value& flow, const value& val)>> match_constraints
            {
                { U("color_sampling"), [](const web::json::value& flow, const value& val) { return nmos::details::make_sampling(nmos::fields::components(flow)).name == val.as_string(); } },
                { U("component_depth"), [](const web::json::value& flow, const value& val) { return nmos::fields::bit_depth(nmos::fields::components(flow).at(0)) == val.as_integer(); } },
                { U("frame_width"), [](const web::json::value& flow, const value& val) { return nmos::fields::frame_width(flow) == val.as_integer(); } },
                { U("frame_height"), [](const web::json::value& flow, const value& val) { return nmos::fields::frame_height(flow) == val.as_integer(); } },
                { U("interlace_mode"), [](const web::json::value& flow, const value& val) { return nmos::fields::interlace_mode(flow) == val.as_string(); } },
                { U("grain_rate"), [](const web::json::value& flow, const value& val) { return nmos::fields::numerator(nmos::fields::grain_rate(flow)) == nmos::fields::numerator(val) && nmos::fields::denominator(nmos::fields::grain_rate(flow)) == nmos::fields::denominator(val); } },
                { U("media_type"), [](const web::json::value& flow, const value& val)
                {
                    const auto media_types = nmos::fields::media_types(flow).as_array();
                    const auto found = std::find(media_types.begin(), media_types.end(), val);
                    return media_types.end() != found;
                } }
            };

            const auto& media_params = media_profile.as_object();
            return media_params.end() == std::find_if(media_params.begin(), media_params.end(), [&](const std::pair<utility::string_t, value>& media_param)
            {
                const auto& found = match_constraints.find(media_param.first);
                return match_constraints.end() != found && !found->second(video_flow, media_param.second);
            });
        }

        bool match_audio_source_flow_media_profile(const web::json::value& audio_source, const web::json::value& audio_flow, const web::json::value& media_profile)
        {
            using web::json::value;

            auto flow_with_channels = audio_flow;
            nmos::fields::channels(flow_with_channels) = nmos::fields::channels(audio_source);

            static const std::map<utility::string_t, std::function<bool(const web::json::value&, const value&)>> match_constraints
            {
                { U("grain_rate"), [](const web::json::value& flow, const value& val) { return nmos::fields::numerator(nmos::fields::grain_rate(flow)) == nmos::fields::numerator(val) && nmos::fields::denominator(nmos::fields::grain_rate(flow)) == nmos::fields::denominator(val); } },
                { U("sample_rate"), [](const web::json::value& flow, const value& val) { return nmos::fields::sample_rate(flow) == val.as_integer(); } },
                { U("media_type"), [](const web::json::value& flow, const value& val)
                {
                    const auto media_types = nmos::fields::media_types(flow).as_array();
                    const auto found = std::find(media_types.begin(), media_types.end(), val);
                    return media_types.end() != found;
                } },
                { U("bit_depth"), [](const web::json::value& flow, const value& val) { return nmos::fields::bit_depth(flow) == val.as_integer(); } },
                { U("channel_count"), [](const web::json::value& source, const value& val) { return nmos::fields::channels(source).size() == val.as_integer(); } }
            };

            const auto& media_params = media_profile.as_object();
            return media_params.end() == std::find_if(media_params.begin(), media_params.end(), [&](const std::pair<utility::string_t, value>& media_param)
            {
                const auto& found = match_constraints.find(media_param.first);
                return match_constraints.end() != found && !found->second(flow_with_channels, media_param.second);
            });
        }
        bool match_media_profiles(nmos::node_model& model, const nmos::id& sender_id)
        {
            using web::json::value;

            auto& node_resources = model.node_resources;
            auto& sinkmetadataprocessing_resources = model.sinkmetadataprocessing_resources;

            auto sinkmetadataprocessing_sender = find_resource(sinkmetadataprocessing_resources, { sender_id, nmos::types::sender });
            if (sinkmetadataprocessing_sender == node_resources.end()) {
                throw std::logic_error("matching IS-11 Sender not found");
            }
            if (nmos::fields::media_profiles(sinkmetadataprocessing_sender->data) == value::array())
                return true;

            auto sender = find_resource(node_resources, { sender_id, nmos::types::sender });
            if (sender == node_resources.end()) {
                throw std::logic_error("matching IS-04 Sender not found");
            }
            auto flow = find_resource(node_resources, { nmos::fields::flow_id(sender->data).as_string(), nmos::types::flow });
            if (flow == node_resources.end()) {
                throw std::logic_error("matching IS-04 Flow not found");
            }
            auto source = find_resource(node_resources, { nmos::fields::source_id(flow->data), nmos::types::source });
            if (source == node_resources.end()) {
                throw std::logic_error("matching IS-04 Source not found");
            }

            auto media_profiles = nmos::fields::media_profiles(sinkmetadataprocessing_sender->data);
            if (nmos::fields::format(flow->data) == nmos::formats::video.name) {
                for (const auto& media_profile : media_profiles.as_array()) {
                    if (match_video_flow_media_profile(flow->data, media_profile)) {
                        return true;
                    }
                }
            } else if (nmos::fields::format(flow->data) == nmos::formats::audio.name) {
                for (const auto& media_profile : media_profiles.as_array()) {
                    if (match_audio_source_flow_media_profile(source->data, flow->data, media_profile)) {
                        return true;
                    }
                }
            }

            return false;
        }
    }
}