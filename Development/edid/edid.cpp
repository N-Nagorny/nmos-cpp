#include "edid/edid.h"
#include "sdp/json.h"

namespace edid
{
    std::vector<timing> parse_standard_timings(std::vector<edid_t::std_timing_t*> std_timings_info) {
        std::vector<timing> result;
        for (edid_t::std_timing_t* std_timing_info : std_timings_info) {
            if (!std_timing_info->is_used())
                continue;

            edid_t::std_timing_t::aspect_ratios_t aspect = std_timing_info->aspect_ratio();
            double aspect_ratio = 0.0;
            if (aspect == edid_t::std_timing_t::aspect_ratios_t::ASPECT_RATIOS_RATIO_16_10) aspect_ratio = 16.0 / 10.0;
            else if (aspect == edid_t::std_timing_t::aspect_ratios_t::ASPECT_RATIOS_RATIO_4_3) aspect_ratio = 4.0 / 3.0;
            else if (aspect == edid_t::std_timing_t::aspect_ratios_t::ASPECT_RATIOS_RATIO_5_4) aspect_ratio = 5.0 / 4.0;
            else if (aspect == edid_t::std_timing_t::aspect_ratios_t::ASPECT_RATIOS_RATIO_16_9) aspect_ratio = 16.0 / 9.0;
            auto frame_width = std_timing_info->horiz_active_pixels();
            auto frame_height = frame_width / aspect_ratio;
            result.push_back({ frame_width, frame_height, nmos::rational(std_timing_info->refresh_rate(), 1)});
        }
        return result;
    }

    std::vector<timing> parse_established_timings(edid_t::est_timings_info_t est_timings_info) {
        std::vector<timing> established_timings;
        if (est_timings_info.can_720_400_70()) established_timings.push_back({720, 400, nmos::rational(70, 1)});
        if (est_timings_info.can_720_400_88()) established_timings.push_back({720, 400, nmos::rational(88, 1)});
        if (est_timings_info.can_640_480_60()) established_timings.push_back({640, 480, nmos::rational(60, 1)});
        if (est_timings_info.can_640_480_67()) established_timings.push_back({640, 480, nmos::rational(67, 1)});
        if (est_timings_info.can_640_480_72()) established_timings.push_back({640, 480, nmos::rational(72, 1)});
        if (est_timings_info.can_640_480_75()) established_timings.push_back({640, 480, nmos::rational(75, 1)});
        if (est_timings_info.can_800_600_56()) established_timings.push_back({800, 600, nmos::rational(56, 1)});
        if (est_timings_info.can_800_600_60()) established_timings.push_back({800, 600, nmos::rational(60, 1)});
        if (est_timings_info.can_800_600_72()) established_timings.push_back({800, 600, nmos::rational(72, 1)});
        if (est_timings_info.can_800_600_75()) established_timings.push_back({800, 600, nmos::rational(75, 1)});
        if (est_timings_info.can_832_624_75()) established_timings.push_back({832, 624, nmos::rational(75, 1)});
        if (est_timings_info.can_1024_768_87_i()) established_timings.push_back({1024, 768, nmos::rational(87, 1)});
        if (est_timings_info.can_1024_768_60()) established_timings.push_back({1024, 768, nmos::rational(60, 1)});
        if (est_timings_info.can_1024_768_70()) established_timings.push_back({1024, 768, nmos::rational(70, 1)});
        if (est_timings_info.can_1024_768_75()) established_timings.push_back({1024, 768, nmos::rational(75, 1)});
        if (est_timings_info.can_1280_1024_75()) established_timings.push_back({1280, 1024, nmos::rational(75, 1)});
        if (est_timings_info.can_1152_870_75()) established_timings.push_back({1152, 870, nmos::rational(75, 1)});
        return established_timings;
    }

    web::json::value make_edid_timing(const edid::timing& timing) {
        using web::json::value;
        using web::json::value_of;

        return value_of({
            { U("frame_rate"), nmos::make_rational(timing.frame_rate) },
            { U("frame_width"), timing.frame_width },
            { U("frame_height"), timing.frame_height }
        });
    }

    web::json::value make_edid(
        utility::string_t manufacturer,
        unsigned int manufacturer_week,
        unsigned int manufacturer_year,
        unsigned int screen_width,
        unsigned int screen_height,
        float gamma,
        std::vector<sdp::sampling> color_samplings,
        std::vector<edid::timing> established_timings,
        std::vector<edid::timing> standard_timings,
        std::vector<edid::timing> detailed_timings,
        std::vector<edid::timing> cta_861_timings
    )
    {
        using web::json::value;
        using web::json::value_of;

        value result = value_of({
            { U("manufacturer"), value::string(manufacturer) },
            { U("manufacture_week"), manufacturer_week },
            { U("manufacture_year"), manufacturer_year },
            { U("screen_size"), value_of({{ U("width"), screen_width }, { U("height"), screen_height }})},
            { U("gamma"), gamma }
        });

        auto& samplings = result[U("color_samplings")] = value::array();
        for (const auto& sampling : color_samplings)
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

    web::json::value parse_edid(const utility::string_t& edid_bytes)
    {
        kaitai::kstream ks(edid_bytes);
        edid_t edid_data(&ks);
        std::string manufacturer_name =
        {
            static_cast<char>(edid_data.mfg_id_ch1() + '@'),
            static_cast<char>(edid_data.mfg_id_ch2() + '@'),
            static_cast<char>(edid_data.mfg_id_ch3() + '@')
        };
        std::vector<sdp::sampling> samplings = { sdp::samplings::RGB };
        if (edid_data.features_flags() & (1 << 3)) samplings.push_back(sdp::samplings::YCbCr_4_2_2);
        if (edid_data.features_flags() & (1 << 4)) samplings.push_back(sdp::samplings::YCbCr_4_4_4);

        return make_edid(
            manufacturer_name,
            edid_data.mfg_week(),
            edid_data.mfg_year(),
            edid_data.screen_size_h(),
            edid_data.screen_size_v(),
            edid_data.gamma(),
            samplings,
            parse_established_timings(*edid_data.est_timings()),
            parse_standard_timings(*edid_data.std_timings()),
            {},
            {}
        );
    }
}
