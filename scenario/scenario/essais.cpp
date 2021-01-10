//
//  essais.cpp
//  scenario
//
//  Created by Anne-Emeline Huard on 06/01/2021.
//

#include "essais.hpp"
#include "read_files.cpp"

map_final read_files(int nb_obs, int nb_var, int nb_tops_total)
{
    event_map events;
    data_map all_data;
    tableau_trace* tab_trace;
    event_map::iterator p;
    data_map::iterator k;
        
    events = read_event();
    all_data = read_data(nb_var);
    
    tab_trace = read_trace(nb_obs);
    
    //parcourir tab_trace
    //pour chaque patient parcours trace_t
    //recupe all_data associé
    //recupe duration associé dans events
    
    map_final final_map;
    
    while(tab_trace != nullptr )
    {
        int num_patient = tab_trace->patient;
        vector<trace_t> vect = tab_trace->donnees;
        
        for(int i=0; i<vect.size(); i++)
        {
            int top = vect[i].first;
            int top_plus = vect[i+1].first;
            string event_ref = vect[i].second;
            
            p=events.begin();
            while(p->first != event_ref)
            {
                p++;
            }
            vector<var_top_p> variables = p->second;
            
            segments vect_final;
            
            for(k=all_data.begin(); k!=all_data.end(); k++)
            {
                vector<float> the_seg;
                segment_s seg_dur;

                string var_ref = k->first;
                tableau_var* head_data = k->second;
                
                while(head_data->patient != num_patient)
                {
                    head_data = head_data->nxt_patient;
                }
                
                vector<float> segment = head_data->donnees;
                int the_dur;
                                
                for(int j=0; j<variables.size(); j++)
                {
                    if(variables[j].first == var_ref)
                    {
                        the_dur = variables[j].second;
                    }
                }
                
                for(int v=top; v<top_plus; v++)
                {
                    the_seg.push_back(segment[v]);
                }
                
                seg_dur.first = the_seg;
                seg_dur.second = the_dur;
                ensemble_seg.push_back[seg_dur];
                
                vect_final = final_map[event_ref][var_ref];
                if(vect_final == nullptr)
                {
                    vect_final = ensemble_seg;
                }
                vect_final.insert(vect_final.end(), ensemble_seg.begin(), ensemble_seg.end());
                
                final_map[event_ref][var_ref] = vect_final;
            }

        }
        
        tab_trace = tab_trace->nxt_patient;
    }
    return final_map;
}
