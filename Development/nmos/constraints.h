#ifndef NMOS_CONSTRAINTS_H
#define NMOS_CONSTRAINTS_H

namespace web
{
    namespace json
    {
        class value;
    }
}

namespace nmos
{
    namespace experimental
    {
        web::json::value get_constraint_intersection(const web::json::value& lhs, const web::json::value& rhs);
        web::json::value get_constraint_set_intersection(const web::json::value& lhs, const web::json::value& rhs, bool merge_left_to_right = false);

        bool is_subconstraint(const web::json::value& constraint, const web::json::value& subconstraint);
        bool is_constraint_subset(const web::json::value& constraint_set, const web::json::value& constraint_subset, bool merge_left_to_right = false);
    }
}

#endif
