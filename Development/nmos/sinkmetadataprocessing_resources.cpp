#include "nmos/sinkmetadataprocessing_resources.h"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
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

    web::json::value make_empty_media_profiles()
    {
        using web::json::value;

        return value::array();
    }

    nmos::resource make_sink(const nmos::id& id, const nmos::edid& edid, const nmos::settings& settings)
    {
        using web::json::value;
        using web::json::value_of;

        auto data = details::make_resource_core(id, settings);
        data[U("edid")] = edid;

        return{ is11_versions::v1_0, types::sink, std::move(data), id, false };
    }

    web::json::value make_edid_timing(const edid_timing& timing) {
        using web::json::value;
        using web::json::value_of;

        return value_of({
            { U("frame_rate"), nmos::make_rational(timing.frame_rate) },
            { U("width"), timing.frame_width },
            { U("height"), timing.frame_height }
        });
    }

    nmos::edid make_edid(
        utility::string_t manufacturer,
        unsigned int manufacturer_week,
        unsigned int manufacturer_year,
        unsigned int screen_width,
        unsigned int screen_height,
        float gamma,
        std::vector<sdp::sampling> display_type,
        std::vector<edid_timing> established_timings,
        std::vector<edid_timing> standard_timings,
        std::vector<edid_timing> detailed_timings,
        std::vector<edid_timing> cta_861_timings
    )
    {
        using web::json::value;
        using web::json::value_of;

        value result = value_of({
            { U("manufacturer"), manufacturer },
            { U("manufacturer_week"), manufacturer_week },
            { U("manufacturer_year"), manufacturer_year },
            { U("screen_width"), screen_width },
            { U("screen_height"), screen_height },
            { U("gamma"), gamma }
        });

        auto& samplings = result[U("display_type")] = value::array();
        for (const auto& sampling : display_type)
        {
            web::json::push_back(samplings, sampling.name);
        }

        auto& established_timings_ = result[U("established_timings")] = value::array();
        for (const auto& timing : established_timings)
        {
            web::json::push_back(established_timings_, make_edid_timing(timing));
        }

        auto& standard_timings_ = result[U("standard_timings")] = value::array();
        for (const auto& timing : standard_timings)
        {
            web::json::push_back(standard_timings_, make_edid_timing(timing));
        }

        auto& detailed_timings_ = result[U("detailed_timings")] = value::array();
        for (const auto& timing : detailed_timings)
        {
            web::json::push_back(detailed_timings_, make_edid_timing(timing));
        }

        auto& cta_861_timings_ = result[U("cta_861_timings")] = value::array();
        for (const auto& timing : cta_861_timings)
        {
            web::json::push_back(cta_861_timings_, make_edid_timing(timing));
        }

        return result;
    }
}
