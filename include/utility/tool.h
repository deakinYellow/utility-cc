/*
 *  @brief:  C/C++编程常用小工具: LOG,延时,系统时间,键盘输入等
 *  @author: Deakin
 *  @email:  deakinhwang@163.com
 *  @last modify:  2019/12/25
 */

#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include "time.h"


using std::cout;
using std::endl;
using std::string;

#define __need_timeval

//--------------------------------LOG ABOUT---------------------------------------
//在需要开启debuglog的目标源文件开头包含tool.h前引入,如果全局开启,则在这里引入
#//define USING_MLOGD
#ifdef USING_MLOGD
    #define MLOGD(fmt,...)  printf("%s [D] %22s | \033[0;0;32m " fmt " \033[0m\n",stool::sys_ms_ts_str().c_str(), __FUNCTION__, ##__VA_ARGS__)
#else
    #define MLOGD(fmt,...)  ;
#endif

#define MLOGI(fmt,...)  printf("%s [I] %22s |" fmt "\n",GetSystemTimeStr().c_str(), __FUNCTION__, ##__VA_ARGS__)
#define MLOGW(fmt,...)  printf("%s [W] %22s | \033[0;0;33m " fmt "\033[0m\n", stool::sys_ms_ts_str().c_str(), __FUNCTION__, ##__VA_ARGS__)
#define MLOGE(fmt,...)  printf("%s [E] %22s | \033[0;33;31m " fmt "\033[0m\n",stool::sys_ms_ts_str().c_str(), __FUNCTION__, ##__VA_ARGS__)
//--------------------------------LOG ABOUT---------------------------------------

//--------------------------------TIME ABOUT-------------------------------------
///特指CPU消耗的时间( 延时函数不会消耗太多CPU实际使用时间)
#define  TIME_START clock_t startTimeT = clock()
#define  TIME_END   clock_t endTimeT = clock()
#define  TIME_COST  ( endTimeT - startTimeT ) / (CLOCKS_PER_SEC / 1000 )
#define  TIME_COSTLOGD MLOGD("cost time: %f ms.",(float)TIME_COST )


#include <unistd.h>
#include <sys/time.h>
#define TPUSLEEP(x)     usleep((x))
#define TPMSLEEP(x)     usleep( (x)*1000 )
//---------------------------------TIME ABOUT-------------------------------------

//---------------------------------OPT RET------------------------------------------
#define TPOK   0
#define TPFAIL   1
//---------------------------------OPT RET END------------------------------------------

namespace  stool {


//获取系统毫秒级时间戳
static inline uint64_t sys_ms_ts( void ) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000 + tv.tv_usec/1000;  //获取毫秒
}

//毫秒级时间戳格式化输出 //格式如下:2019/07/14 00:48:13.298
static std::string inline ms_ts2str( uint64_t stamp ){
    time_t tt = (time_t)( stamp / 1000 );
    struct tm *ttime;
    ttime = localtime(&tt);
    char date[64];
    strftime(date,64,"%Y/%m/%d %H:%M:%S",ttime);
    std::string timeStr;
    char msStr[4];
    int ms =( int )( stamp % 1000);
    sprintf(msStr, "%d", ms );
    timeStr += date;
    if( ms < 100 && ms > 10 )
        timeStr += ".0";
    else if( ms < 10 )
        timeStr += ".00";
    else
        timeStr += ".";
    timeStr += msStr;
    return timeStr;
}

//获取系统毫秒级时间字符串
static std::string inline sys_ms_ts_str( void ){
    uint64_t ms_timestamp = sys_ms_ts();
    return ms_ts2str( ms_timestamp ) ;
}

//获取系统秒级时间字符串
static std::string inline sys_s_ts_str( void ){
    string s = sys_ms_ts_str();
    return s.substr(0, ( s.size() - 4 )) ;
}

}

//--------------------------------OTHER  TOOL---------------------------------------
#include "utility/configer.h"
#include "utility/stool.hpp"


#endif


