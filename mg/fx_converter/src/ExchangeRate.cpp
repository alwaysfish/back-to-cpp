#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <unordered_map>
using namespace std;

#include "ExchangeRate.hpp"
#include "ExchangeBoard.hpp"

typedef unordered_map<string,shared_ptr<ExchangeRate>> unord_map ;

//Function to create unordered map containing the base, quote and ExchangeRate pointer  key<Base>, key<Quote>, value<ExchangeRate pointer>
nested_unord_map bid_insert(unord_map &inmap, ExchangeRate &ex_rate, nested_unord_map &umap){
    shared_ptr<ExchangeRate> er_pointer=make_shared<ExchangeRate>(ex_rate);
    inmap[ex_rate.getQuote()]=er_pointer;
    umap[ex_rate.getBase()]=inmap;
    return umap;
}

//Function to input the exchange_rate.csv file and output 1 nested unordered map, key<Base>, key<Quote>, value<ExchangeRate pointer>
bool const insertExchange(const string & fileName,  nested_unord_map &umap)
{
    // Open the File
    ifstream file(fileName.c_str());

    if(!file)
    {
        std::cout << "Cannot open the File : "<<fileName<<endl;
        return false;
    }
    
    
    string line;
    unord_map aud_bid;
    unord_map eur_bid;
    unord_map gbp_bid;
    unord_map usd_bid;
    unord_map nzd_bid;    
    
    // Skip 1st line and read the next line from File untill it reaches the end.
    getline(file,line);
    while(getline(file,line))
    {   
        istringstream ss(line);
        ExchangeRate ex_rate;

        for (int i = 0; i < 5; i++){
            getline(ss, line, ',');
            if (i==0){
                ex_rate.setBase(line);
            }
            else if(i==1){
                ex_rate.setQuote(line);
            }

            else if(i==2){
                ex_rate.setBid(stod(line));                

            }
            else if(i==3){ 
                ex_rate.setAsk(stod(line));

            }
            else if(i==4){ 
                ex_rate.setLast(stod(line));
            }
        }
        
        if (ex_rate.getBase()=="AUD"){
            umap=bid_insert(aud_bid,ex_rate,umap);    
        }
        else if (ex_rate.getBase()=="EUR"){
            umap=bid_insert(eur_bid,ex_rate,umap);
        }
        else if (ex_rate.getBase()=="GBP"){
            umap=bid_insert(gbp_bid,ex_rate,umap);
        }
        else if (ex_rate.getBase()=="NZD"){
            umap=bid_insert(nzd_bid,ex_rate,umap);
        }
        else if (ex_rate.getBase()=="USD"){
            umap=bid_insert(usd_bid,ex_rate,umap);
        }
        else if((ex_rate.getBase()!="AUD")||(ex_rate.getBase()!="EUR")||(ex_rate.getBase()!="GBP")||(ex_rate.getBase()!="NZD")||(ex_rate.getBase()!="USD")){
            cout<<"new currency: "<<ex_rate.getBase();
            return false;
        }      
    };

    //Close The File
    file.close();
    return true;
}