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

/*
 Procedure
 searching for variable name in a line ofe type string
*/
void chercher_variable(string the_line, string tne_variable, int* adr_variable)
{
    string word;
    istringstream stream(the_line);
    stream >> word;
    if (word == tne_variable)
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
 Function read file event_var and create a map with all informations from this file
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
tableau_var* create_tab_data(string file)
{
    tableau_var* head = nullptr;
    tableau_var* prec_node = nullptr;
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
            tableau_var* current = new tableau_var;
            current->patient = num_patient;
            current->donnees = vect_data;
            if(head == nullptr)
            {
                head = current;
                prec_node = current;
            }
            prec_node->nxt_patient = current;
            prec_node = current;
            num_patient++;
        }
    }
    
    return head;
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
    tableau_var* var;
    std::vector<float> vect_data;
    data_map all_data;
    
    for (int i=1; i<=1; i++) //remplacer 1 par nb_var dans code final
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
 create a linked list with informations of a trace file (trace of a synthetics patients)
 a patient is a struct with num of the patient and a vector with pair of top and event acts during the chirurgie
 return head of the liste
*/
tableau_trace* read_trace(int nb_obs)
{
    tableau_trace* head = nullptr;
    tableau_trace* prec_node = nullptr;
    
    for (int j=1; j<=1; j++) //remplacer 1 par nb_obs dans code final
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(j) + ".csv";
        
        vector<trace_t> the_trace = read_trace(file);
        
        tableau_trace* current = new tableau_trace;
        current->patient = j;
        current->donnees = the_trace;
        if(head == nullptr)
        {
            head = current;
            prec_node = current;
        }
        prec_node->nxt_patient = current;
        prec_node = current;
        
    }
    return head;
}

// *****************************************************************************************************************************
/*
 Main Function
 
 */
map_final read_files(int nb_obs, int nb_var, int nb_tops_total)
{
    event_map events;
    data_map all_data;
    tableau_trace* tab_trace;
    event_map::iterator p;
    data_map::iterator k;
        
    events = read_event();
    all_data = read_data(nb_var);
    
    tab_trace = read_trace(nb_obs);
    
    //parcourir tab_trace
    //pour chaque patient parcours trace_t
    //recupe all_data associé
    //recupe duration associé dans events
    
    vector<float> the_seg;
    segments ensemble_seg;
    map_final final_map;
    
    while(tab_trace != nullptr )
    {
        int num_patient = tab_trace->patient;
        vector<trace_t> vect = tab_trace->donnees;
        
        for(int i=0; i<vect.size(); i++)
        {
            int top = vect[i].first;
            int top_plus = vect[i+1].first;
            string event_ref = vect[i].second;
            
            for(p=events.begin(); p!=events.end(); p++)
            {
                string event = p->first;
                vector<var_top_p> variables = p->second;
                
                if(event_ref == event)
                {
                    for(k=all_data.begin(); k!=all_data.end(); k++)
                    {
                        string var_ref = k->first;
                        tableau_var* head_data = k->second;
                        
                        while(head_data->patient != num_patient)
                        {
                            head_data = head_data->nxt_patient;
                        }
                        vector<float> segment = head_data->donnees;

                        for(int j=0; j<variables.size(); j++)
                        {
                            string the_var = variables[j].first;
                            int the_dur = variables[j].second;
                            
                            if(var_ref == the_var)
                            {
                                for(int v=top; v<top_plus; v++)
                                {
                                    the_seg.push_back(segment[v]);
                                }
                            }
                            
                            segment_s seg_pair;
                            seg_pair.first = the_seg;
                            seg_pair.second = the_dur;
                            ensemble_seg.push_back(seg_pair);
                            
                        }
                    }
                }
            }
            
            
            
        }
        
        tab_trace = tab_trace->nxt_patient;
    }
        
}
