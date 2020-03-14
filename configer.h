#ifndef _CONFIGER_H_
#define _CONFIGER_H_

#include <iostream>
#include "yaml-cpp/yaml.h"

using std::cout;
using std::endl;


//c++ CONFIG class  (  yaml or ini)
class Configer  
{
public:
    YAML::Node _yamlCfg;   
    Configer(){
        ;
    }
    void Init( std::string cfgPath  ){
        _yamlCfg = YAML::LoadFile( cfgPath );
    }
    /**
    * @brief  从yaml配置文件中读取数据 T is datatype: int double string
    * @param  [in] levelMaster  1级ID  必须有
    * @param  [in] levelNext    2级ID  若无请输入空字符串
    * @param  [in,out]
    * @retval     读取结果
    * @note
    */
    template<typename T> T 
    yamlRead( std::string levelMaster, std::string levelNext = ""){
        T ret;
        if( !levelNext.empty() ){
            try {
                ret = _yamlCfg[ levelMaster ][ levelNext ].as<T>();
                std::cout<<"Found parameter: "<< levelMaster + "-" + levelNext
                        <<": "<< ret <<std::endl;
                return ret;
            } catch (std::exception e ) {
                std::cout<<"Can not find parameter: "<< levelMaster + "-" + levelNext
                        <<" program exit!" <<std::endl;
                exit(1);  //找不到直接退出
            }
        }
        else{
            try {
                ret = _yamlCfg[ levelMaster ].as<T>();
                std::cout<<"Found parameter: "<< levelMaster <<": "<< ret <<std::endl;
                return ret;
            } catch (std::exception e ) {
                std::cout<<"Can not find parameter: "<< levelMaster <<" program exit!" <<std::endl;
                exit(1);  //找不到直接退出
            }
        }
    }
    ~Configer(){
        ;
    }
private:
    ;
};

#endif



