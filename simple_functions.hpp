//
//  simple_functions.hpp
//  Projet_Sinoquet
//
//  Created by Anne-Emeline Huard on 24/11/2020.
//

#ifndef simple_functions_hpp
#define simple_functions_hpp

#include <stdio.h>
#include<string>
#include <vector>
#include <map>

void chercher_variable(std::string the_line, std::string tne_variable, int* adr_variable);

void combien_de_tops(std::string the_line, std::string the_variable, std::vector<int>* adr_tab_nb_tops);

using proba_t = std::pair<std::string, float>;

std::vector<proba_t> ranger_pair(std::string one_line);

using pair_variation_var = std::pair<std::string,std::string>;

pair_variation_var creation_var_pair(std::string line);

#endif /* simple_functions_hpp */
