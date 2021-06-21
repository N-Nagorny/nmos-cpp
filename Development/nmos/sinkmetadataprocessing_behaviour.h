#ifndef NMOS_SINKMETADATAPROCESSING_BEHAVIOUR_H
#define NMOS_SINKMETADATAPROCESSING_BEHAVIOUR_H

#include "nmos/model.h"
#include "nmos/slog.h"

namespace nmos
{
    namespace experimental
    {
        void sinkmetadataprocessing_behaviour_thread(nmos::node_model& model, slog::base_gate& gate);
    }
}

#endif
