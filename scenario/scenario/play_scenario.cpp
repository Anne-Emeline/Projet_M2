//
//  play_scenario.cpp
//  scenario
//
//  Created by Anne-Emeline Huard on 04/02/2021.
//

#include "play_scenario.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// *****************************************************************************************************************************
/*
 Procedure
 display variables in 1 line and the first value of the scenario under
*/
void first_display(vector<string> var_name, vector<float> data_display)
{
    for(int i=0; i<var_name.size(); i++)
    {
        cout << var_name[i] << ' ';
    }
    cout << endl;
    for(int v=0; v<data_display.size(); v++)
    {
        cout << "  " <<  data_display[v] << "  ";
    }
    cout << endl;
}

// *****************************************************************************************************************************
/*
 Procedure
 display value of the scenario following the previous ones
*/
void display(vector<float> data_display)
{
    for(int v=0; v<data_display.size(); v++)
    {
        cout << "  " <<  data_display[v] << "  ";
    }
    cout << endl;
}

// *****************************************************************************************************************************
/*
 Procedure
 
*/
void start_scen(map_final donnes_patients_synth, int nb_var, int nb_obs, map_save* save, vector<pair<string,int>>* current_event, map<string,vector<float>>* last_segment)
{
    vector<string> var_name;
    vector<float> data_display;
    for(int i=1; i<=nb_var; i++)
    {
        pair<string,int> one_pair;
        int num = rand()%nb_obs;
        string var = "var_"+to_string(i);
        segment_s data = donnes_patients_synth["B"][var][num];
        
        (*last_segment)[var] = data.first;
        
        one_pair.first = "B";
        one_pair.second = data.second;
        
        (*current_event).push_back(one_pair);
        (*save)[var].push_back(data.first[0]);
        
        var_name.push_back(var);
        data_display.push_back(data.first[0]);
    }
    first_display(var_name, data_display);
}

// *****************************************************************************************************************************
/*
 Function
 research segment with value = precedant value of the scenario (+/- 10)
*/
segment_s best_seg(segments vect_data, float prec_value)
{
    for(int i=0; i<vect_data.size(); i++)
    {
        if(vect_data[i].first[0] >= prec_value-10 && vect_data[i].first[0] <= prec_value+10)
        {
            return vect_data[i];
        }
    }
    int num = rand()%vect_data.size();
    return vect_data[num];
}

// *****************************************************************************************************************************
/*
 Procedure
 
*/
void practice_action(map_final donnes_patients_synth, int i, map_save* save, vector<pair<string,int>>* current_event, string answer, int nb_var, map_save* last_segment)
{
    vector<float> data_display;
    for(int j=1; j<=nb_var; j++)
    {
        pair<string,int> one_pair;
        string var = "var_"+to_string(j);
        segments vect_data = donnes_patients_synth[answer][var];
        one_pair.first = answer;
        float prec_value = (*save)[var][i];
        
        segment_s data = best_seg(vect_data, prec_value);
        
        one_pair.second = data.second;
        (*current_event).push_back(one_pair);
        (*save)[var].push_back(data.first[0]);
        
        data_display.push_back(data.first[0]);
    }
    display(data_display);
}

// *****************************************************************************************************************************
/*
 Procedure
 
*/
void continue_segment(map_final donnes_patients_synthdata, int i, map_save* save, vector<pair<string,int>>* current_event, int nb_var, map_save* last_segment)
{
    
}

// *****************************************************************************************************************************
/*
 Function
 does the user's answer is a real event
 return 1 if yes and 2 if no
*/
int wich_value(string answer, map_final donnes_patients_synth)
{
    int valid;
    if(donnes_patients_synth.count(answer))
    {
        valid = 1;
    }
    else
    {
        valid = 2;
    }
    return valid;
}

// *****************************************************************************************************************************
/*
 Main Function
 create a map that contains all data
 map<event,<map<variable,<vector<pair<vector<segment_data>,real_duration>>>>>>
*/
void play_scenario(map_final donnes_patients_synth, int nb_obs, int nb_var, int nb_tops_total)
{
    srand((unsigned int)time(0));
    string answer;
    map_save save;
    vector<pair<string,int>> current_event;
    map_save last_segment;
    
    for(int i=0; i<nb_tops_total; i++)
    {
        if(i==0)
        {
            start_scen(donnes_patients_synth, nb_var, nb_obs, &save, &current_event, &last_segment);
        }
        
        cin >> answer;
        
        int valid = wich_value(answer, donnes_patients_synth);
        
        switch (valid) {
            case 1:
                practice_action(donnes_patients_synth, i, &save, &current_event, answer, nb_var, &last_segment);
                break;
                
            default:
                continue_segment(donnes_patients_synth, i, &save, &current_event, nb_var, &last_segment);
                break;
        }
    }
}
