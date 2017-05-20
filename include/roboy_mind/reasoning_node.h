#ifndef REASONING_NODE_H
#define REASONING_NODE_H

#endif // REASONING_NODE_H

/*! @file
 *  \brief Header file including RoboyMind class declarations.
 *
 *  Storing all declarations of RoboyMind class methods.
 */

// ROS library
#include <ros/ros.h>
#include <ros/duration.h>

// Prolog
#include <json_prolog/prolog.h>

//LOGIC SERVICES
#include <roboy_communication_cognition/AssertProperty.h>
#include <roboy_communication_cognition/CallQuery.h>
#include <roboy_communication_cognition/CheckProperty.h>
#include <roboy_communication_cognition/CheckQuery.h>
#include <roboy_communication_cognition/CreateInstance.h>
#include <roboy_communication_cognition/FindInstances.h>
#include <roboy_communication_cognition/ShowInstances.h>
#include <roboy_communication_cognition/ShowProperty.h>
#include <roboy_communication_cognition/ShowPropertyValue.h>
#include <roboy_communication_cognition/SaveObject.h>
#include <roboy_communication_cognition/GetObject.h>


#include <common.hpp>

using namespace std;
using namespace json_prolog;

#define SHOW_QUERIES true

class RoboyMind{
public:
    // Constructors
    RoboyMind(ros::NodeHandle);
    ~RoboyMind(){};

    /* *******************
     * Service functions
     * *******************/

    /** Service server for asserting property
     *  @param   req         object of srvAssertProperty::Request service type,
     *  @param   res         object of srvAssertProperty::Response service type,
     *  @param   object      name of the instance that the property should be asserted to, string
     *  @param   property    name of the property, string
     *  @param   instance    value for data properties or name of the instance for object properties, string
     *  @param   data        variable indicating whether the property is of data or object type, bool
     *  @return  result of the service, bool
     */
    bool assertPropertySRV(roboy_communication_cognition::AssertProperty::Request  &req,roboy_communication_cognition::AssertProperty::Response &res);
    
    /** Service server for calling queries
     *  @param   req         object of srvCallQuery::Request service type,
     *  @param   res         object of srvCallQuery::Response service type,
     *  @param   query       query that needs to be called, string
     *  @return  result of the service stating whether the query has been called, bool
     */
    bool callQuerySRV(roboy_communication_cognition::CallQuery::Request  &req,roboy_communication_cognition::CallQuery::Response &res);

    /** Service server for checking property
     *  @param   req         object of srvCheckProperty::Request service type,
     *  @param   res         object of srvCheckProperty::Response service type,
     *  @param   object      name of the instance that the property should be asserted to, string
     *  @param   property    name of the property, string
     *  @param   instance    value for data properties or name of the instance for object properties, string
     *  @param   data        variable indicating whether the property is of data or object type, bool
     *  @return  result of the service stating whether the property with the given value was asserted, bool
     */
    bool checkPropertySRV(roboy_communication_cognition::CheckProperty::Request  &req,roboy_communication_cognition::CheckProperty::Response &res);

    /** Service server for checking queries
     *  @param   req         object of srvCheckQuery::Request service type,
     *  @param   res         object of srvCheckQuery::Response service type,
     *  @param   query       query that needs to be checked, string
     *  @return  result of the service stating whether the query is true or false, bool
     */
    bool checkQuerySRV(roboy_communication_cognition::CheckQuery::Request  &req,roboy_communication_cognition::CheckQuery::Response &res);

    /** Service server for instance creation
     *  @param   req            object of srvCreateInstance::Request service type,
     *  @param   res            object of srvCreateInstance::Response service type,
     *  @param   object_class   name of the object class which should be instantiated, string
     *  @param   id             id of the instance, int32
     *  @return  result of the service, bool
     */
    bool createInstanceSRV(roboy_communication_cognition::CreateInstance::Request  &req,roboy_communication_cognition::CreateInstance::Response &res);

    /** Service server for finding all instances with a given property
     *  @param   req            object of srvFindInstances::Request service type,
     *  @param   res            object of srvFindInstances::Response service type,
     *  @param   property       name of the property, string
     *  @param   instance       value for data properties or name of the instance for object properties, string
     *  @param   data           variable indicating whether the property is of data or object type, bool
     *  @return  vector of instances for which the property holds
     */
    bool findInstancesSRV(roboy_communication_cognition::FindInstances::Request  &req,roboy_communication_cognition::FindInstances::Response &res);

    /** Service server for showing instances
     *  @param   req            object of srvShowInstances::Request service type,
     *  @param   res            object of srvShowInstances::Response service type,
     *  @param   object_class   name of the object class instances of which should be shown, string
     *  @return  vector of instances for which the property holds
     */
    bool showInstancesSRV(roboy_communication_cognition::ShowInstances::Request  &req,roboy_communication_cognition::ShowInstances::Response &res);

    /** Service server for showing instances
     *  @param   req            object of srvShowProperty::Request service type,
     *  @param   res            object of srvShowProperty::Response service type,
     *  @param   object         name of the instance properties of which should be shown, string
     *  @return  vector of properties of the object
     */
    bool showPropertySRV(roboy_communication_cognition::ShowProperty::Request  &req,roboy_communication_cognition::ShowProperty::Response &res);

    /** Service server for showing property values of instances
     *  @param   req            object of srvShowPropertyValue::Request service type,
     *  @param   res            object of srvShowPropertyValue::Response service type,
     *  @param   object         name of the instance properties of which should be shown, string
     *  @param   property       name of the property, string
     *  @return  vector of properties of the object
     */
    bool showPropertyValueSRV(roboy_communication_cognition::ShowPropertyValue::Request  &req,roboy_communication_cognition::ShowPropertyValue::Response &res);


    bool saveObjectSRV(roboy_communication_cognition::SaveObject::Request  &req,roboy_communication_cognition::SaveObject::Response &res);

    bool getObjectSRV(roboy_communication_cognition::GetObject::Request  &req,roboy_communication_cognition::GetObject::Response &res);

private:
    Prolog pl;
    
    string ontology_name;
    string knowrob;
    // Logic services
    ros::ServiceServer assert_property_service;
    ros::ServiceServer call_query_service;
    ros::ServiceServer check_query_service;
    ros::ServiceServer check_property_service;
    ros::ServiceServer create_instance_service;
    ros::ServiceServer find_instances_service;
    ros::ServiceServer show_instances_service;
    ros::ServiceServer show_properties_service;
    ros::ServiceServer show_property_value_service;

    ros::ServiceServer save_object_service;
    ros::ServiceServer get_object_service;

    /// The node handle
    ros::NodeHandle nh_;
    /// Node handle in the private namespace
    ros::NodeHandle priv_nh_;
};