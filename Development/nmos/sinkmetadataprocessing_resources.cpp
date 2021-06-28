#include "nmos/sinkmetadataprocessing_resources.h"

#include <boost/range/adaptor/filtered.hpp>
#include "cpprest/json_validator.h"
#include "nmos/api_utils.h"
#include "nmos/is11_versions.h"
#include "nmos/json_schema.h"
#include "nmos/model.h"

namespace nmos
{
    nmos::resource make_sinkmetadataprocessing_sender(const nmos::id& id)
    {
        using web::json::value;
        using web::json::value_of;

        auto data = value_of({
                { nmos::fields::id, id },
                { nmos::fields::device_id, U("these are not the droids you are looking for") },
                { nmos::fields::media_profiles, make_empty_media_profiles() }
        });

        return{ is11_versions::v1_0, types::sender, std::move(data), id, false };
    }

    nmos::resource make_sinkmetadataprocessing_receiver(const nmos::id& id)
    {
        using web::json::value;
        using web::json::value_of;

        auto data = value_of({
                { nmos::fields::id, id },
                { nmos::fields::device_id, U("these are not the droids you are looking for") }
        });

        return{ is11_versions::v1_0, types::receiver, std::move(data), id, false };
    }

    web::json::value make_empty_media_profiles()
    {
        using web::json::value;

        return value::array();
    }

    nmos::resource make_sink(const nmos::id& id, const nmos::id& receiver_id, const web::json::value& edid, const utility::string_t& edid_bytes, const nmos::settings& settings)
    {
        using web::json::value;
        using web::json::value_of;

        auto data = details::make_resource_core(id, settings);
        data[U("edid")] = edid;
        data[U("edid_binary")] = value::string(edid_bytes);
        data[U("receiver_id")] = value::string(receiver_id);

        return{ is11_versions::v1_0, types::sink, std::move(data), id, false };
    }

    nmos::resource make_sink(const nmos::id& id, const nmos::id& receiver_id, const utility::string_t& edid_bytes, const nmos::settings& settings)
    {
        using web::json::value;
        using web::json::value_of;

        auto data = details::make_resource_core(id, settings);
        data[U("edid")] = edid::parse_edid(edid_bytes);
        data[U("edid_binary")] = value::string(edid_bytes);
        data[U("receiver_id")] = value::string(receiver_id);

        return{ is11_versions::v1_0, types::sink, std::move(data), id, false };
    }
}
