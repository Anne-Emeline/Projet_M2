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

void start_scen(map_final donnes_patients_synth, int nb_var, int nb_obs)
{
    for(int i=1; i<=nb_var; i++)
    {
        int num = rand()%nb_obs;
        string var = "var_"+to_string(i);
        cout << var << endl;
        segment_s data = donnes_patients_synth["B"][var][num];
    }
    
}

void play_scenario(map_final donnes_patients_synth, int nb_obs, int nb_var, int nb_tops_total)
{
    srand((unsigned int)time(0));
    
    for(int i=0; i<nb_tops_total; i++)
    {
        if(i==0)
        {
            start_scen(donnes_patients_synth, nb_var, nb_obs);
        }
    }
}

using namespace std;
