#pragma once

#include <string>
#include <vector>
//## Class __Currency__

//Stores information of currencies from currencies.csv
class Currency{
    private:
        std::string name;
        std::string code;
        int numeric_code=0;
        int minor_unit=0;
    public:
        Currency() {}

    Currency(std::string new_name, std::string new_code, int new_numeric_code,int minor_unit){
            name=new_name;
            code=new_code;
            numeric_code=new_numeric_code;
            this->minor_unit=minor_unit;
    }


    const std::string & getCode () const{
        return code;
    }

    void setCode(const std::string& new_code){
        code=new_code;
    }


    const std::string & getName () const {
        return name;
    }

    void setName(const std::string& new_name){
        name=new_name;
    }

    const int & getNumericCode () const {
        return numeric_code;
    }

    void setNumericCode(const int & new_numeric_code){
        numeric_code=new_numeric_code;
    }


    const int & getMinorUnit () const {
        return minor_unit;
    }

    void setMinorUnit(const int & new_minor_unit){
        minor_unit=new_minor_unit;
    }

};


bool getFileContent(const std::string & fileName,std::vector<Currency> &vec);