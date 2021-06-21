#include "nmos/sinkmetadataprocessing_behaviour.h"

#include <boost/range/adaptor/filtered.hpp>
#include "nmos/activation_mode.h"
#include "nmos/activation_utils.h"
#include "nmos/media_profiles.h"

namespace nmos
{
    namespace experimental
    {
        void sinkmetadataprocessing_behaviour_thread(nmos::node_model& model, slog::base_gate& gate)
        {
            using web::json::value;
            using web::json::value_of;

            auto lock = model.write_lock(); // in order to update the resources
            auto& node_resources = model.node_resources;
            auto& sinkmetadataprocessing_resources = model.sinkmetadataprocessing_resources;

            auto most_recent_update = nmos::tai_min();

            for (;;)
            {
                model.wait(lock, [&] { return model.shutdown || most_recent_update < nmos::most_recent_update(node_resources); });
                if (model.shutdown) break;

                auto active_senders = node_resources | boost::adaptors::filtered([&most_recent_update] (const nmos::resource& resource) {
                    return nmos::types::sender == resource.type
                        && true == nmos::fields::active(nmos::fields::subscription(resource.data));
                });

                auto updated_sources = node_resources | boost::adaptors::filtered([&most_recent_update] (const nmos::resource& resource) {
                    return nmos::types::source == resource.type
                        && most_recent_update < resource.updated;
                });

                auto updated_flows = node_resources | boost::adaptors::filtered([&most_recent_update] (const nmos::resource& resource) {
                    return nmos::types::flow == resource.type
                        && most_recent_update < resource.updated;
                });

                for (const auto& flow : updated_flows)
                {
                    slog::log<slog::severities::info>(gate, SLOG_FLF) << "Flow " << flow.id << " is updated";
                    auto sender = std::find_if(active_senders.begin(), active_senders.end(), [&flow] (const nmos::resource& resource) {
                        return flow.id == nmos::fields::flow_id(resource.data).as_string();
                    });

                    if (active_senders.end() == sender)
                        continue;

                    const std::pair<nmos::id, nmos::type> id_type{ sender->id, nmos::types::sender };
                    auto sinkmetadataprocessing_sender = find_resource(sinkmetadataprocessing_resources, id_type);

                    if (sinkmetadataprocessing_resources.end() == sinkmetadataprocessing_sender)
                        continue;

                    slog::log<slog::severities::info>(gate, SLOG_FLF) << "Flow " << flow.id << " of Sink Metadata Processing sender is updated";
                    if (!nmos::experimental::match_media_profiles(model, sender->id))
                    {
                        auto connection_sender = find_resource(model.connection_resources, id_type);
                        if (model.connection_resources.end() != connection_sender)
                        {
                            slog::log<slog::severities::info>(gate, SLOG_FLF) << "Stopping transmitting from " << sender->id;
                            web::json::value merged;
                            nmos::modify_resource(model.connection_resources, id_type.first, [&merged](nmos::resource& connection_resource)
                            {
                                connection_resource.data[nmos::fields::version] = web::json::value::string(nmos::make_version());
                                merged = nmos::fields::endpoint_staged(connection_resource.data);
                                merged[nmos::fields::master_enable] = value::boolean(false);
                                auto activation = nmos::make_activation();
                                activation[nmos::fields::mode] = value::string(nmos::activation_modes::activate_immediate.name);
                                details::merge_activation(merged[nmos::fields::activation], activation, nmos::tai_now());
                                connection_resource.data[nmos::fields::endpoint_staged] = merged;
                            });

                            details::handle_immediate_activation_pending(model, lock, id_type, merged[nmos::fields::activation], gate);
                            slog::log<slog::severities::info>(gate, SLOG_FLF) << "Stopping transmitting from " << connection_sender->data;
                        }
                    }
                }

                model.notify();
                most_recent_update = nmos::most_recent_update(node_resources);
            }
        }
    }
}
