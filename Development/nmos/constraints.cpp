#include <map>
#include "nmos/capabilities.h"
#include "nmos/constraints.h"
#include "nmos/json_fields.h"
#include "nmos/sdp_utils.h"

namespace nmos
{
    namespace experimental
    {
        bool match_source_parameters_constraint_set(const web::json::value& source, const web::json::value& constraint_set)
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

        bool match_flow_parameters_constraint_set(const web::json::value& flow, const web::json::value& constraint_set)
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

        template <typename Parse>
        bool is_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint, Parse parse)
        {
            // subconstraint should have enum if constraint has enum
            if (constraint.has_field(nmos::fields::constraint_enum) && !subconstraint.has_field(nmos::fields::constraint_enum))
            {
                return false;
            }
            // subconstraint should have minimum or enum if constraint has minimum
            if (constraint.has_field(nmos::fields::constraint_minimum) && !subconstraint.has_field(nmos::fields::constraint_enum) && !subconstraint.has_field(nmos::fields::constraint_minimum))
            {
                return false;
            }
            // subconstraint should have maximum or enum if constraint has maximum
            if (constraint.has_field(nmos::fields::constraint_maximum) && !subconstraint.has_field(nmos::fields::constraint_enum) && !subconstraint.has_field(nmos::fields::constraint_maximum))
            {
                return false;
            }
            if (constraint.has_field(nmos::fields::constraint_minimum) && subconstraint.has_field(nmos::fields::constraint_minimum))
            {
                const auto& constraint_minimum = nmos::fields::constraint_minimum(constraint);
                const auto& subconstraint_minimum = nmos::fields::constraint_minimum(subconstraint);
                if (parse(constraint_minimum) > parse(subconstraint_minimum))
                {
                    return false;
                }
            }
            if (constraint.has_field(nmos::fields::constraint_maximum) && subconstraint.has_field(nmos::fields::constraint_maximum))
            {
                const auto& constraint_maximum = nmos::fields::constraint_maximum(constraint);
                const auto& subconstraint_maximum = nmos::fields::constraint_maximum(subconstraint);
                if (parse(constraint_maximum) < parse(subconstraint_maximum))
                {
                    return false;
                }
            }

            // subconstraint enum values should match constraint
            const auto& subconstraint_enum_values = nmos::fields::constraint_enum(subconstraint).as_array();
            if (subconstraint_enum_values.end() == std::find_if(subconstraint_enum_values.begin(), subconstraint_enum_values.end(), [&parse, &constraint](const web::json::value& enum_value)
            {
                return details::match_constraint(parse(enum_value), constraint, parse);
            }))
            {
                return false;
            }
            return true;
        }

        bool is_string_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint)
        {
            return is_subconstraint(constraint, subconstraint, [](const web::json::value& enum_value)
            {
                return enum_value.as_string();
            });
        }

        bool is_integer_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint)
        {
            return is_subconstraint(constraint, subconstraint, [](const web::json::value& enum_value)
            {
                return enum_value.as_integer();
            });
        }

        bool is_number_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint)
        {
            return is_subconstraint(constraint, subconstraint, [](const web::json::value& enum_value)
            {
                return enum_value.as_double();
            });
        }

        bool is_boolean_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint)
        {
            return is_subconstraint(constraint, subconstraint, [](const web::json::value& enum_value)
            {
                return enum_value.as_bool();
            });
        }

        bool is_rational_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint)
        {
            return is_subconstraint(constraint, subconstraint, [](const web::json::value& enum_value)
            {
                return nmos::parse_rational(enum_value);
            });
        }

#define CAPS_ARGS const web::json::value& constraint, const web::json::value& subconstraint
        static const std::map<utility::string_t, std::function<bool(CAPS_ARGS)>> format_constraints
        {
            // General Constraints

            { nmos::caps::format::media_type, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
            // hm, how best to match (rational) nmos::caps::format::grain_rate against (double) framerate e.g. for video/SMPTE2022-6?
            // is 23.976 a match for 24000/1001? how about 23.98, or 23.9? or even 23?!
            { nmos::caps::format::grain_rate, [](CAPS_ARGS) { return is_rational_subconstraint(constraint, subconstraint); } },

            // Video Constraints

            { nmos::caps::format::frame_height, [](CAPS_ARGS) { return is_integer_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::frame_width, [](CAPS_ARGS) { return is_integer_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::color_sampling, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::interlace_mode, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::colorspace, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::transfer_characteristic, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::component_depth, [](CAPS_ARGS) { return is_integer_subconstraint(constraint, subconstraint); } },

            // Audio Constraints

            { nmos::caps::format::channel_count, [](CAPS_ARGS) { return is_integer_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::sample_rate, [](CAPS_ARGS) { return is_rational_subconstraint(constraint, subconstraint); } },
            { nmos::caps::format::sample_depth, [](CAPS_ARGS) { return is_integer_subconstraint(constraint, subconstraint); } },

            // Transport Constraints

            { nmos::caps::transport::packet_time, [](CAPS_ARGS) { return is_number_subconstraint(constraint, subconstraint); } },
            { nmos::caps::transport::max_packet_time, [](CAPS_ARGS) { return is_number_subconstraint(constraint, subconstraint); } },
            { nmos::caps::transport::st2110_21_sender_type, [](CAPS_ARGS) { return is_string_subconstraint(constraint, subconstraint); } },
        };
#undef CAPS_ARGS

        bool is_constraint_subset(const web::json::value& constraint_set, const web::json::value& constraint_subset)
        {
            using web::json::value;

            if (!nmos::caps::meta::enabled(constraint_subset)) return true;

            const auto& param_constraints_set = constraint_set.as_object();
            const auto& param_constraints_subset = constraint_subset.as_object();

            return param_constraints_subset.end() == std::find_if(param_constraints_subset.begin(), param_constraints_subset.end(), [&](const std::pair<utility::string_t, value>& subconstraint)
            {
                if (subconstraint.first == nmos::caps::meta::label.key || subconstraint.first == nmos::caps::meta::preference.key) return false;

                const auto& found = format_constraints.find(subconstraint.first);
                const auto& constraint = param_constraints_set.find(subconstraint.first);
                return param_constraints_set.end() == constraint || (found != format_constraints.end() && !found->second(constraint->second, subconstraint.second));
            });
        }
    }
}