#include "nmos/sinkmetadataprocessing_api.h"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include "cpprest/json_validator.h"
#include "cpprest/containerstream.h"
#include "nmos/api_utils.h"
#include "nmos/capabilities.h"
#include "nmos/connection_resources.h"
#include "nmos/constraints.h"
#include "nmos/format.h"
#include "nmos/is11_versions.h"
#include "nmos/json_schema.h"
#include "nmos/model.h"
#include "nmos/rational.h"
#include "nmos/sdp_utils.h"
#include "nmos/sinkmetadataprocessing_resources.h"
#include "sdp/sdp.h"

#include <unordered_set>

namespace nmos
{
    namespace experimental
    {
        web::http::experimental::listener::api_router make_unmounted_sinkmetadataprocessing_api(nmos::node_model& model, details::sinkmetadataprocessing_media_profiles_patch_handler media_profiles_patch_handler, details::sinkmetadataprocessing_media_profiles_delete_handler media_profiles_delete_handler, nmos::experimental::details::sinkmetadataprocessing_constraints_validator constraints_validator, slog::base_gate& gate);

        web::http::experimental::listener::api_router make_sinkmetadataprocessing_api(nmos::node_model& model, details::sinkmetadataprocessing_media_profiles_patch_handler media_profiles_patch_handler, details::sinkmetadataprocessing_media_profiles_delete_handler media_profiles_delete_handler, nmos::experimental::details::sinkmetadataprocessing_constraints_validator constraints_validator, slog::base_gate& gate)
        {
            using namespace web::http::experimental::listener::api_router_using_declarations;

            api_router sinkmetadataprocessing_api;

            sinkmetadataprocessing_api.support(U("/?"), methods::GET, [](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body({ U("x-nmos/") }, req, res));
                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/x-nmos/?"), methods::GET, [](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body({ U("sink-mp/") }, req, res));
                return pplx::task_from_result(true);
            });

            const auto versions = with_read_lock(model.mutex, [&model] { return nmos::is11_versions::from_settings(model.settings); });
            sinkmetadataprocessing_api.support(U("/x-nmos/") + nmos::patterns::sinkmetadataprocessing_api.pattern + U("/?"), methods::GET, [versions](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body(nmos::make_api_version_sub_routes(versions), req, res));
                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.mount(U("/x-nmos/") + nmos::patterns::sinkmetadataprocessing_api.pattern + U("/") + nmos::patterns::version.pattern, make_unmounted_sinkmetadataprocessing_api(model, media_profiles_patch_handler, media_profiles_delete_handler, constraints_validator, gate));

            return sinkmetadataprocessing_api;
        }

        web::http::experimental::listener::api_router make_unmounted_sinkmetadataprocessing_api(nmos::node_model& model, details::sinkmetadataprocessing_media_profiles_patch_handler media_profiles_patch_handler, details::sinkmetadataprocessing_media_profiles_delete_handler media_profiles_delete_handler, nmos::experimental::details::sinkmetadataprocessing_constraints_validator constraints_validator, slog::base_gate& gate_)
        {
            using namespace web::http::experimental::listener::api_router_using_declarations;

            api_router sinkmetadataprocessing_api;

            // check for supported API version
            const auto versions = with_read_lock(model.mutex, [&model] { return nmos::is11_versions::from_settings(model.settings); });

            const web::json::experimental::json_validator validator
            {
                nmos::experimental::load_json_schema,
                boost::copy_range<std::vector<web::uri>>(versions | boost::adaptors::transformed(experimental::make_sinkmetadataprocessingapi_sender_constraints_put_request_uri))
            };

            sinkmetadataprocessing_api.support(U(".*"), nmos::details::make_api_version_handler(versions, gate_));

            sinkmetadataprocessing_api.support(U("/?"), methods::GET, [](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body({ U("inputs/"), U("outputs/"), U("senders/"), U("receivers/") }, req, res));
                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::sinkMetadataResourceType.pattern + U("/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                nmos::api_gate gate(gate_, req, parameters);
                auto lock = model.read_lock();
                auto& resources = model.sinkmetadataprocessing_resources;

                const string_t resourceType = parameters.at(nmos::patterns::sinkMetadataResourceType.name);

                const auto match = [&](const nmos::resources::value_type& resource) { return resource.type == nmos::type_from_resourceType(resourceType); };

                size_t count = 0;

                // experimental extension, to support human-readable HTML rendering of NMOS responses
                if (experimental::details::is_html_response_preferred(req, web::http::details::mime_types::application_json))
                {
                    set_reply(res, status_codes::OK,
                        web::json::serialize_array(resources
                            | boost::adaptors::filtered(match)
                            | boost::adaptors::transformed(
                                [&count, &req](const nmos::resource& resource) { ++count; return experimental::details::make_html_response_a_tag(resource.id + U("/"), req); }
                            )),
                        web::http::details::mime_types::application_json);
                }
                else
                {
                    set_reply(res, status_codes::OK,
                        web::json::serialize_array(resources
                            | boost::adaptors::filtered(match)
                            | boost::adaptors::transformed(
                                [&count](const nmos::resource& resource) { ++count; return value(resource.id + U("/")); }
                            )
                        ),
                        web::http::details::mime_types::application_json);
                }

                slog::log<slog::severities::info>(gate, SLOG_FLF) << "Returning " << count << " matching " << resourceType;

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::sinkMetadataResourceType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                nmos::api_gate gate(gate_, req, parameters);
                auto lock = model.read_lock();
                auto& resources = model.sinkmetadataprocessing_resources;

                const string_t resourceType = parameters.at(nmos::patterns::sinkMetadataResourceType.name);
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::type_from_resourceType(resourceType) };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if ((nmos::type_from_resourceType(resourceType) == nmos::types::sender ||
                        nmos::type_from_resourceType(resourceType) == nmos::types::receiver) &&
                        model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    std::set<utility::string_t> sub_routes;
                    if (nmos::types::sender == resource->type)
                    {
                        sub_routes = { U("inputs/"), U("constraints/") };
                    }
                    else if (nmos::types::receiver == resource->type)
                    {
                        sub_routes = { U("outputs/") };
                    }
                    else
                    {
                        sub_routes = { U("edid/"), U("properties/") };
                    }

                    set_reply(res, status_codes::OK, nmos::make_sub_routes_body(std::move(sub_routes), req, res));
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/constraints/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::types::sender };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if (model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    std::set<utility::string_t> sub_routes{ U("active/"), U("supported/") };

                    set_reply(res, status_codes::OK, nmos::make_sub_routes_body(std::move(sub_routes), req, res));
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/constraints") + U("/supported/?"), methods::GET, [&model](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::types::sender };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if (model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    const auto response = web::json::value_of({
                        { nmos::fields::parameter_constraints, web::json::value_from_elements(nmos::fields::parameter_constraints(resource->data)) }
                    });

                    set_reply(res, status_codes::OK, response);
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/constraints") + U("/active/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                std::shared_ptr<nmos::api_gate> gate(new nmos::api_gate(gate_, req, parameters));
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::types::sender };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if (model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    if (!nmos::experimental::match_sender_constraint_sets(model, resourceId))
                        set_reply(res, status_codes::ResetContent);
                    else
                        set_reply(res, status_codes::OK, nmos::fields::constraint_sets(resource->data));
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/constraints") + U("/active/?"), methods::PUT, [&model, validator, media_profiles_patch_handler, constraints_validator, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                std::shared_ptr<nmos::api_gate> gate(new nmos::api_gate(gate_, req, parameters));

                auto lock = model.write_lock();
                auto& node_resources = model.node_resources;
                auto& connection_resources = model.connection_resources;
                auto& sinkmetadataprocessing_resources = model.sinkmetadataprocessing_resources;

                const nmos::api_version version = nmos::parse_api_version(parameters.at(nmos::patterns::version.name));
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                auto sinkmetadataprocessing_sender = find_resource(sinkmetadataprocessing_resources, { resourceId, nmos::types::sender });

                if (sinkmetadataprocessing_resources.end() != sinkmetadataprocessing_sender)
                {
                    return nmos::details::extract_json(req, *gate).then([&model, &node_resources, &connection_resources, &sinkmetadataprocessing_resources, sinkmetadataprocessing_sender, media_profiles_patch_handler, constraints_validator, validator, version, resourceId, res, gate](value constraints) mutable
                    {
                        validator.validate(constraints, experimental::make_sinkmetadataprocessingapi_sender_constraints_put_request_uri(version));

                        const auto supported_param_cons = boost::copy_range<std::unordered_set<utility::string_t>>(nmos::fields::parameter_constraints(sinkmetadataprocessing_sender->data) | boost::adaptors::transformed([gate](const web::json::value& param_con)
                        {
                            return std::unordered_set<utility::string_t>::value_type{ param_con.as_string() };
                        }));

                        const auto constraint_sets = nmos::fields::constraint_sets(constraints);

                        for (const auto& constraint_set : constraint_sets.as_array())
                        {
                            const auto& param_cons = constraint_set.as_object();
                            if (param_cons.end() != std::find_if(param_cons.begin(), param_cons.end(), [&](const std::pair<utility::string_t, value>& constraint)
                            {
                                return supported_param_cons.count(constraint.first) == 0;
                            })) {
                                set_error_reply(res, status_codes::BadRequest, U("The requested Constraint Set uses Parameter Constraints unsupported by this Sender."));
                                return true;
                            }
                        }

                        if (constraints_validator) {
                            if (!constraints_validator(resourceId, constraints, *gate)) {
                                set_error_reply(res, status_codes::UnprocessableEntity, U("This Sender can't adhere to the requested Constraint Sets."));
                                return true;
                            }
                        }

                        auto connection_sender = find_resource(connection_resources, { resourceId, nmos::types::sender });
                        if (connection_sender == connection_resources.end()) {
                            throw std::logic_error("matching IS-05 Sender not found");
                        }
                        auto sender = find_resource(node_resources, { resourceId, nmos::types::sender });
                        if (sender == node_resources.end()) {
                            throw std::logic_error("matching IS-04 Sender not found");
                        }
                        auto flow = find_resource(node_resources, { nmos::fields::flow_id(sender->data).as_string(), nmos::types::flow });
                        if (flow == node_resources.end()) {
                            throw std::logic_error("matching IS-04 Flow not found");
                        }
                        auto source = find_resource(node_resources, { nmos::fields::source_id(flow->data), nmos::types::source });
                        if (node_resources.end() == source) {
                            throw std::logic_error("matching IS-04 Source not found");
                        }

                        auto new_flow = flow->data;
                        auto new_source = source->data;
                        if (media_profiles_patch_handler)
                            media_profiles_patch_handler(resourceId, constraints, new_source, new_flow, *gate);

                        slog::log<slog::severities::info>(*gate, SLOG_FLF) << "Sender " << sender->id << " accepted " << constraints;
                        modify_resource(sinkmetadataprocessing_resources, resourceId, [&constraint_sets](nmos::resource& resource) { resource.data[U("constraint_sets")] = constraint_sets; });
                        set_reply(res, status_codes::OK, constraints);
                        return true;
                    });
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/constraints") + U("/active/?"), methods::DEL, [&model, media_profiles_delete_handler, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                std::shared_ptr<nmos::api_gate> gate(new nmos::api_gate(gate_, req, parameters));

                auto lock = model.write_lock();
                auto& resources = model.sinkmetadataprocessing_resources;

                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                auto found = find_resource(resources, { resourceId, nmos::types::sender });

                if (resources.end() != found)
                {
                    modify_resource(resources, resourceId, [](nmos::resource& resource) {
                        resource.data[U("constraint_sets")] = value::array();
                    });
                    if (media_profiles_delete_handler)
                        media_profiles_delete_handler(resourceId, *gate);
                    set_reply(res, status_codes::NoContent);
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::connectorType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/") + nmos::patterns::senderReceiverSubrouteType.pattern + U("/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                nmos::api_gate gate(gate_, req, parameters);
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceType = parameters.at(nmos::patterns::connectorType.name);
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);
                const string_t associatedResourceType = parameters.at(nmos::patterns::senderReceiverSubrouteType.name);
                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::type_from_resourceType(resourceType) };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if (model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    const auto match = [&](const nmos::resources::value_type& resource)
                    {
                        return resource.type == nmos::type_from_resourceType(resourceType) && nmos::fields::id(resource.data) == resourceId;
                    };

                    const auto filter = (nmos::types::input == nmos::type_from_resourceType(associatedResourceType)) ?
                        nmos::fields::inputs :
                        nmos::fields::outputs;

                    set_reply(res, status_codes::OK,
                        web::json::serialize_array(resources
                            | boost::adaptors::filtered(match)
                            | boost::adaptors::transformed(
                                [&filter](const nmos::resource& resource) { return value_from_elements(filter(resource.data)); }
                            )
                        ),
                        web::http::details::mime_types::application_json);
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::inputOutputType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/edid/?"), methods::GET, [&model](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceType = parameters.at(nmos::patterns::inputOutputType.name);
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::type_from_resourceType(resourceType) };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto i_stream = concurrency::streams::bytestream::open_istream(resource->data.at("edid_binary").as_string());
                    set_reply(res, status_codes::OK, i_stream);
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::inputOutputType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/properties/?"), methods::GET, [&model](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceType = parameters.at(nmos::patterns::inputOutputType.name);
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::type_from_resourceType(resourceType) };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto data = resource->data;
                    data.erase(U("edid_binary"));
                    set_reply(res, status_codes::OK, data);
                }
                else if (nmos::details::is_erased_resource(resources, id_type))
                {
                    set_error_reply(res, status_codes::NotFound, U("Not Found; ") + nmos::details::make_erased_resource_error());
                }
                else
                {
                    set_reply(res, status_codes::NotFound);
                }

                return pplx::task_from_result(true);
            });

            return sinkmetadataprocessing_api;
        }
    }
}
