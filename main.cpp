/*
	Master de Bio-Informatique de l'Université de Nantes 2020 – 2021
	Projet Advanced algorithmics and programming for biologists / Models, methods and algorithms for bioinformatics
	Romain YANG 
	Anne-Emeline HUARD
 */

#include <iostream>
#include <sstream>
#include <fstream>

#include "lecture_fichier_txt.hpp"


using namespace std;


//Fonction principale
int main(int argc, char *argv[])
{
	
    int nb_obs, nb_var, nb_actions;
    vector<int> tab_nb_tops;
    vector<vector<proba_t>> vect_proba;
    map_param map_event_variation_var;
    std::vector<trace_t> one_trace;
    map_min_max val_start_var;
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
    
    val_start_var = lire_fichier_val_start_var();
    /*
    map_min_max::iterator p;
    for (p = val_start_var .begin(); p != val_start_var.end(); p++)
    {
        cout << p->first << endl;
        cout << p->second.first << endl;
        cout << p->second.second << endl;
        
    }
     */
    
    //generer_traces(nb_obs, tab_nb_tops, vect_proba);
    
    map_event_variation_var = lire_fichier_param_events();
    /*
    map_param::iterator p;
    for (p = map_event_variation_var.begin(); p != map_event_variation_var.end(); p++)
    {
        cout << p->first << endl;
        for (int i=0; i<p->second.size();i++)
        {
            cout << p->second[i].first << " " << p->second[i].second << endl;
            
        }
        //cout << p->second << endl;
    }
	*/
    
    for (int i=0; i<1; i++)
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/traces/trace_patient_" + to_string(i+1) + ".csv";
        one_trace = lire_fichier_trace(file);
        /*
        for (int j=0; j< one_trace.size(); j++)
        {
            cout << one_trace[j].first << ' ' << one_trace[j].second << endl;
        }
        */
        
        generate_var_files(one_trace, map_event_variation_var, i+1, nb_var, val_start_var, tab_nb_tops);
    }

	return 0;
}
