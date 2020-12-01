//  lecture_fichier_txt.hpp
//  Projet_Sinoquet
//
//  Created by Anne-Emeline Huard on 13/11/2020.
//

#ifndef __lecture_fichier_txt_hpp__
#define __lecture_fichier_txt_hpp__

#include <stdio.h>
#include<string>
#include <vector>
#include <map>

void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, std::vector<int>* adr_tab_nb_tops);

using proba_t = std::pair<std::string, float>;

std::vector<std::vector<proba_t>> lire_fichier_proba();

using val_min_max = std::pair<int, int>;

using map_min_max = std::map<std::string, val_min_max>;

map_min_max lire_fichier_val_start_var();

void generer_traces(int nb_obs, std::vector<int> tab_nb_tops, std::vector<std::vector<proba_t>> vect_proba);

using pair_variation_var = std::pair<std::string,std::string>;

using map_param = std::map<std::string,std::vector<pair_variation_var>>;

map_param lire_fichier_param_events();

using trace_t = std::pair<int, std::string>;

std::vector<trace_t> lire_fichier_trace(std::string file);

// *****************************************************************************************************************************

using one_var_m = std::vector<float>;

using all_var_m = std::map<std::string, one_var_m>;

void generate_var_files(std::vector<trace_t> trace_v, map_param event_var_map, int num_patient, int nb_var, map_min_max val_start_var, vector<int> tab_nb_tops);



#endif /* lecture_fichier_txt_hpp */
