#include <map>
#include "nmos/capabilities.h"
#include "nmos/components.h"
#include "nmos/format.h"
#include "nmos/json_fields.h"
#include "nmos/constraints.h"
#include "nmos/model.h"
#include "nmos/sdp_utils.h"

namespace nmos {
    namespace experimental {
        bool match_source_constraint_set(const web::json::value& source, const web::json::value& constraint_set)
        {
            using web::json::value;

            if (!nmos::caps::meta::enabled(constraint_set)) return true;

            // NMOS Parameter Registers - Capabilities register
            // See https://github.com/AMWA-TV/nmos-parameter-registers/blob/main/capabilities/README.md
            static const std::map<utility::string_t, std::function<bool(const web::json::value& source, const value& con)>> match_constraints
            {
                // Audio Constraints

                { nmos::caps::format::channel_count, [](const web::json::value& source, const value& con) { return nmos::match_integer_constraint((uint32_t)nmos::fields::channels(source).size(), con); } }
            };

            const auto& constraints = constraint_set.as_object();
            return constraints.end() == std::find_if(constraints.begin(), constraints.end(), [&](const std::pair<utility::string_t, value>& constraint)
            {
                const auto& found = match_constraints.find(constraint.first);
                return match_constraints.end() != found && !found->second(source, constraint.second);
            });
        }

        bool match_flow_constraint_set(const web::json::value& flow, const web::json::value& constraint_set)
        {
            using web::json::value;

            if (!nmos::caps::meta::enabled(constraint_set)) return true;

            // NMOS Parameter Registers - Capabilities register
            // See https://github.com/AMWA-TV/nmos-parameter-registers/blob/main/capabilities/README.md
            static const std::map<utility::string_t, std::function<bool(const web::json::value& flow, const value& con)>> match_constraints
            {
                // General Constraints

                { nmos::caps::format::media_type, [](const web::json::value& flow, const value& con) { return nmos::match_string_constraint(flow.at(U("media_type")).as_string(), con); } },
                { nmos::caps::format::grain_rate, [](const web::json::value& flow, const value& con) {
                    auto grain_rate = nmos::rational(nmos::fields::numerator(nmos::fields::grain_rate(flow)), nmos::fields::denominator(nmos::fields::grain_rate(flow)));
                    return nmos::match_rational_constraint(grain_rate, con); }
                },

                // Video Constraints

                { nmos::caps::format::frame_height, [](const web::json::value& flow, const value& con) { return nmos::match_integer_constraint(nmos::fields::frame_height(flow), con); } },
                { nmos::caps::format::frame_width, [](const web::json::value& flow, const value& con) { return nmos::match_integer_constraint(nmos::fields::frame_width(flow), con); } },
                { nmos::caps::format::color_sampling, [](const web::json::value& flow, const value& con) { return nmos::match_string_constraint(nmos::details::make_sampling(nmos::fields::components(flow)).name, con); } },
                { nmos::caps::format::interlace_mode, [](const web::json::value& flow, const value& con) { return nmos::match_string_constraint(nmos::fields::interlace_mode(flow), con); } },
                { nmos::caps::format::colorspace, [](const web::json::value& flow, const value& con) { return nmos::match_string_constraint(nmos::fields::colorspace(flow), con); } },
                { nmos::caps::format::transfer_characteristic, [](const web::json::value& flow, const value& con) { return nmos::match_string_constraint(nmos::fields::transfer_characteristic(flow), con); } },
                { nmos::caps::format::component_depth, [](const web::json::value& flow, const value& con) { return nmos::match_integer_constraint(nmos::fields::bit_depth(nmos::fields::components(flow).at(0)), con); } },

                // Audio Constraints

                { nmos::caps::format::sample_rate, [](const web::json::value& flow, const value& con) {
                    auto sample_rate = nmos::rational(nmos::fields::numerator(nmos::fields::sample_rate(flow)), nmos::fields::denominator(nmos::fields::sample_rate(flow)));
                    return nmos::match_rational_constraint(sample_rate, con); }
                },
                { nmos::caps::format::sample_depth, [](const web::json::value& flow, const value& con) { return nmos::match_integer_constraint(nmos::fields::bit_depth(flow), con); } },
            };

            const auto& constraints = constraint_set.as_object();
            return constraints.end() == std::find_if(constraints.begin(), constraints.end(), [&](const std::pair<utility::string_t, value>& constraint)
            {
                const auto& found = match_constraints.find(constraint.first);
                return match_constraints.end() != found && !found->second(flow, constraint.second);
            });
        }

        bool match_source_and_flow_constraint_sets(const web::json::value& source, const web::json::value& flow, const web::json::value& constraint_sets)
        {
            for (const auto& constraint_set : constraint_sets.as_array()) {
                if (match_source_constraint_set(source, constraint_set) &&
                    match_flow_constraint_set(flow, constraint_set)) {
                        return true;
                }
            }
            return false;
        }

        bool match_sender_constraint_sets(nmos::node_model& model, const nmos::id& sender_id)
        {
            using web::json::value;

            auto& node_resources = model.node_resources;
            auto& sinkmetadataprocessing_resources = model.sinkmetadataprocessing_resources;

            auto sinkmetadataprocessing_sender = find_resource(sinkmetadataprocessing_resources, { sender_id, nmos::types::sender });
            if (sinkmetadataprocessing_sender == node_resources.end()) {
                throw std::logic_error("matching IS-11 Sender not found");
            }

            auto constraint_sets = nmos::fields::constraint_sets(sinkmetadataprocessing_sender->data);
            if (constraint_sets.as_array().size() == 0)
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

            return match_source_and_flow_constraint_sets(source->data, flow->data, constraint_sets);
        }
    }
}
