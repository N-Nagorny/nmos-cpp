#include "nmos/sinkmetadataprocessing_resources.h"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include "cpprest/json_validator.h"
#include "nmos/api_utils.h"
#include "nmos/is11_versions.h"
#include "nmos/json_schema.h"
#include "nmos/model.h"
#include "nmos/rational.h"

namespace nmos
{
    nmos::resource make_empty_media_profiles(const nmos::id& id)
    {
        using web::json::value;
        using web::json::value_of;

        return{ is11_versions::v1_0, types::media_profiles, std::move(value_of({U("foo"), U("bar")})), id, false };
    }

    nmos::resource make_empty_sink(const nmos::id& id)
    {
        using web::json::value;
        using web::json::value_of;

        return{ is11_versions::v1_0, types::sink, std::move(value_of({U("foo"), U("bar")})), id, false };
    }
}
