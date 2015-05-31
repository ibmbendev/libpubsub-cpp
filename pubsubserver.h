/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_PUBSUBSERVER_H_
#define JSONRPC_CPP_STUB_PUBSUBSERVER_H_

#include <jsonrpccpp/server.h>

class PubSubServer : public jsonrpc::AbstractServer<PubSubServer>
{
    public:
        PubSubServer(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<PubSubServer>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("pubsub.subscribe", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "ip",jsonrpc::JSON_STRING,"notification",jsonrpc::JSON_STRING, NULL), &PubSubServer::pubsub_subscribeI);
            this->bindAndAddMethod(jsonrpc::Procedure("pubsub.unsubscribe", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_BOOLEAN, "notificationId",jsonrpc::JSON_STRING, NULL), &PubSubServer::pubsub_unsubscribeI);
            this->bindAndAddNotification(jsonrpc::Procedure("pubsub.offerTopic", jsonrpc::PARAMS_BY_NAME, "ip",jsonrpc::JSON_STRING,"topics",jsonrpc::JSON_ARRAY, NULL), &PubSubServer::pubsub_offerTopicI);
        }

        inline virtual void pubsub_subscribeI(const Json::Value &request, Json::Value &response)
        {
            response = this->pubsub_subscribe(request["ip"].asString(), request["notification"].asString());
        }
        inline virtual void pubsub_unsubscribeI(const Json::Value &request, Json::Value &response)
        {
            response = this->pubsub_unsubscribe(request["notificationId"].asString());
        }
        inline virtual void pubsub_offerTopicI(const Json::Value &request)
        {
            this->pubsub_offerTopic(request["ip"].asString(), request["topics"]);
        }
        virtual std::string pubsub_subscribe(const std::string& ip, const std::string& notification) = 0;
        virtual bool pubsub_unsubscribe(const std::string& notificationId) = 0;
        virtual void pubsub_offerTopic(const std::string& ip, const Json::Value& topics) = 0;
};

#endif //JSONRPC_CPP_STUB_PUBSUBSERVER_H_
