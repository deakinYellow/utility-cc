#ifndef STOOL_H
#define STOOL_H

#include <iostream>

using std::cout;
using std::endl;


typedef struct LinearEuqation2P{
    long x1;
    long y1;
    long x2;
    long y2;
}LinearEuqation2P;


/**
 * @brief 小工具,一些常用的简单操作如:
 * 整形字符串相互转换
 * 格式化输
 * read config file.
 */
namespace  stool {
    //非阻塞获取键盘输入  //还需要处理特殊按键(如方向键,小键盘上的,功能键等)
    static char get_key()
    {
        //先清空输入缓冲 //
        fflush( stdin );
        /*最初终端驱动处于普通的一次一行模式*/
        int ty = system("stty raw");   /*使终端驱动处于一次一字符模式*/
        fd_set rfds;
        struct timeval tv;

        int ch = 0;

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 10; //设置等待超时时间
        //检测键盘是否有输入
        if( select(1, &rfds, NULL, NULL, &tv ) > 0)
        {
           ch = getchar();
           //printf("a==========%d \n", ch );
           /*
           if( ch == 27 ){
                ch = getchar();
                printf("b==========%d \n", ch );
                ch = getchar();
                printf("c==========%d \n", ch );
           }
           */
        }
        //std::cin.sync();  //放弃缓冲区所有内容
        ty = system("stty cooked");   /*使终端驱动回到一次一行模式*/
        return ch;
    }

    //variable value limit
    template<typename T>
    static T limit_value( T& value, T min, T max ) {
        T temp_v = value;
        if( temp_v < min ){
            value = min;
        }else if( temp_v > max ){
            value = max;
        }
        return  value;
    }

    /**
    * @brief  将bytes转换为int float double 类型 ,使用方法如下
           f = bytes2T<float>(p);
    * @param  [in] bytes数据( uchar类型 )
    * @retval
    * @note //转换结果,低位在前
    */
    template<typename T>
    static T bytes2T(unsigned char *bytes) {
        T res = 0;
        int n = sizeof(T);
        memcpy(&res, bytes, n);
        return res;
    }
    /**
    * @brief  将int float double 转化为bytes类型 ,使用方法如下
               int d = 267;
            unsigned char *p = T2bytes<int>(d);
            得到数据长度为sizeof(d);
    * @param  [in] 待转换数据
    * @retval
    * @note //转换结果,低位在前
    */
    template<typename T>
    static unsigned char* T2bytes(T u) {
        int n = sizeof(T);
        unsigned char* b = new unsigned char[n];
        memcpy(b, &u, n);
        return b;
    }

    /**
    * @brief  将整形转为指定格式的string
    * @param  [in]  num       整形数据
    * @param  [in]  length    指定有效数字长度,数值不够大前面补0
    * @param  [in,out]  str   cxx string 类型
    * @retval     0  成功  -1失败
    * @note
    */
    static int int2string( long num , int length, std::string& str ){
        //先清空
        str.clear();
        //判断是几位数
        int digitLen = 0;
        long temp = num;
        //针对0情况
        if( temp == 0 ){
            digitLen = 1;
        }
        else{
            while ( temp ) {
            digitLen++;
            temp /= 10;
            }
         }
        if( length < digitLen ){
            cout << "intToString error: length is too small" <<  endl;
            return -1;
        }
        //填充-
        if( num < 0 ){
            num = -num;
            str += "-";
        }
        //填充0
        int addZero = length - digitLen;
        for( int i = 0; i < addZero; i++ ){
            str += "0";
        }
        //填充有效数值
        std::stringstream ss;
        std::string numStr;
        ss << num;
        ss >> numStr;//或者 res = ss.str();
        str += numStr;
        return 0;
    }
    //1元线性方程 输入coeff:直线上两点,x 返回 y 值
    static long LinearEuqation( LinearEuqation2P coeff, long x ){
        double k = (double)( coeff.y2 - coeff.y1 ) / (double)( coeff.x2 - coeff.x1 );
        long y = k * ( x - coeff.x1 ) + coeff.y1;
        return y;
    }
}

#endif // STOOL_H

