//  lecture_fichier_txt.cpp
//  Projet_Sinoquet
//
//  Created by Anne-Emeline Huard on 13/11/2020.
//

#include "lecture_fichier_txt.hpp"
#include "simple_functions.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

/*
 Procedure
 reading the file with general settings
 number of observations
 number of variables
 number of actions
 vector with actions / events associate with their probability
*/
void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, vector<int>* adr_tab_nb_tops)
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
 reading file with Action / Events and their probability
 returns a vector which contains vectors containing an action associated with its events and their probabilities
 */
vector<vector<proba_t>> lire_fichier_proba()
{
    ifstream proba_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/proba.txt");
    string line;
    vector<proba_t> proba_v;
    vector<vector<proba_t>> proba_v_v;

    if (proba_file)
    {
        while (getline(proba_file, line))
        {
            if (line[0] != '/')
            {
                proba_v = ranger_pair(line);
                proba_v_v.push_back(proba_v);
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the proba file." << endl;
    }
    return proba_v_v;
}

// *****************************************************************************************************************************
/*
 Function
 reading val_start_var file and return a map with var as index and a pair of min and max value for the var for the anchor B
 */
map_min_max lire_fichier_val_start_var()
{
    val_min_max the_pair;
    map_min_max the_map;
    string line, var;
    int min, max;
    ifstream val_start_var_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/val_start_var.txt");

    if (val_start_var_file)
    {
        while (getline(val_start_var_file, line))
        {
            if (line[0] != '/')
            {
                istringstream stream(line);
                stream >> var;
                stream >> min;
                stream >> max;
                the_pair.first = min;
                the_pair.second = max;
                the_map[var] = the_pair;
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the proba file." << endl;
    }
    return the_map;
}

// *****************************************************************************************************************************
/*
 Procedure
 using parameters saved from files, in order to create csv files (1 by patient), with trace of actions and events draw lots in function of their probability with a top associate
 */
void generer_traces(int nb_obs, vector<int> tab_nb_tops, vector<vector<proba_t>> vect_proba)
{
    srand((unsigned int)time(0));
    for (int i=0; i<1; i++)
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(i+1) + ".csv";
        ofstream trace_file(file.c_str());
        
        if (trace_file)
        {
            for (int i=0; i<vect_proba.size() ; i++)
            {
                for (int j=0; j<vect_proba[i].size() ; j++)
                {
                    float nb_alea = (rand() % 100+1); //random between 1 and 100
                    if (vect_proba[i][0].second > nb_alea/100) //ancre proba > au random
                    {
                        trace_file << vect_proba[i][j].first << endl;
                        float nb_alea_bis = (rand() % 100+1); //random between 1 and 100
                        if (vect_proba[i][j].second > nb_alea_bis/100)
                        {
                            trace_file << vect_proba[i][j].first << endl;
                        }
                    }
                    //cout << vect_proba[i][j].first << " " << vect_proba[i][j].second << endl;
                }
            }
         }
        else
        {
            cout << "ERROR: Impossible to open the trace_patient file." << endl;
        }
    }
}

// *****************************************************************************************************************************
/*
 Function
 reading file with Actions/Events and how they affect variables
 return a map with as index Action/Event associate with a vector which contain variables affected by action/event and how they are affected
 */
map_param lire_fichier_param_events()
{
    ifstream param_events_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/event_var.txt");
    string line, event;
    map_param variation_map;
    vector<pair_variation_var> tab;
    pair_variation_var var_slope_dur;
    if (param_events_file)
    {
        while (getline(param_events_file, line))
        {
            if (line[0] != '/')
            {
                istringstream stream(line);
                stream >> event;
                if (variation_map.count(event))
                {
                    var_slope_dur = creation_var_pair(line);
                    tab.push_back(var_slope_dur);
                    variation_map[event] = tab;
                } else
                {
                    tab.clear();
                    var_slope_dur = creation_var_pair(line);
                    tab.push_back(var_slope_dur);
                    variation_map[event] = tab;
                }
            }
        }
     }
    else
    {
        cout << "ERROR: Impossible to open the event_var.txt file." << endl;
    }
    return variation_map;
}

// *****************************************************************************************************************************
/*
 Function
 reading a trace.csv file and return the trace as vector of pair that contains top and event associate
 */
vector<trace_t> lire_fichier_trace(string file)
{
    std::vector<trace_t> the_trace;
    trace_t one_pair;
    string line, event;
    int top=0;
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

// A METTRE DANS UN AUTRE FICHIER CPP TYPE GENERER_DONNEES_SYNTHETIQUES.CPP
// *****************************************************************************************************************************
// *****************************************************************************************************************************
/*
 Procedure
 create var files with the number of the patient
 complete these files with a value random between the min and max of the variable in function of the number of top associate at the B achor
 */
all_var_m start_var(int start_top, int end_top, int nb_var, map_min_max val_start_var)
{
    map_min_max::iterator p;
    int n = 75; //inclure nb_top_total + 1 ici
    all_var_m map_all_var;
    one_var_m vect_one_var(n,0);
    string variable;
    for (p = val_start_var.begin(); p != val_start_var.end(); p++)
    {
        variable = p->first;
        /*
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/variables/" + variable + "_" + to_string(num_patient) + ".csv";
        ofstream var_file(file.c_str());
         */

        int begining = rand()%(p->second.second - p->second.first) + p->second.first;
        for(int top=start_top; top<end_top; top++)
        {
            vect_one_var[top] = begining;
        }
        map_all_var[variable] = vect_one_var;

    }
    return map_all_var;
}

// *****************************************************************************************************************************
/*
 
 */
void complete_var(vector<pair_variation_var> effect_event, int start_top, int end_top, all_var_m* map_all_var_start)
{
    string variable, param_var;
    int nb_tops = 0, top;
    float slope = 0;
    for (int i=0; i<effect_event.size(); i++)
    {
        variable = effect_event[i].first;
        param_var = effect_event[i].second;
        istringstream stream(param_var);
        stream >> slope;
        stream >> nb_tops;
        nb_tops = nb_tops + start_top;
        
        auto search = map_all_var_start->find(variable);
        cout << "on s'occupe de : " << variable << " qui va du top " << start_top << " à " << nb_tops << endl;
        //for (int v=1; v<search->second.size(); v++)
        //{
          //  cout << search->second[v] << endl;
        //}
        
        
        for(top=start_top ;top < nb_tops; top++)
        {
            //cout << top << " " << search->second[top] << endl;
            search->second[top] = search->second[top-1] * slope;
            
            //cout << "pour la variable " << variable << ", le top " << top << " est complété avec " << search->second[top-1] * slope << endl;
            
        }
        /*
        for (top=nb_tops ;top < end_top; top++)
        {
            search->second[top] = search->second[top-1];
            cout << "pour la variable " << variable << ", le top " << top << " est complétéavec " << search->second[top-1] << endl;
            //cout << top << " " << search->second[top] << endl;
        }
         */
    }
    // mauvaise lecture avec les pointeurs 
    for (all_var_m::iterator p = map_all_var_start->begin(); p != map_all_var_start->end(); p++)
    {
        for (int i=start_top; i<end_top; i++)
        {
            if(p->second[i] == 0)
            {
                p->second[i] = p->second[i-1];
            }
        }

    }
}

// *****************************************************************************************************************************
/*
 
 */
void generate_var_files(vector<trace_t> trace_v, map_param event_var_map, int num_patient, int nb_var, map_min_max val_start_var)
{
    string event;
    vector<pair_variation_var> effect_event;
    all_var_m map_all_var_start;

    for (int i=0; i< trace_v.size(); i++)
    {
        event = trace_v[i].second;
        
        if (event == "B")
        {
            map_all_var_start = start_var(trace_v[i].first, trace_v[i+1].first, nb_var, val_start_var);
        }
        else
        {
            //cout << "Nous sommes à l'venenement : " << event << endl;
            effect_event = event_var_map[event];
            /*
            for (int v=0; v<effect_event.size(); v++)
            {
                cout << effect_event[v].first << endl;
            }
            */
            complete_var(effect_event, trace_v[i].first, trace_v[i+1].first, &map_all_var_start);
            
        }
    }
    
    all_var_m::iterator p;
    for (p = map_all_var_start.begin(); p != map_all_var_start.end(); p++)
    {
        for (int i=1; i<p->second.size(); i++)
        {
            cout << p->first << ' ' << i << ' ' << p->second[i] << endl;
        }

    }
    
    
}
