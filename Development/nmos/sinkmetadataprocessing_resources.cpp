#include "nmos/sinkmetadataprocessing_resources.h"

#include <boost/range/adaptor/filtered.hpp>
#include "cpprest/json_validator.h"
#include "edid/edid.h"
#include "nmos/api_utils.h"
#include "nmos/is11_versions.h"
#include "nmos/json_schema.h"
#include "nmos/model.h"

namespace nmos
{
    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id, const std::vector<nmos::id>& inputs)
    {
        using web::json::value;
        using web::json::value_of;
        using web::json::value_from_elements;

        auto data = value_of({
                { nmos::fields::id, id },
                { nmos::fields::device_id, U("these are not the droids you are looking for") },
                { nmos::fields::media_profiles, make_empty_media_profiles() },
                { nmos::fields::inputs, value_from_elements(inputs) },
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

    web::json::value make_empty_media_profiles()
    {
        using web::json::value;

        return value::array();
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
