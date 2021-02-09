//
//  main.cpp
//  scenario
//
//  Created by Anne-Emeline Huard on 07/12/2020.
//

#include <iostream>
#include <vector>

#include "read_files.hpp"
#include "play_scenario.hpp"

using namespace std;

int main() {
    
    int nb_obs, nb_var, nb_actions, nb_tops_total;
    vector<int> tab_nb_tops;
    vector<proba_t> vect_proba;
    map_final donnes_patients_synth;
    
    lire_fichier_param_gen(&nb_obs, &nb_var, &nb_actions, &tab_nb_tops, &nb_tops_total);
    
    vect_proba = lire_fichier_proba();

    donnes_patients_synth = read_files(nb_obs, nb_var, nb_tops_total);
    
    play_scenario(donnes_patients_synth, nb_obs, nb_var, nb_tops_total, vect_proba);

    return 0;
}
