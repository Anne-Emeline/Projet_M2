//
//  read_files.hpp
//  scenario
//
//  Created by Anne-Emeline Huard on 07/12/2020.
//

#ifndef read_files_hpp
#define read_files_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, std::vector<int>* adr_tab_nb_tops, int* adr_nb_tops_total);

using segment_s = std::pair<std::vector<float>, int>;

using segments = std::vector<segment_s>;

using s_map = std::map<std::string, segments>;

using map_final = std::map<std::string, s_map>;

//using variables_p = std::pair<std::string, segments>;

//using segment_map = std::map<std::string, std::vector<variables_p>>;

map_final read_files(int nb_obs, int nb_var, int nb_tops_total);

using trace_t = std::pair<int, std::string>;

using var_top_p = std::pair<std::string, int>;

using event_map = std::map<std::string, std::vector<var_top_p>>;

struct tableau_var{
    int patient;
    std::vector<float> donnees;
    tableau_var* nxt_patient;
};
using data_map = std::map<std::string, tableau_var*>;

struct tableau_trace{
    int patient;
    std::vector<trace_t> donnees;
    tableau_trace* nxt_patient;
};


#endif /* read_files_hpp */
