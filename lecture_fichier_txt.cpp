//  lecture_fichier_txt.cpp
//  Projet_Sinoquet
//
//  Created by Anne-Emeline Huard on 13/11/2020.
//

#include "lecture_fichier_txt.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

// *****************************************************************************************************************************
//Procedure
//searching for variable name in a line ofe type string
void chercher_variable(string the_line, string tne_variable, int* adr_variable)
{
    string word;
    istringstream stream(the_line);
    stream >> word;
    if (word == tne_variable)
    {
        stream >> *adr_variable;
    }
}

// *****************************************************************************************************************************
//Procedure
//reading the string type line and save all the tops in a vector (reading variable nb_tops)
void combien_de_tops(string the_line, string the_variable, vector<int>* adr_tab_nb_tops)
{
    string word;
    int val;
    istringstream stream(the_line);
    stream >> word;
    if (word == the_variable)
    {
       while (stream >> val)
       {
           adr_tab_nb_tops->push_back(val);
       }
    }
}

// *****************************************************************************************************************************
/*
 Function
 reading line from proba.txt file, saving action and its probability associate in a paire
 one line corresponding 1 main Action and Events associate
 all the elements of a row are saved in a vector
 return the vector
*/
vector<proba_t> ranger_pair(string one_line)
{
    string word, probastr;
    proba_t one_pair;
    vector<proba_t> proba_v;
    
    istringstream stream(one_line);
    while (stream >> word)
    {
        stream >> probastr;
        one_pair.first = word;
        one_pair.second = stof(probastr);
        proba_v.push_back(one_pair);
    }
    return proba_v;
}

// *****************************************************************************************************************************
/*
 Procedure
 reading the file with general settings
 number of observations
 number of variables
 number of actions
 vector with actions / events associate with their probability
*/
void lire_fichier_param_gen(int* adr_nb_obs, int* adr_nb_var, int* adr_nb_actions, vector<int>* adr_tab_nb_tops)
{
    ifstream param_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/param_gen.txt");

    if (param_file)
    {
        string line;
        while (getline(param_file, line))
        {
            if (line[0] != '/')
            {
                chercher_variable(line, "nb_obs", adr_nb_obs );
                chercher_variable(line, "nb_var", adr_nb_var);
                chercher_variable(line, "nb_actions", adr_nb_actions);
                combien_de_tops(line, "nb_tops", adr_tab_nb_tops);
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the file." << endl;
    }
}

// *****************************************************************************************************************************
/*
 Function
 reading file with Action / Events and their probability
 returns a vector which contains vectors containing an action associated with its events and their probabilities
 */
vector<vector<proba_t>> lire_fichier_proba()
{
    ifstream proba_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/proba.txt");
    string line;
    vector<proba_t> proba_v;
    vector<vector<proba_t>> proba_v_v;

    if (proba_file)
    {
        while (getline(proba_file, line))
        {
            if (line[0] != '/')
            {
                proba_v = ranger_pair(line);
                proba_v_v.push_back(proba_v);
            }
        }
    }
    else
    {
        cout << "ERROR: Impossible to open the file." << endl;
    }
    return proba_v_v;
}

// *****************************************************************************************************************************
/*
 Procedure
 using parameters saved from files, in order to create csv files (1 by patient), with trace of actions and events draw lots in function of their probability with a top associate
 */
void generer_traces(int nb_obs, std::vector<int> tab_nb_tops, std::vector<std::vector<proba_t>> vect_proba)
{
    srand((unsigned int)time(0));
    for (int i=0; i<1; i++)
    {
        string const file = "/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/trace_patient_" + to_string(i+1) + ".csv";
        ofstream trace_file(file.c_str());
        
        if (trace_file)
        {
            for (int i=0; i<vect_proba.size() ; i++)
            {
                for (int j=0; j<vect_proba[i].size() ; j++)
                {
                    float nb_alea = (rand() % 100+1); //random between 1 and 100
                    if (vect_proba[i][0].second > nb_alea/100) //ancre proba > au random
                    {
                        trace_file << vect_proba[i][j].first << endl;
                        float nb_alea_bis = (rand() % 100+1); //random between 1 and 100
                        if (vect_proba[i][j].second > nb_alea_bis/100)
                        {
                            trace_file << vect_proba[i][j].first << endl;
                        }
                    }
                    //cout << vect_proba[i][j].first << " " << vect_proba[i][j].second << endl;
                }
            }
         }
        else
        {
            cout << "ERROR: Impossible to open the file." << endl;
        }
    }
}

// *****************************************************************************************************************************
/*
 Procedure
 
 */
void lire_fichier_param_events()
{
    ifstream param_events_file("/Users/Anne-Emeline/Desktop/Projet_Sin/Projet_Sinoquet/param.txt");
    string line;
}
