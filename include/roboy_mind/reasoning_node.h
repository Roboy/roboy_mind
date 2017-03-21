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
#include <roboy_mind/srvAssertProperty.h>
#include <roboy_mind/srvCallQuery.h>
#include <roboy_mind/srvCheckProperty.h>
#include <roboy_mind/srvCheckQuery.h>
#include <roboy_mind/srvCreateInstance.h>
#include <roboy_mind/srvFindInstances.h>
#include <roboy_mind/srvShowInstances.h>
#include <roboy_mind/srvShowProperty.h>
#include <roboy_mind/srvShowPropertyValue.h>
#include <roboy_mind/srvSaveObject.h>
#include <roboy_mind/srvGetObject.h>


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
    bool assertPropertySRV(roboy_mind::srvAssertProperty::Request  &req,roboy_mind::srvAssertProperty::Response &res);
    
    /** Service server for calling queries
     *  @param   req         object of srvCallQuery::Request service type,
     *  @param   res         object of srvCallQuery::Response service type,
     *  @param   query       query that needs to be called, string
     *  @return  result of the service stating whether the query has been called, bool
     */
    bool callQuerySRV(roboy_mind::srvCallQuery::Request  &req,roboy_mind::srvCallQuery::Response &res);

    /** Service server for checking property
     *  @param   req         object of srvCheckProperty::Request service type,
     *  @param   res         object of srvCheckProperty::Response service type,
     *  @param   object      name of the instance that the property should be asserted to, string
     *  @param   property    name of the property, string
     *  @param   instance    value for data properties or name of the instance for object properties, string
     *  @param   data        variable indicating whether the property is of data or object type, bool
     *  @return  result of the service stating whether the property with the given value was asserted, bool
     */
    bool checkPropertySRV(roboy_mind::srvCheckProperty::Request  &req,roboy_mind::srvCheckProperty::Response &res);

    /** Service server for checking queries
     *  @param   req         object of srvCheckQuery::Request service type,
     *  @param   res         object of srvCheckQuery::Response service type,
     *  @param   query       query that needs to be checked, string
     *  @return  result of the service stating whether the query is true or false, bool
     */
    bool checkQuerySRV(roboy_mind::srvCheckQuery::Request  &req,roboy_mind::srvCheckQuery::Response &res);

    /** Service server for instance creation
     *  @param   req            object of srvCreateInstance::Request service type,
     *  @param   res            object of srvCreateInstance::Response service type,
     *  @param   object_class   name of the object class which should be instantiated, string
     *  @param   id             id of the instance, int32
     *  @return  result of the service, bool
     */
    bool createInstanceSRV(roboy_mind::srvCreateInstance::Request  &req,roboy_mind::srvCreateInstance::Response &res);

    /** Service server for finding all instances with a given property
     *  @param   req            object of srvFindInstances::Request service type,
     *  @param   res            object of srvFindInstances::Response service type,
     *  @param   property       name of the property, string
     *  @param   instance       value for data properties or name of the instance for object properties, string
     *  @param   data           variable indicating whether the property is of data or object type, bool
     *  @return  vector of instances for which the property holds
     */
    bool findInstancesSRV(roboy_mind::srvFindInstances::Request  &req,roboy_mind::srvFindInstances::Response &res);

    /** Service server for showing instances
     *  @param   req            object of srvShowInstances::Request service type,
     *  @param   res            object of srvShowInstances::Response service type,
     *  @param   object_class   name of the object class instances of which should be shown, string
     *  @return  vector of instances for which the property holds
     */
    bool showInstancesSRV(roboy_mind::srvShowInstances::Request  &req,roboy_mind::srvShowInstances::Response &res);

    /** Service server for showing instances
     *  @param   req            object of srvShowProperty::Request service type,
     *  @param   res            object of srvShowProperty::Response service type,
     *  @param   object         name of the instance properties of which should be shown, string
     *  @return  vector of properties of the object
     */
    bool showPropertySRV(roboy_mind::srvShowProperty::Request  &req,roboy_mind::srvShowProperty::Response &res);

    /** Service server for showing property values of instances
     *  @param   req            object of srvShowPropertyValue::Request service type,
     *  @param   res            object of srvShowPropertyValue::Response service type,
     *  @param   object         name of the instance properties of which should be shown, string
     *  @param   property       name of the property, string
     *  @return  vector of properties of the object
     */
    bool showPropertyValueSRV(roboy_mind::srvShowPropertyValue::Request  &req,roboy_mind::srvShowPropertyValue::Response &res);


    bool saveObjectSRV(roboy_mind::srvSaveObject::Request  &req,roboy_mind::srvSaveObject::Response &res);

    bool getObjectSRV(roboy_mind::srvGetObject::Request  &req,roboy_mind::srvGetObject::Response &res);

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