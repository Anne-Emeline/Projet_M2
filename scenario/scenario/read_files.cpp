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
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DON'T WORK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    
    while(head != nullptr)
    {
        vector<float> tableau;
        tableau = head->donnees;
        cout << "patient : " << head->patient << endl;
        for(int i=0; i<tableau.size(); i++)
        {
            cout << tableau[i] << endl;
        }
        head = head->nxt_patient;
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
    
    for (int i=1; i<=3; i++) //remplacer 1 par nb_var dans code final
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
tableau_trace* create_tab_trace(int nb_obs)
{
    tableau_trace* head = nullptr;
    tableau_trace* prec_node = nullptr;
        
    for (int j=1; j<=2; j++) //remplacer 1 par nb_obs dans code final
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(j) + ".csv";
        
        vector<trace_t> the_trace = read_trace(file);
        
        tableau_trace* current = new tableau_trace;
        current->patient = j;
        current->donnees = the_trace;
        if(head == nullptr)
        {
            head = current;
            //cout << "La tête est le patient n°" << head->patient << endl;
            prec_node = current;
        }
        /*
        cout << "Noeud du patient " << current->patient << endl;
        for(int i=0; i<current->donnees.size(); i++)
        {
            cout << current->donnees[i].second << endl;
        }
         */
        prec_node->nxt_patient = current;
        prec_node = current;
        
    }
    return head;
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
    for(int j=0; j<variables.size(); j++) //parcourir les variables présent dans data
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
 
*/
vector<var_top_p> find_var(event_map events, string event_ref)
{
    event_map::iterator p;
    vector<var_top_p> variables;
    for(p = events.begin(); p != events.end(); p++) //parcourir map key=Event, value=vector<pair<var,duration>>
    {
        if(p->first == event_ref )
        {
            variables = p->second; //récuperer vector<pair<var,duration>> associé à event
            break;
        }
    }
    return variables;
}

// *****************************************************************************************************************************
/*
 Function
 search in all_data map vecto<float> associate with actual variable and patient
*/
vector<float> search_seg(data_map all_data, string the_var, int num_patient)
{
    vector<float> segment;
    data_map::iterator k;
    tableau_var* head_data;
    
    head_data = all_data.find(the_var)->second;
    
    while(head_data->nxt_patient != nullptr)
    {
        if (head_data->patient == num_patient)
        {
            segment = head_data->donnees;
            break;
        }
        head_data = head_data->nxt_patient;
    }
    
    return segment;
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
        
    for(int v=top-1; v<top_plus-1; v++) //récupérer segment data associé à l'event et la variable
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
 Main Function
 
*/
map_final read_files(int nb_obs, int nb_var, int nb_tops_total)
{
    event_map events;
    data_map all_data;
    tableau_trace* tab_trace;
        
    events = read_event(); //map key=Event, value=vector<pair<var,duration>>
    all_data = read_data(nb_var); //map key=var, value=liste chainée num patient + vector<float>
    
    tab_trace = create_tab_trace(nb_obs); //liste chainée num patient + pair<top,action>
    
    map_final final_map;
    
    while(tab_trace != nullptr ) //parcourir la liste chainée comprenant la trace des patients
    {
        int num_patient = tab_trace->patient;
        vector<trace_t> vect = tab_trace->donnees;
        
        //cout << num_patient << endl;
        
        for(int i=0; i<vect.size(); i++) //parcourir le vecteur de pair (top, event) = trace pour 1 patient
        {
            vector<var_top_p> variables;
            int top = vect[i].first; //top begin event
            
            int top_plus = chose_top_plus(top, nb_tops_total, i, vect);
            
            string event_ref = vect[i].second; //event
            
            variables = find_var(events, event_ref);
            
            segments vect_final;
            
            for(int s=1; s<=nb_var; s++)
            {
                string the_var = "var_"+to_string(s);
                int the_dur = var_in_data(s, variables, the_var);
                
                vector<float> segment = search_seg(all_data, the_var, num_patient);
                
                segment_s seg_dur = create_ensemble(top, top_plus, segment, the_dur);

                final_map[event_ref][the_var].push_back(seg_dur);
                
            }
            
        }
        tableau_trace* previous = tab_trace;
        tab_trace = tab_trace->nxt_patient;
        free(previous);
    }
    return final_map;
}
