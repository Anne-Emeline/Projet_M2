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
 Function
 
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
 Procedure
 
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
 
 */
segment_map read_files(int nb_obs, int nb_var, int nb_tops_total)
{
    event_map events = read_event();
    
    for (int i=1; i<=1; i++) //remplacer 1 par nb_var dans code final
    {
        tableau_var* var;
        std::vector<float> vect_data;
        data_map all_data;
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/variables/var_" + to_string(i) + ".csv";
        
        var = create_tab_data(file);
        string var_name = "var_" + to_string(i);
        all_data[var_name] = var;
       
        
    }

    for (int j=1; j<=1; j++) //remplacer 1 par nb_obs dans code final
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(j) + ".csv";
        
        vector<trace_t> the_trace = read_trace(file);
       
        
    }
        
}
