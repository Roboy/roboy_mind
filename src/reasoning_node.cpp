/* ***************************************
    Author:	Emilia Lozinska
    E-mail:	ga47nub@mytum.de
*/

/*! @file
 *  \brief Main reasoning node.
 *         Storing all service and callback definitions.
 *
 *  Storing all definitions of RoboyMin dclass methods.
 */
#include <roboy_mind/reasoning_node.h>

/* *******************
* Service functions
* *******************/
bool RoboyMind::assertPropertySRV(roboy_mind::srvAssertProperty::Request  &req,roboy_mind::srvAssertProperty::Response &res)
{
    // Query part for the object
    string query = "rdf_assert('" + this->ontology_name;
    query += req.object;
    query += "','" + this->ontology_name;
    query += req.property;
    if (!req.data){
      query += "','" + this->ontology_name;
      query += req.instance;
    }
    else{
      query += "','";
      query += req.instance;
    }
    query += "')";
    if (SHOW_QUERIES)   
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    res.result = true;
    return true;
}

bool RoboyMind::callQuerySRV(roboy_mind::srvCallQuery::Request  &req,roboy_mind::srvCallQuery::Response &res)
{
    // Quering Prolog to see the instances
    PrologQueryProxy bdgs = pl.query(req.query);
    if (SHOW_QUERIES) 
        cout << req.query << endl;
    res.result = false;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        //cout << "Query is : " << (bool)(it == bdgs.end()) << endl;
        res.result = true;
    }
    return true;
}


bool RoboyMind::checkPropertySRV(roboy_mind::srvCheckProperty::Request  &req,roboy_mind::srvCheckProperty::Response &res)
{
    // Query part for the object
    string query = "owl_has('" + this->ontology_name;
    query += req.object;
    query += "','" + this->ontology_name;
    query += req.property;
    if (!req.data)
      query += "','" + this->ontology_name;
    else
      query += "','";
    query += req.instance;
    query += "')";
    if (SHOW_QUERIES) 
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    res.result = false;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        //cout << "Real query is : " << (bool)(it == bdgs.end()) << endl;
        res.result = true;
    }
}

bool RoboyMind::checkQuerySRV(roboy_mind::srvCheckQuery::Request  &req,roboy_mind::srvCheckQuery::Response &res)
{
    // Quering Prolog to see the instances
    PrologQueryProxy bdgs = pl.query(req.query);
    if (SHOW_QUERIES) 
        cout << req.query << endl;
    res.result = false;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        //cout << "Query is : " << (bool)(it == bdgs.end()) << endl;
        res.result = true;
    }
    return true;
}

bool RoboyMind::createInstanceSRV(roboy_mind::srvCreateInstance::Request  &req,roboy_mind::srvCreateInstance::Response &res)
{
    // Building the query
    string query = "create_instance_from_class('" + this->ontology_name;
    query += req.object_class;
    query += "',";
    query += IntToStr(req.id);
    query += ", ObjInst)";
    if (SHOW_QUERIES) 
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    res.instance = req.object_class + "_" + IntToStr(req.id);
    ROS_INFO("New instance created. \n Instance id: %d ", req.id);
    return true;
}

bool RoboyMind::findInstancesSRV(roboy_mind::srvFindInstances::Request  &req,roboy_mind::srvFindInstances::Response &res)
{
    vector<string> result;
    // Query part for the object
    string query = "owl_has(A,'" + this->ontology_name;
    query += req.property;
    query += "','";
    if (!req.data){
      query += "" + this->ontology_name;
    }
    query += req.value;
    query += "')";
    if (SHOW_QUERIES)   
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    stringstream ss;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        //cout << "A : " << bdg["A"] << endl;
        ss << bdg["A"];
        result.push_back(ss.str());
        ss.str(std::string());
    }
    res.instances = result;
    return true;
}

bool RoboyMind::showInstancesSRV(roboy_mind::srvShowInstances::Request  &req,roboy_mind::srvShowInstances::Response &res)
{
    vector<string> result;
    string query = "rdfs_individual_of(I, '" + this->ontology_name;
    query += req.object_class;
    query += "')";
    if (SHOW_QUERIES) 
        cout << query << endl;
    // Quering Prolog to see the instances
    PrologQueryProxy bdgs = pl.query(query);
    stringstream ss;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        //cout << "I : " << bdg["I"] << endl;
        ss << bdg["I"];
        result.push_back(ss.str());
        ss.str(std::string());
    }
    res.instances = result;
    return true;
}

bool RoboyMind::showPropertySRV(roboy_mind::srvShowProperty::Request  &req,roboy_mind::srvShowProperty::Response &res)
{
    vector<string> result;
    // Query part for the object
    string query = "owl_has('";
    query += ontology_name;
    query += req.object;
    query += "',A,P)";
    if (SHOW_QUERIES) 
        cout << query << endl;
    // Quering Prolog to see the properties and values
    PrologQueryProxy bdgs = pl.query(query);
    stringstream ss;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        cout << "Property : " << bdg["A"] << endl;
        cout << "Value : " << bdg["P"] << endl;
        ss << bdg["A"];
        result.push_back(ss.str());
        ss.str(std::string());
    }
    res.property = result;
    return true;
}

bool RoboyMind::showPropertyValueSRV(roboy_mind::srvShowPropertyValue::Request  &req,roboy_mind::srvShowPropertyValue::Response &res)
{
    vector<string> result;
    // Query part for the object
    string query = "owl_has('";
    query += req.object;
    query += "','" + this->ontology_name;
    query += req.property;
    query += "',P)";
    if (SHOW_QUERIES)   
        cout << query << endl;
    // Quering Prolog to see the properties and values
    PrologQueryProxy bdgs = pl.query(query);
    stringstream ss;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        cout << "Value : " << bdg["P"] << endl;
        ss << bdg["P"];
        result.push_back(ss.str());
        ss.str(std::string());
    }
    res.value = result;
    return true;
}

bool RoboyMind::saveObjectSRV(roboy_mind::srvSaveObject::Request  &req,roboy_mind::srvSaveObject::Response &res)
{    
    // Query part for the object
    // save_object(Class, ID, Properties, Values, Instance)
    stringstream main, prop, val;
    main << "save_object('" << req.class_name << "','" << req.id << "',['";
    // Save names
    for (int i = 0; i < req.properties.size(); i++)
    {
        if (i != req.properties.size() - 1)
        {
            prop << req.properties[i] << "','";
            val << req.values[i] << "','";
        }
        else
        {
            prop << req.properties[i] << "'],['";
            val << req.values[i] << "'],";         
        }
    }
    main << prop.str() << val.str() << " Instance)";
    string query = main.str();
    query.erase(std::remove(query.begin(), query.end(), '\n'), query.end());
    if (SHOW_QUERIES)   
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    res.result = false;
    string inst;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        inst = (bdg["Instance"].toString());
        if (inst.find("#", 0) !=std::string::npos)
            res.instance = inst.substr(inst.find("#", 0)+1);
        else
            res.instance = inst;
        res.result = true;
    }
    return true;  
}


bool RoboyMind::getObjectSRV(roboy_mind::srvGetObject::Request  &req,roboy_mind::srvGetObject::Response &res)
{    
    // Query part for the object
    // get_object(Properties, Values, Class, Instance)
    stringstream main, prop, val;
    main << "get_object(['";
    // Save names
    for (int i = 0; i < req.properties.size(); i++)
    {
        if (i != req.properties.size() - 1)
        {
            prop << req.properties[i] << "','";
            val << req.values[i] << "','";
        }
        else
        {
            prop << req.properties[i] << "'],['";
            val << req.values[i] << "'],";         
        }
    }
    main << prop.str() << val.str() << " Class, Instance)";
    string query = main.str();
    query.erase(std::remove(query.begin(), query.end(), '\n'), query.end());
    if (SHOW_QUERIES)   
        cout << query << endl;
    PrologQueryProxy bdgs = pl.query(query);
    res.result = false;
    string inst,cl;
    for(PrologQueryProxy::iterator it=bdgs.begin();it != bdgs.end(); it++)
    {
        PrologBindings bdg = *it;
        inst = (bdg["Instance"].toString());
        if (inst.find("#", 0) !=std::string::npos)
            res.instance = inst.substr(inst.find("#", 0)+1);
        else
            res.instance = inst;

        cl = (bdg["Class"].toString());
        if (cl.find("#", 0) !=std::string::npos)
            res.class_name = cl.substr(cl.find("#", 0)+1);
        else
            res.instance = inst;
        res.result = true;
    }
    return true;  
}


// Constructor
RoboyMind::RoboyMind(ros::NodeHandle nh) : nh_(nh), priv_nh_("~")
{
    // Service Servers
    assert_property_service = nh_.advertiseService("/roboy_mind/assert_property",&RoboyMind::assertPropertySRV,this);
    call_query_service = nh_.advertiseService("/roboy_mind/call_query",&RoboyMind::callQuerySRV,this);
    check_property_service = nh_.advertiseService("/roboy_mind/check_property",&RoboyMind::checkPropertySRV,this);
    check_query_service = nh_.advertiseService("/roboy_mind/check_query",&RoboyMind::checkQuerySRV,this);
    create_instance_service = nh_.advertiseService("/roboy_mind/create_instance",&RoboyMind::createInstanceSRV,this);
    find_instances_service = nh_.advertiseService("/roboy_mind/find_instances",&RoboyMind::findInstancesSRV,this);
    show_instances_service = nh_.advertiseService("/roboy_mind/show_instances",&RoboyMind::showInstancesSRV,this);
    show_properties_service = nh_.advertiseService("/roboy_mind/show_property",&RoboyMind::showPropertySRV,this);
    show_property_value_service = nh_.advertiseService("/roboy_mind/show_property_value",&RoboyMind::showPropertyValueSRV,this);

    save_object_service = nh_.advertiseService("/roboy_mind/save_object",&RoboyMind::saveObjectSRV,this);
    get_object_service = nh_.advertiseService("/roboy_mind/get_object",&RoboyMind::getObjectSRV,this);

    //nh.param<std::string>("/knowrob", knowrob, "http://knowrob.org/kb/knowrob.owl#");
    nh.param<std::string>("/ontology_name", ontology_name, "http://knowrob.org/kb/knowrob.owl#");//"http://knowrob.org/kb/semRoom_semantic_map.owl#");
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "reasoning_node");
    ros::NodeHandle nh;
    RoboyMind node(nh);
    ROS_INFO("Reasoning node init successful");
    ros::spin();
    return 0;
}