#include <fstream>

#include <cstdio>
#include <vector>
#include <sstream>
#include <string>
#include <dirent.h>
#include <boost/algorithm/string/predicate.hpp>

#include "../include/ExchangeRate.hpp"
#include "../include/ExchangeBoard.hpp"

typedef std::unordered_map<std::string,std::shared_ptr<ExchangeRate>> unord_map ;

//Function to create unordered map containing the base, quote and ExchangeRate pointer  key<Base>, key<Quote>, value<ExchangeRate pointer>
nested_unord_map bid_insert(unord_map &inmap, ExchangeRate &ex_rate, nested_unord_map &umap){
    std::shared_ptr<ExchangeRate> er_pointer=std::make_shared<ExchangeRate>(ex_rate);
    inmap[ex_rate.getQuote()]=er_pointer;
    umap[ex_rate.getBase()]=inmap;
    return umap;
}

//Function to input the exchange_rate.csv file and output 1 nested unordered map, key<Base>, key<Quote>, value<ExchangeRate pointer>
bool const insertCSV(nested_unord_map &umap){   

    //Loop through directory to obtain files
    /*const char * path="/home/margon/projects/back-to-cpp/datasets";
    DIR *dir;
    std::string file_name;
    struct dirent *reader;
    vector<string> filenames;

    cout<<file_name;

    if ((dir=opendir(path))!=NULL){
        while((reader=readdir(dir))!=NULL){
            if(boost::algorithm::ends_with(reader->d_name, ".csv")){
                file_name= string(path) + "/" +reader->d_name;
                filenames.push_back(file_name);
            }
        }
        closedir (dir);
    }else{
        cout<<"Cannot open directory";
    }


    //MAKE SURE DIR, PATH AND READER DELETED
    //cout<<dir<<path<<reader;
    //delete path, dir, reader;
 
    cout<<file_name<<endl;
    
    if (FILE *fp= fopen(file_name.c_str(),"r")){
        ExchangeRate ex_rate;
        char c;
        string base,quote, line2;
        double bid,ask,last;
    
    char buff[1024];
    short stringlength=4;

    while (size_t len = fread(buff, sizeof(char) ,(size_t)stringlength, fp)){
    //while (size_t len= fread(&base,1,5,fp)<5){
        cout<<"new"<<endl;
        cout<<buff<<endl;
        unsigned first = buff.find(",");
        unsigned last = buff.find(",");
        string strNew = str.substr (first,last-first);
    }


 //       while(fscanf(fp, "%s,%s,%d,%d,%d",&base, &quote,&bid,&ask,&last)){
            //fread(base,quote,bid,ask,last);
            //printf(base, quote,bid,ask,last);
            //ex_rate.setBase(string(base)).setQuote(quote).setBid(bid);
 //       }
        fclose(fp);
    }*/

    //getline(ifstream(file_name)) ;

    const std::string & fileName="datasets/exchange_rates.csv";  
    // Open the File
    std::ifstream file(fileName.c_str());

    if(!file)
    {
        std::cout << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }
    
    
    std::string line;
    unord_map aud_bid;
    unord_map eur_bid;
    unord_map gbp_bid;
    unord_map usd_bid;
    unord_map nzd_bid;    
    
    // Skip 1st line and read the next line from File untill it reaches the end.
    std::getline(file,line);
    while(std::getline(file,line))
    {   
        std::istringstream ss(line);
        ExchangeRate ex_rate;

        for (int i = 0; i < 5; i++){
            std::getline(ss, line, ',');
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
            std::cout<<"new currency: "<<ex_rate.getBase();
            return false;
        }      
    };

    //Close The File
    file.close();
    return true;
}