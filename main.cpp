/*
	Master de Bio-Informatique de l'Université de Nantes 2020 – 2021
	Projet Advanced algorithmics and programming for biologists / Models, methods and algorithms for bioinformatics
	Romain YANG 
	Anne-Emeline HUARD
 */

#include <iostream>
#include <sstream>

#include "lecture_fichier_txt.hpp"


using namespace std;


//Fonction principale
int main(int argc, char *argv[])
{
	
    int nb_obs, nb_var, nb_actions;
    vector<int> tab_nb_tops;
    vector<vector<proba_t>> vect_proba;
    //TPtrAction ptr_tete_proba;
    
    lire_fichier_param_gen(&nb_obs, &nb_var, &nb_actions, &tab_nb_tops);
    
    //cout << nb_obs << " " << nb_var << " " << nb_actions <<  endl;
    /*
    for (int i=0; i<4 ; i++)
    {
        cout << tab_nb_tops[i] << endl;
    }
    */
    
    vect_proba = lire_fichier_proba();
    /*
    for (int i=0; i<vect_proba.size() ; i++)
    {
        for (int j=0; j<vect_proba[i].size() ; j++)
        {
            cout << vect_proba[i][j].first << " " << vect_proba[i][j].second << endl;
        }
        
    }
    */
    
    generer_traces(nb_obs, tab_nb_tops, vect_proba);
	

	return 0;
}
