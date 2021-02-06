//
//  play_scenario.hpp
//  scenario
//
//  Created by Anne-Emeline Huard on 04/02/2021.
//

#ifndef play_scenario_hpp
#define play_scenario_hpp

#include <stdio.h>
#include "read_files.hpp"

void play_scenario(map_final donnes_patients_synth, int nb_obs, int nb_var, int nb_tops_total);

using map_save = std::map<std::string, std::vector<float>>;

#endif /* play_scenario_hpp */
