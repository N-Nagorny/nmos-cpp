#ifndef NMOS_CONSTRAINTS_H
#define NMOS_CONSTRAINTS_H

#include "cpprest/json_ops.h" // for web::json::value, web::json::as, etc.
#include "nmos/model.h"

namespace nmos
{
    struct node_model;

    namespace experimental
    {
        bool match_source_constraint_set(const web::json::value& source, const web::json::value& constraint_set);
        bool match_flow_constraint_set(const web::json::value& flow, const web::json::value& constraint_set);
        bool match_source_and_flow_constraint_sets(const web::json::value& source, const web::json::value& flow, const web::json::value& constraint_sets);
        bool match_sender_constraint_sets(nmos::node_model& model, const nmos::id& sender_id);
    }
}

#endif
