//
//  simple_functions.cpp
//  Projet_Sinoquet
//
//  Created by Anne-Emeline Huard on 24/11/2020.
//

#include "simple_functions.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// *****************************************************************************************************************************
/*
 Procedure
 searching for variable name in a line ofe type string
*/
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
/*
 Procedure
 reading the string type line and save all the tops in a vector (reading variable nb_tops)
*/
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
 Function
 reading line from param.txt file
 making pair of variable with its slope and duration
 return the pair
*/
pair_variation_var creation_var_pair(string line)
{
    string event, variable, slope, duration, slope_duration;
    pair_variation_var var_slope_dur;
    istringstream stream(line);
    //cout << line << endl;
    stream >> event;
    stream >> variable;
    stream >> slope;
    stream >> duration;
    slope_duration = slope + ' ' + duration;
    var_slope_dur.first = variable;
    var_slope_dur.second = slope_duration;
        
    return var_slope_dur;
}
