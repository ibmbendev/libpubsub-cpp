/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_PUBSUBCLIENT_H_
#define JSONRPC_CPP_STUB_PUBSUBCLIENT_H_

#include <jsonrpccpp/client.h>

class PubSubClient : public jsonrpc::Client
{
    public:
        PubSubClient(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        std::string pubsub_subscribe(const std::string& notification) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["notification"] = notification;
            Json::Value result = this->CallMethod("pubsub.subscribe",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool pubsub_unsubscribe(const std::string& notificationId) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["notificationId"] = notificationId;
            Json::Value result = this->CallMethod("pubsub.unsubscribe",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        void pubsub_offerTopic(const std::string& ip, const Json::Value& topics) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["ip"] = ip;
            p["topics"] = topics;
            this->CallNotification("pubsub.offerTopic",p);
        }
};

#endif //JSONRPC_CPP_STUB_PUBSUBCLIENT_H_
