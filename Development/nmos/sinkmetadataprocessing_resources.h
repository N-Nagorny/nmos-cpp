#ifndef NMOS_SINKMETADATAPROCESSING_RESOURCES_H
#define NMOS_SINKMETADATAPROCESSING_RESOURCES_H

#include "nmos/id.h"
#include "nmos/settings.h"

namespace web
{
    class uri;
}

namespace nmos
{
    struct resource;

    nmos::resource make_empty_media_profiles(const nmos::id& id);
}

#endif
