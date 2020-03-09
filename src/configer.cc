#include <iostream>
#include "yaml-cpp/yaml.h"
#include "utility/configer.h"


//--------------------------test func area------------------------
/**
//static void configerTest(){
void configerTest(){
    Configer  cfg("../testconfig.yaml");
    int a  = cfg.yamlRead<int>("testi");
    double d  = cfg.yamlRead<double>("testd");
    std::string s  = cfg.yamlRead<std::string>("tests");
    cout << "test yaml read testi:" << a << endl; 
    cout << "test yaml read testd:" << d << endl; 
    cout << "test yaml read tests:" << s << endl; 
}
*/
