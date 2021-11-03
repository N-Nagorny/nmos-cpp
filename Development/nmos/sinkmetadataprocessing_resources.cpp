#include "nmos/sinkmetadataprocessing_resources.h"

#include <boost/range/adaptor/filtered.hpp>
#include "cpprest/json_validator.h"
#include "edid/edid.h"
#include "nmos/api_utils.h"
#include "nmos/capabilities.h"
#include "nmos/is11_versions.h"
#include "nmos/json_schema.h"
#include "nmos/model.h"

namespace nmos
{
    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id, const std::vector<nmos::id>& inputs, const std::vector<utility::string_t>& supported_param_cons)
    {
        using web::json::value;
        using web::json::value_of;
        using web::json::value_from_elements;

        std::vector<utility::string_t> effective_param_cons{
            nmos::caps::meta::label.key,
            nmos::caps::meta::preference.key,
            nmos::caps::meta::enabled.key,
            nmos::caps::format::media_type.key,
            nmos::caps::format::grain_rate.key,
            nmos::caps::format::frame_width.key,
            nmos::caps::format::frame_height.key,
            nmos::caps::format::interlace_mode.key,
            nmos::caps::format::colorspace.key,
            nmos::caps::format::color_sampling.key,
            nmos::caps::format::component_depth.key,
            nmos::caps::format::channel_count.key,
            nmos::caps::format::sample_rate.key,
            nmos::caps::format::sample_depth.key
        };

        effective_param_cons.insert(effective_param_cons.end(), supported_param_cons.begin(), supported_param_cons.end());

        auto data = value_of({
                { nmos::fields::id, id },
                { nmos::fields::device_id, U("these are not the droids you are looking for") },
                { nmos::fields::constraint_sets, value::array() },
                { nmos::fields::inputs, value_from_elements(inputs) },
                { nmos::fields::parameter_constraints, value_from_elements(effective_param_cons) },
        });

        return{ is11_versions::v1_0, types::sender, std::move(data), id, false };
    }

    nmos::resource make_sinkmetadataprocessing_receiver(const nmos::id& id, const std::vector<nmos::id>& outputs)
    {
        using web::json::value;
        using web::json::value_of;
        using web::json::value_from_elements;

        auto data = value_of({
                { nmos::fields::id, id },
                { nmos::fields::device_id, U("these are not the droids you are looking for") },
                { nmos::fields::outputs, value_from_elements(outputs) },
        });

        return{ is11_versions::v1_0, types::receiver, std::move(data), id, false };
    }

    nmos::resource make_io_item(const nmos::id& id, nmos::type type, const web::json::value& edid, const utility::string_t& edid_bytes, const nmos::settings& settings)
    {
        using web::json::value;
        using web::json::value_of;
        using web::json::value_from_elements;

        auto data = details::make_resource_core(id, settings);
        insert(data, std::begin(edid.as_object()), std::end(edid.as_object()));

        data[U("edid_binary")] = value::string(edid_bytes);

        return{ is11_versions::v1_0, type, std::move(data), id, false };
    }

    nmos::resource make_io_item(const nmos::id& id, nmos::type type, const utility::string_t& edid_bytes, const nmos::settings& settings)
    {
        return make_io_item(id, type, edid::parse_edid(edid_bytes), edid_bytes, settings);
    }
}
