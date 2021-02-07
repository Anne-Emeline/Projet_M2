//
//  read_files.cpp
//  scenario
//
//  Created by Anne-Emeline Huard on 07/12/2020.
//

#include "read_files.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// *****************************************************************************************************************************
// ********************************************** lire_fichier_param_gen *******************************************************
// *****************************************************************************************************************************
/*
 Procedure
 searching for variable name in a line of type string
*/
void chercher_variable(string the_line, string the_variable, int* adr_variable)
{
    string word;
    istringstream stream(the_line);
    stream >> word;
    if (word == the_variable)
    {
        stream >> *adr_variable;
    }
}

// *****************************************************************************************************************************
/*
 Procedure
 reading the string type line and save all the tops in a vector (reading variable nb_tops)
*/
void combien_de_tops(string the_line, string the_variable, vector<int>* adr_tab_nb_tops)
{
    string word;
    int val;
    istringstream stream(the_line);
    stream >> word;
    if (word == the_variable)
    {
       while (stream >> val)
       {
           adr_tab_nb_tops->push_back(val);
       }
    }
}

// *****************************************************************************************************************************
/*
 Procedure
 reading the file with general settings
 number of observations
 number of variables
 number of actions
 vector with actions / events associate with their probability
*/
void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, vector<int>* adr_tab_nb_tops, int* adr_nb_tops_total)
{
    ifstream param_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/param_gen.txt");

    if (param_file)
    {
        string line;
        while (getline(param_file, line))
        {
            if (line[0] != '/')
            {
                chercher_variable(line, "nb_obs", adr_nb_obs );
                chercher_variable(line, "nb_var", adr_nb_var);
                chercher_variable(line, "nb_actions", adr_nb_actions);
                combien_de_tops(line, "nb_tops", adr_tab_nb_tops);
                chercher_variable(line, "nb_tops_total", adr_nb_tops_total);
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the param_gen file." << endl;
    }
}

// *****************************************************************************************************************************
// ************************************************** read_files ***************************************************************
// *****************************************************************************************************************************
/*
 Function
 read trace file and return a vector with action and top associate in a pair
 */
vector<trace_t> read_trace(string file)
{
    string line, event;
    int top;
    trace_t one_pair;
    vector<trace_t> the_trace;
    ifstream trace_file(file.c_str());
    if (trace_file)
    {
        while (getline(trace_file, line))
        {
            if (line[0] != '/')
            {
                istringstream stream(line);
                stream >> top;
                stream >> event;
                event.erase(0,1);
                one_pair.first = top;
                one_pair.second = event;
                the_trace.push_back(one_pair);
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the trace file." << endl;
    }
    return the_trace;
}

// *****************************************************************************************************************************
/*
 Function
 read file event_var and create a map with all informations from this file
 key of the map is event
 value of the map is a vector of pair of the variable on wich the event acts and the duration of this event on the variable
 return the map
 */
event_map read_event()
{
    string line, var, event;
    int duration;
    float slope;
    var_top_p event_p;
    vector<var_top_p> event_vect;
    event_map event_m;
    string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/event_var.txt";
    ifstream event_file(file.c_str());
    if (event_file)
    {
        while (getline(event_file, line))
        {
            if (line[0] != '/')
            {
                istringstream stream(line);
                stream >> event;
                stream >> var;
                stream >> slope;
                stream >> duration;
                if(event_m.count(event))
                {
                    event_p.first = var;
                    event_p.second = duration;
                    event_vect.push_back(event_p);
                    event_m[event] = event_vect;
                }
                else
                {
                    event_vect.clear();
                    event_p.first = var;
                    event_p.second = duration;
                    event_vect.push_back(event_p);
                    event_m[event] = event_vect;
                }
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the event_var.txt file." << endl;
    }
    return event_m;
}

// *****************************************************************************************************************************
/*
 Function
 create a linked list with informations of a var file (data of a synthetics patients)
 a patient is a struct with num of the patient and a vector with value of the variable during the chirurgie
 return head of the liste
*/
map_var create_tab_data(string file)
{
    map_var var;
    vector<float> vect_data;
    string line;
    int num_patient = 1;
    ifstream var_file(file.c_str());
    
    if(var_file)
    {
        while(getline(var_file, line))
        {
            stringstream ss(line);
            string str_data;
            while(getline(ss, str_data, ','))
            {
                vect_data.push_back(stof(str_data));
            }
            var[num_patient] = vect_data;
            
            num_patient++;
        }
    }
    return var;
}

// *****************************************************************************************************************************
/*
 Function
 read var file and store informations in a map
 key of the map is the var
 value of the map is the linked list associate
*/
data_map read_data(int nb_var)
{
    map_var var;
    std::vector<float> vect_data;
    data_map all_data;
    
    for (int i=1; i<=nb_var; i++)
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/variables/var_" + to_string(i) + ".csv";
        
        var = create_tab_data(file);
        string var_name = "var_" + to_string(i);
        all_data[var_name] = var;
    }
    return all_data;
}

// *****************************************************************************************************************************
/*
 Function
 create a map informations of a trace file (trace of a synthetics patients)
 the key is a patient number and the value a vector with pair of top and event acts during the chirurgie
 return the map
*/
map_trace create_tab_trace(int nb_obs)
{
    map_trace trace_m;
        
    for (int j=1; j<=nb_obs; j++)
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(j) + ".csv";
        
        vector<trace_t> the_trace = read_trace(file);
        trace_m[j] = the_trace;
    }
    return trace_m;
}

// *****************************************************************************************************************************
/*
 Function
 fix upper bound error in its selection in the vector
*/
int chose_top_plus(int top, int nb_tops_total, int i, vector<trace_t> vect)
{
    int top_plus;
    if(top != nb_tops_total)
    {
        top_plus = vect[i+1].first; //top end event
    }
    else
    {
        top_plus = nb_tops_total+1;
    }
    return top_plus;
}

// *****************************************************************************************************************************
/*
 Function
 if variable in data use its own real duration else use the duration = 0
*/
int var_in_data(int s, vector<var_top_p> variables, string the_var)
{
    int the_dur = 0;
    for(int j=0; j<variables.size(); j++) //browse variables present in the data
    {
        if(variables[j].first == the_var)
        {
            the_dur = variables[j].second;
            break;
        }
    }
    return the_dur;
}

// *****************************************************************************************************************************
/*
 Function
 browse the map with events, find actual event and
 return information of variables for this event (variable name and duration)
*/
vector<var_top_p> find_var(event_map events, string event_ref)
{
    event_map::iterator p;
    vector<var_top_p> variables;
    for(p = events.begin(); p != events.end(); p++) //browse map key=Event, value=vector<pair<var,duration>>
    {
        if(p->first == event_ref )
        {
            variables = p->second; //recover vector<pair<var,duration>> associated with the event
            break;
        }
    }
    return variables;
}

// *****************************************************************************************************************************
/*
 Function
 create an ensemble struct segment_s with segment vector<float> + duration real associate to variable and patient
*/
segment_s create_ensemble(int top, int top_plus, vector<float> segment, int the_dur)
{
    vector<float> the_seg;
    segment_s seg_dur;
        
    for(int v=top-1; v<top_plus-1; v++) //browse segment data associated with the event and the variable
    {
        float one_var = segment.at(v);
        the_seg.push_back(one_var);
    }
    seg_dur.first = the_seg;
    seg_dur.second = the_dur;
    
    return seg_dur;
}

// *****************************************************************************************************************************
/*
 Procedure
 for one variable find the real duration of the variable in data
 create a vector<float> with segment for one event in data
 gathers information in vector<pair<vector<float>,int>>
 save information in the map final
*/
void complete_map(int nb_var, vector<var_top_p> variables, int num_patient, int top, int top_plus, data_map all_data, map_final* final_map, string event_ref)
{
    for(int i=1; i<=nb_var; i++)
    {
        string the_var = "var_"+to_string(i);
        int the_dur = var_in_data(i, variables, the_var);
        
        vector<float> segment = all_data[the_var][num_patient];
        
        segment_s seg_dur = create_ensemble(top, top_plus, segment, the_dur);

        (*final_map)[event_ref][the_var].push_back(seg_dur);
        
    }
}

// *****************************************************************************************************************************
/*
 Procedure
 for one trace of patient find duration of action (top and top_plus)
 find vector with variables and duration associate to the event
 then complete the map
*/
void read_vect(vector<trace_t> vect, int num_patient, event_map events, data_map all_data, map_final* final_map, int nb_var, int nb_tops_total)
{
    for(int i=0; i<vect.size(); i++) //browse vector pair (top, event) = trace of 1 patient
    {
        vector<var_top_p> variables;
        int top = vect[i].first; //top begin event
        
        int top_plus = chose_top_plus(top, nb_tops_total, i, vect);
        
        string event_ref = vect[i].second; //event
        
        variables = find_var(events, event_ref);
        
        complete_map(nb_var, variables, num_patient, top, top_plus, all_data, final_map, event_ref);
    }
}

// *****************************************************************************************************************************
/*
 Main Function
 create a map that contains all data
 map<event,<map<variable,<vector<pair<vector<segment_data>,real_duration>>>>>>
*/
map_final read_files(int nb_obs, int nb_var, int nb_tops_total)
{
    event_map events;
    data_map all_data;
    map_trace trace_m;
    map_trace::iterator p;
        
    events = read_event(); //map key=Event, value=vector<pair<var,duration>>
    all_data = read_data(nb_var); //map key=var, value= map< num patient + vector<float> >
    
    trace_m = create_tab_trace(nb_obs); //linked list num patient + pair<top,action>
    
    map_final final_map;
    
    for(p = trace_m.begin(); p != trace_m.end(); p++) //browse the map with traces of patients
    {
        int num_patient = p->first;
        vector<trace_t> vect = p->second;
        
        read_vect(vect, num_patient, events, all_data, &final_map, nb_var, nb_tops_total);
    }
    return final_map;
}
