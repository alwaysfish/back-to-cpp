#include <vector>
#include <algorithm>

#include "ExchangeRate.hpp"
#include "ExchangeBoard.hpp"

//Select conversion yielding maximum num
double maxCurrency(unordered_map<string, double> curr_to_amount){
    double current_max = 0;
    string curr_conv;
    
    for(const auto& it:curr_to_amount){
        if (it.second>current_max){
            curr_conv=it.first;
            current_max=it.second;
        }
    }
    return current_max;
}
double conversion_intermed(unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>>& umap, const string &curr_from, const string &intermed, const string &curr_to, const double &amount){
    vector <string> bases;
    for(const auto& base:umap){
        bases.push_back(base.first);
        
    }
    
    auto to_inter= umap[curr_from].find(curr_to+intermed);
    auto from_inter =umap[curr_to].find(curr_from+intermed);


    std::cout<<to_inter->second;
    std::cout<<from_inter->second;
    /*if(){

    }*/

    return 0;
}
//Conversion calculator
double const corr_mon(unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>>& umap, const string &_curr_from, const string &_curr_to, const double &amount){
    
    unordered_map<string, double> curr_to_amount;
    double convers;
    vector<string> base_curr;

    //Standardizing input
    const string curr_from=_curr_from;
    const string curr_to=_curr_to;
    bool is_num=isdigit(amount);

    //Validation
    if(curr_from==curr_to){
        std::cout<<"Cannot exchange currency pair with same currency code"<<endl;
        return 0;
    }else if (is_num=false){
        std::cout<<"Amount must be numeric "<<amount<<endl;
        return 0;
    }else if(amount<=0){
        std::cout<<"Cannot exchange amount less than or equal to 0"<<endl;
        return 0;
    }else if ((umap.find(curr_from)!=umap.end())&&(umap[curr_to].find(curr_from)!=umap[curr_to].end())){
        std::cout<<"Cannot exchange currency pair above-- make sure your currency from is correct";
        return 0;
    }else if ((umap.find(curr_to)!=umap.end())&&(umap[curr_from].find(curr_to)!=umap[curr_from].end())){
        std::cout<<"Cannot exchange currency pair above-- make sure your currency to is correct";
        return 0;
    }


    //Check if invalid input and conversion to be done
    unordered_map<string,shared_ptr<ExchangeRate>>::iterator it_to = umap[curr_from].find(curr_to); 

    for(const auto& base:umap){
        for(const auto& quote:base.second){

            //Check if currency from is a base currency and whether the currency to is a quote currency or if it requires intermediary
            if(curr_from==base.first){
                if (quote.first==curr_to){
                    convers=amount*quote.second -> getBid();
                    curr_to_amount[curr_to]=convers;
                    std::cout<<amount<<" "<<quote.first<<endl;
                }
                else if (quote.first!=curr_to){
                    if(umap.find(quote.first)!=umap.end()){
                    //if (find(base_curr.begin(),base_curr.end(),quote.first)!=base_curr.end()){
                        if (umap[quote.first][curr_to]){
                            double from_inter=umap[curr_from][quote.first]-> getBid();
                            double inter_to=umap[quote.first][curr_to]->getBid();
                            return(amount*from_inter*inter_to);
                            convers=(amount*from_inter*inter_to);
                            curr_to_amount[quote.first]=convers;
                        }
                        else if(umap[curr_to][quote.first]){
                            double from_inter=umap[curr_from][quote.first]-> getBid();
                            double inter_to=umap[curr_to][quote.first]->getAsk();
                            return(amount*from_inter*inter_to);
                            convers=(amount*from_inter/inter_to);
                            curr_to_amount[quote.first]=convers;
                        }
                        curr_to_amount[quote.first]=convers;
                        std::cout<<curr_to_amount[quote.first]<<endl;
                    }

                }
            }

            //Check if currency from is a quote currency
            if(curr_from==quote.first){
                if(base.first==curr_to){
                    convers=amount*umap[base.first][quote.first]->getBid();
                    curr_to_amount[base.first]=convers;

                }
                else if(base.first!=curr_to){
                    if (umap.find(quote.first)!=umap.end()){
                        cout<<curr_from<<" "<<quote.first<<" "<<curr_to;
                        if (umap[base.first][curr_to]){
                            double from_inter=umap[curr_from][base.first]->getAsk();
                            double inter_to=umap[base.first][curr_to]->getBid();
                            convers=(amount*inter_to/from_inter);
                            curr_to_amount[quote.first]=convers;
                        }                
                        else if(umap[curr_to][base.first]){
                            double from_inter=umap[curr_from][base.first]-> getAsk();
                            double inter_to=umap[curr_to][base.first]->getAsk();
                            convers=((amount/from_inter)/inter_to);
                            curr_to_amount[quote.first]=convers;
                        }

                    }
                }
            }
            
        }
    }
    double conversion=maxCurrency(curr_to_amount);
    std::cout<<amount<<" "<<curr_from<<" successfully changed to "<<conversion<<" "<<curr_to;
    return conversion;
};
