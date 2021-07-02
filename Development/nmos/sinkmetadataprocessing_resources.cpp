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
        // TODO (N-Nagorny): Replace it with more generalized code
        data[U("manufacturer")] = edid.at(U("manufacturer"));
        data[U("manufacture_week")] = edid.at(U("manufacture_week"));
        data[U("manufacture_year")] = edid.at(U("manufacture_year"));
        data[U("screen_size")] = edid.at(U("screen_size"));
        data[U("gamma")] = edid.at(U("gamma"));

        data[U("color_samplings")] = edid.at(U("color_samplings"));
        data[U("established_timings")] = edid.at(U("established_timings"));
        data[U("standard_timings")] = edid.at(U("standard_timings"));
        data[U("detailed_timings")] = edid.at(U("detailed_timings"));
        data[U("cta_861_timings")] = edid.at(U("cta_861_timings"));
        data[U("edid_binary")] = value::string(edid_bytes);
        data[U("receiver_id")] = value::string(receiver_id);

        return{ is11_versions::v1_0, types::sink, std::move(data), id, false };
    }

    nmos::resource make_sink(const nmos::id& id, const nmos::id& receiver_id, const utility::string_t& edid_bytes, const nmos::settings& settings)
    {
        return make_sink(id, receiver_id, edid::parse_edid(edid_bytes), edid_bytes, settings);
    }
}
