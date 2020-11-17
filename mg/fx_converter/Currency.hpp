#pragma once

using namespace std;
#include <string>
#include <vector>
//## Class __Currency__

class Currency{
    private:
        string name;
        string code;
        int numeric_code;
        int minor_unit;
    public:
        Currency() {}

    Currency(string new_name, string new_code, int new_numeric_code,int minor_unit){
            name=new_name;
            code=new_code;
            numeric_code=new_numeric_code;
            this->minor_unit=minor_unit;
    }


    const string & getCode () const{
        return code;
    }

    void setCode(string new_code){
        code=new_code;
    }


    const string & getName () const {
        return name;
    }

    void setName(string new_name){
        name=new_name;
    }

    const double & getNumericCode () const {
        return numeric_code;
    }

    void setNumericCode(int new_numeric_code){
        numeric_code=new_numeric_code;
    }


    const double & getMinorUnit () const {
        return minor_unit;
    }

    void setMinorUnit(int new_minor_unit){
        minor_unit=new_minor_unit;
    }

};


bool getFileContent(string fileName,vector<Currency> &vec);