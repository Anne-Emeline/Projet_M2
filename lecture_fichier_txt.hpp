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

void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, std::vector<int>* adr_tab_nb_tops);

using proba_t = std::pair<std::string, float>;

std::vector<std::vector<proba_t>> lire_fichier_proba();

void generer_traces(int nb_obs, std::vector<int> tab_nb_tops, std::vector<std::vector<proba_t>> vect_proba);

//void generer_trace(TPtrAction tete, int nb_obs, std::vector<int> adr_tab_nb_tops);

#endif /* lecture_fichier_txt_hpp */
