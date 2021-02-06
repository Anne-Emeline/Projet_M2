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
 
*/
void start_scen(map_final donnes_patients_synth, int nb_var, int nb_obs, map_save* save, vector<pair<string,int>>* current_event)
{
    for(int i=1; i<=nb_var; i++)
    {
        pair<string,int> one_pair;
        int num = rand()%nb_obs;
        string var = "var_"+to_string(i);
        segment_s data = donnes_patients_synth["B"][var][num];
        one_pair.first = "B";
        one_pair.second = data.second;
        (*current_event).push_back(one_pair);
        (*save)[var].push_back(data.first[0]);
        
        cout << var << endl;
        cout << data.first[0] << endl;
    }
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
    char answer;
    map_save save;
    vector<pair<string,int>> current_event;
    
    for(int i=0; i<nb_tops_total; i++)
    {
        if(i==0)
        {
            start_scen(donnes_patients_synth, nb_var, nb_obs, &save, &current_event);
        }
        
        cout << "Wish you practice an action ? (y/n)" << endl;
        cin >> answer;
        switch(answer)
        {
            case 'y' : practice_action(i) ; break;
            case 'n' : ; break;
            default:
                cout << "Incorrect answer" << endl;
                cout << "Wish you practice an action ? (y/n)" << endl; break;
        }
        
        
    }
}

using namespace std;
