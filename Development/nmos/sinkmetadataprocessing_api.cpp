#include "nmos/sinkmetadataprocessing_api.h"

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
    namespace experimental
    {
        web::http::experimental::listener::api_router make_unmounted_sinkmetadataprocessing_api(nmos::node_model& model, slog::base_gate& gate);

        web::http::experimental::listener::api_router make_sinkmetadataprocessing_api(nmos::node_model& model, slog::base_gate& gate)
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
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body({ U("sinkmetadataprocessing/") }, req, res));
                return pplx::task_from_result(true);
            });

            const auto versions = with_read_lock(model.mutex, [&model] { return nmos::is11_versions::from_settings(model.settings); });
            sinkmetadataprocessing_api.support(U("/x-nmos/") + nmos::patterns::sinkmetadataprocessing_api.pattern + U("/?"), methods::GET, [versions](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body(nmos::make_api_version_sub_routes(versions), req, res));
                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.mount(U("/x-nmos/") + nmos::patterns::sinkmetadataprocessing_api.pattern + U("/") + nmos::patterns::version.pattern, make_unmounted_sinkmetadataprocessing_api(model, gate));

            return sinkmetadataprocessing_api;
        }

        web::http::experimental::listener::api_router make_unmounted_sinkmetadataprocessing_api(nmos::node_model& model, slog::base_gate& gate_)
        {
            using namespace web::http::experimental::listener::api_router_using_declarations;

            api_router sinkmetadataprocessing_api;

            // check for supported API version
            const auto versions = with_read_lock(model.mutex, [&model] { return nmos::is11_versions::from_settings(model.settings); });


            const web::json::experimental::json_validator validator
            {
                nmos::experimental::load_json_schema,
                boost::copy_range<std::vector<web::uri>>(versions | boost::adaptors::transformed(experimental::make_sinkmetadataprocessingapi_sender_media_profiles_put_request_uri))
            };

            sinkmetadataprocessing_api.support(U(".*"), nmos::details::make_api_version_handler(versions, gate_));

            sinkmetadataprocessing_api.support(U("/?"), methods::GET, [](http_request req, http_response res, const string_t&, const route_parameters&)
            {
                set_reply(res, status_codes::OK, nmos::make_sub_routes_body({ U("senders/"), U("receivers/"), U("sinks/") }, req, res));
                return pplx::task_from_result(true);
            });

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::sinkMetadataResourceType.pattern + U("/?"), methods::GET, [&model, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                nmos::api_gate gate(gate_, req, parameters);
                auto lock = model.read_lock();
                auto& resources = model.sinkmetadataprocessing_resources;

                const string_t resourceType = parameters.at(nmos::patterns::sinkMetadataResourceType.name);

                // TODO (N-Nagorny): Add Sinks and Receivers in node_implementation.cpp to let them be found here.
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
                    if (nmos::type_from_resourceType(resourceType) != nmos::types::sink && model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    if (nmos::types::sink == resource->type)
                    {
                        set_reply(res, status_codes::OK, resource->data);
                    }
                    else
                    {
                        std::set<utility::string_t> sub_routes;
                        utility::string_t sub_route;
                        if (nmos::types::sender == resource->type) sub_route = U("media-profiles/");
                        else if (nmos::types::receiver == resource->type) sub_route = (U("sinks/"));
                        sub_routes.insert(sub_route);

                        set_reply(res, status_codes::OK, nmos::make_sub_routes_body(std::move(sub_routes), req, res));
                    }
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

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/media-profiles/?"), methods::GET, [&model](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                auto& resources = model.sinkmetadataprocessing_resources;
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                const std::pair<nmos::id, nmos::type> id_type{ resourceId, nmos::type_from_resourceType(nmos::patterns::senderType.name) };
                auto resource = find_resource(resources, id_type);
                if (resources.end() != resource)
                {
                    auto matching_resource = find_resource(model.node_resources, id_type);
                    if (model.node_resources.end() == matching_resource)
                    {
                        throw std::logic_error("matching IS-04 resource not found");
                    }

                    set_reply(res, status_codes::OK, resource->data);
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

            sinkmetadataprocessing_api.support(U("/") + nmos::patterns::senderType.pattern + U("/") + nmos::patterns::resourceId.pattern + U("/media-profiles/?"), methods::PUT, [&model, validator, &gate_](http_request req, http_response res, const string_t&, const route_parameters& parameters)
            {
                std::shared_ptr<nmos::api_gate> gate(new nmos::api_gate(gate_, req, parameters));

                auto lock = model.write_lock();
                auto& resources = model.sinkmetadataprocessing_resources;

                const nmos::api_version version = nmos::parse_api_version(parameters.at(nmos::patterns::version.name));
                const string_t resourceId = parameters.at(nmos::patterns::resourceId.name);

                auto resource = find_resource(resources, { resourceId, nmos::types::media_profiles });

                std::function<pplx::task<void>(const nmos::id& receiver_id, const web::json::value& sender_data, slog::base_gate& gate)> target_handler = [&model](const nmos::id& receiver_id, const web::json::value& sender_data, slog::base_gate& gate)
                {
                    return pplx::create_task([&model, receiver_id, &gate]
                    {
                        slog::log<slog::severities::info>(gate, SLOG_FLF) << "Returning " << receiver_id;
                    });
                };

                if (resources.end() != resource)
                {
                    return nmos::details::extract_json(req, *gate).then([target_handler, validator, version, &resources, resourceId, res, gate](value sender_data) mutable
                    {
                        validator.validate(sender_data, experimental::make_sinkmetadataprocessingapi_sender_media_profiles_put_request_uri(version));

                        return target_handler(resourceId, sender_data, *gate).then([ &resources, resourceId, res, sender_data, gate]() mutable
                        {
                            modify_resource(resources, resourceId, [&sender_data](nmos::resource& resource) { resource.data = sender_data; });
                            set_reply(res, status_codes::Accepted, sender_data);
                            return true;
                        });
                    });
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
