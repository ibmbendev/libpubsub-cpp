/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    pubsubpeer.cpp
 * @date    5/30/2015
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "pubsubpeer.h"
#include "subscriber.h"

using namespace std;

PubSubPeer::PubSubPeer(int port) :
    PubSubBroadcastServer(m_bcserver),
    PubSubServer(m_httpserver),
    m_port(port),
    m_bcserver(port),
    m_bcclient(port),
    m_httpserver(port)
{
}

void PubSubPeer::addPublishTopic(const std::string &name)
{
    m_publishtopics.insert(name);
}

bool PubSubPeer::hasPublishTopic(const string &name)
{
    if(m_publishtopics.find(name) != m_publishtopics.end())
        return true;
    return false;
}

void PubSubPeer::addSubscribeTopic(const string &name)
{
    m_subscribetopics.insert(name);
}

bool PubSubPeer::hasSubscribeTopic(const string &name)
{
    if(m_subscribetopics.find(name) != m_subscribetopics.end())
        return true;
    return false;
}

//On subscriber broadcasts interest
void PubSubPeer::pubsub_publishinterest(const std::string &ip, const std::string &topic)
{
    if (hasPublishTopic(topic))
    {
        //offerTopic
        Subscriber sub(ip, m_port);
        Json::Value topics;
        for (auto &topic : m_publishtopics)
            topics.append(topic);
        sub.pubsub_offerTopic(m_ip, topics);
    }
}

//on publisher broadcasts topics
void PubSubPeer::pubsub_publishtopics(const std::string &ip, const Json::Value &topics)
{
    for (unsigned int i=0; i < topics.size(); i++)
    {
        if(hasSubscribeTopic(topics[i].asString()))
        {
            //Register
            //add result to subscriptions
            Subscriber* sub = new Subscriber(ip,m_port);
            string id = sub->pubsub_subscribe(m_ip, topics[i].asString());
            if (id != "")
            {
                sub->setSubscriptionId(id);
                m_publishers.addSubscriber(sub);
            }
            else
            {
                delete sub;
            }
        }
    }
}

string PubSubPeer::pubsub_subscribe(const string &ip, const string &notification)
{
    Subscriber* sub = m_subscribers.getSubscriber(ip, notification);
    if (sub == NULL)
    {
        sub = new Subscriber(ip, m_port);
        sub->setTopic(notification);
        m_subscribers.addSubscriber(sub);
    }
    return sub->getSubscriptionId();
}

bool PubSubPeer::pubsub_unsubscribe(const string &notificationId)
{
    return m_subscribers.removeSubscriber(notificationId);
}

void PubSubPeer::pubsub_offerTopic(const string &ip, const Json::Value &topics)
{
    this->pubsub_publishtopics(ip, topics);
}
