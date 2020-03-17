/*
 *  @brief:  C/C++编程常用小工具: LOG,延时,系统时间,键盘输入等
 *  @author: Deakin
 *  @email:  deakinhwang@163.com
 *  @last modify:  2019/12/25
 */
#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <time.h>

#define __need_timeval

//--------------------------------LOG ABOUT---------------------------------------
//在需要开启debuglog的目标源文件开头包含tool.h前引入,如果全局开启,则在这里引入
//#define USING_MLOGD
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
///特指CPU消耗的实际时间，用来判断某段功能的CPU消耗(例如延时函数就不会消耗太多CPU实际使用时间)
#define  TIME_START clock_t startTimeT = clock()
#define  TIME_END   clock_t endTimeT = clock()
#define  TIME_COST  ( endTimeT - startTimeT ) / (CLOCKS_PER_SEC / 1000 )
#define  TIME_COSTLOGD MLOGD("cost time: %f ms.",(float)TIME_COST )


#include <unistd.h>
#include <sys/time.h>
#define M_USLEEP(x)     usleep((x))
#define M_MSLEEP(x)     usleep( (x)*1000 )
#define M_SLEEP(x)      usleep( (x)*1000*1000 )
//---------------------------------TIME ABOUT-------------------------------------

//---------------------------------OPT RET------------------------------------------
#define MOK   0
#define MFAIL   1
//---------------------------------OPT RET END------------------------------------------

//--------------------------------OTHER  TOOL---------------------------------------
//#include "utility/configer.h"
#include "stool.hpp"


#endif



