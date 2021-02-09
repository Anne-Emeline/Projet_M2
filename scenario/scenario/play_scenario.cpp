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
#include <stdio.h>

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
    cout << 'B' << endl;
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
 for the begining of the scenario program randomly chooses the first value between all the data
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
 Function
 create a random float +/- equal to the precedent value
 add noise in the scenario
*/
float random_float(float prec_value)
{
    int born_m = int(prec_value-2);
    float dec = float(rand()%101)/100;
    int entier = rand()%5 + born_m;
    return entier+dec;
}

// *****************************************************************************************************************************
/*
 Function
 if a segment exist on map_final for the event chose best segment and value to displayed
 else displayed a constant value because the event don't have effect on the variable
*/
float test_next(map_final donnes_patients_synth, string answer, string var, float prec_value, vector<pair<string,int>>* current_event)
{
    pair<string,int> one_pair;
    segments vect_data;
    segment_s data;
    float add;
    
    if(donnes_patients_synth[answer].count(var))
    {
        vect_data = donnes_patients_synth[answer][var];
        data = best_seg(vect_data, prec_value);
        
        one_pair.first = answer;
        one_pair.second = data.second;
        (*current_event).push_back(one_pair);
        add = data.first[0];
    }
    else
    {
        add = random_float(prec_value);
    }
    return add;
}

// *****************************************************************************************************************************
/*
 Procedure
 the user has made an action
 program have to find the best value to display considering the last one
*/
void practice_action(map_final donnes_patients_synth, int i, map_save* save, vector<pair<string,int>>* current_event, string answer, int nb_var, map_save* last_segment)
{
    vector<float> data_display;
    for(int j=1; j<=nb_var; j++)
    {
        float add;
        
        string var = "var_"+to_string(j);
        float prec_value = (*save)[var][i-1];
        
        add = test_next(donnes_patients_synth, answer, var, prec_value, current_event);
        
        (*save)[var].push_back(add);
        data_display.push_back(add);
    }
    display(data_display);
}

// *****************************************************************************************************************************
/*
 Function
 find place in the vector of the previous value of the scenario
 if the next value is the end of the vector return last value display
*/
float place(vector<float> prec_seg, float prec_value)
{
    vector<float>::iterator it;
    for(it=prec_seg.begin(); it<prec_seg.end(); it++)
    {
        if(*it == prec_value && it+1 != prec_seg.end())
        {
            return *it+1;
        }
    }
    return random_float(prec_value);
}

// *****************************************************************************************************************************
/*
 Procedure
 user doesn't make action or make action wich doesn't exist
 continue scenario with the rest of the previous segment or a more or less constant value
*/
void continue_segment(map_final donnes_patients_synthdata, int i, map_save* save, vector<pair<string,int>>* current_event, int nb_var, map_save* last_segment)
{
    vector<float> data_display;
    for(int j=1; j<=nb_var; j++)
    {
        pair<string,int> one_pair;
        string var = "var_"+to_string(j);
        
        vector<float> prec_seg = (*last_segment)[var];
        float prec_value = (*save)[var][i-1];
        float v = place(prec_seg, prec_value);
        
        (*save)[var].push_back(v);
        data_display.push_back(v);
    }
    display(data_display);
}

// *****************************************************************************************************************************
/*
 Function
 delete all actions before the last user action
*/
void erase_elements(vector<proba_t>* vect_proba, int i)
{
    for(int j=0; j<=i; j++)
    {
        (*vect_proba).erase((*vect_proba).begin());
    }
}

// *****************************************************************************************************************************
/*
 Function
 if the user's action isn't in the vector of action that mean this action isn't chronologically possible
*/
bool chronology(string answer, vector<proba_t>* vect_proba)
{
    for(int i=0; i<(*vect_proba).size(); i++)
    {
        if((*vect_proba)[i].first == answer)
        {
            erase_elements(vect_proba, i);
            return true;
        }
    }
    return false;
}

// *****************************************************************************************************************************
/*
 Function
 check if the user's action is chronologically possible
*/
int test_chron(string answer, vector<proba_t>* vect_proba)
{
    int valid;
    if(chronology(answer, vect_proba))
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
 Function
 does the user's answer is a real event
 return 1 if yes and 2 if no
*/
int wich_value(string answer, map_final donnes_patients_synth, vector<proba_t>* vect_proba)
{
    int valid = 0;
    if(donnes_patients_synth.count(answer))
    {
        valid = test_chron(answer, vect_proba);
    }
    return valid;
}

// *****************************************************************************************************************************
/*
 Main Function
 
*/
void play_scenario(map_final donnes_patients_synth, int nb_obs, int nb_var, int nb_tops_total, vector<proba_t> vect_proba)
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
            continue;
        }
        
        getline(cin, answer);
        
        int valid = wich_value(answer, donnes_patients_synth, &vect_proba);
        
        switch (valid) {
            case 1:
                practice_action(donnes_patients_synth, i, &save, &current_event, answer, nb_var, &last_segment);
                break;
                
            case 2:
                cout << "Invalid action" << endl;
                i--;
                break;
                
            default:
                continue_segment(donnes_patients_synth, i, &save, &current_event, nb_var, &last_segment);
                break;
        }
    }
    
    cout << "End of scenario" << endl;
}
