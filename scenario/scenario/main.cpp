//
//  main.cpp
//  scenario
//
//  Created by Anne-Emeline Huard on 07/12/2020.
//

#include <iostream>
#include <vector>

#include "read_files.hpp"
#include "essais.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    int nb_obs, nb_var, nb_actions, nb_tops_total;
    vector<int> tab_nb_tops;
    map_final donnes_patients_synth;
    
    lire_fichier_param_gen(&nb_obs, &nb_var, &nb_actions, &tab_nb_tops, &nb_tops_total);

    donnes_patients_synth = read_files(nb_obs, nb_var, nb_tops_total);

    
    return 0;
}
