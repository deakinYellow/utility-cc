#ifndef STOOL_H
#define STOOL_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <vector>
#include <sstream>

#include <algorithm>
#include <numeric>


/**
 * @brief 小工具,一些常用的简单操作如:
 * 整形字符串相互转换
 * 格式化输
 * read config file.
 */
namespace  stool {

    using std::cout;
    using std::endl;

    typedef struct LinearEuqation2P{
        long x1;
        long y1;
        long x2;
        long y2;
    }LinearEuqation2P;

    ////数值范围
    template<typename T>
    struct  ValueRangeT{
        T min;
        T max;
    };

    template<typename T>
    static ValueRangeT<T> ValueRange( const T min, const T max ){
        ValueRangeT<T> range;
        range.min = min;
        range.max = max;
        return range;
    }

    ///检测键盘是否有输入
    ///是返回1,否返回0
    static int kbhit(void) {
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF) {    ///正常值返回等待用户去读
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }

    //非阻塞获取键盘输入
    //耗时小，微妙级，可单独开线程也可直接扫描
    //存在问题: 只适合单键值输入，还需要处理特殊按键(如方向键,小键盘上的,功能键等)
    static char get_key( void ){
        char ch = -1;
        //检测键盘是否有输入
        if( kbhit() ){
            ch = char( getchar() );
        }
        return ch;
    }

    //variable value limit
    template<typename T>
    static T limit_value( const T min, const T max, T& value ) {
        T temp_v = value;
        if( temp_v < min ){
            value = min;
        }else if( temp_v > max ){
            value = max;
        }
        return  value;
    }

    ////判断数值是否在给定的范围
    template<typename T>
    static bool ValueInRange( const T value , const ValueRangeT<T> range , const bool bundary = true ){
        if( bundary ){
            if( value >= range.min && value <= range.max ){
                    return  true;
            }
        }
        else {
            if( value > range.min && value < range.max ){
                    return  true;
            }
        }
        return false;
    }

    /**
    * @brief  将bytes转换为int float double 类型 ,使用方法如下
           f = bytes2T<float>(p);
    * @param  [in] bytes数据( uchar类型 )
    * @retval
    * @note //转换结果,低位在前
    */
    template<typename T>
    static T bytes2T( unsigned char *bytes ){
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
    * @brief  将std::vector<uint8_t>类型, 转化为整形输出
    *         支持有符号无符号
    * @param  [in] 待转换数据,为小端排序
    * @retval
    * @note //转换结果
    */
    template<typename T>
    static T vectorU82integerT( std::vector<uint8_t> d ){
        uint64_t res = 0;
        uint64_t base = 1;
        for ( ulong i = 0; i < d.size(); i++ ) {
            res +=  d[  i ] * base ;
            base *= 256;
        }
        return T( res );
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
        double k = double( coeff.y2 - coeff.y1 ) / double( coeff.x2 - coeff.x1 );
        long y = long( k * ( x - coeff.x1 ) + coeff.y1 );
        return y;
    }
//计算FPS
class FPS {

public:
    void Sampling(){
        long current_time = stool::sys_ms_ts();
        //printf("current_time: %ld \n" , current_time );
        uint normal_fps =  fpsNormal( current_time );
        if( normal_fps != 0 ){
            this->fps_normal = normal_fps;
        }
        fps_real = fpsReal( current_time );
        fps_average = fpsAverage( current_time );

    }
    uint   fps_normal;
    double fps_average;
    double fps_real;

private:
    //秒级实时帧率，帧率为整数
    uint fpsNormal( const long current_time ){
        static uint count = 0;
        static long last_count_time =0;
        uint fps = 0;
        count++;
        if( current_time - last_count_time >= 1000 ){
           fps = count;
           count = 0;
           last_count_time = current_time;
        }
        return fps;
    }
    //实时帧率 //平滑性不好
    double fpsReal( const long current_time ){
        static long last_time =0;
        double fps = 0;
        //printf("dt time: %ld \n" , current_time - last_time );
        if( current_time != last_time ){
            fps = 1000.0 / double( current_time - last_time );
            last_time = current_time;
        }
        return fps;
    }
    //总平均帧率
    double fpsAverage( const long current_time ){
        static long last_count_time =0;
        static long count =0;
        count++;
        if( last_count_time == 0 && current_time != 0 ){
            last_count_time = current_time;
            return  0;
        }else if( current_time != last_count_time ){
            double fps = 1000 * ( double( count )  / double( current_time - last_count_time ) );
            return fps;
        }
    }

};

}

///-----------------通用算法-------------------------------------
namespace  stool   {
    ////利用vector数值对下标进行排序
    template<typename  T>
    std::vector<size_t> GetVectorIndexSort( const std::vector<T> v ){
        ////初始化索引向量
        std::vector<size_t> index_v(v.size());
        //使用iota对向量赋0连续值
        std::iota(  index_v.begin(), index_v.end(), 0 );
        ///利用v数值对index排序  ///升序
        std::sort( index_v.begin(), index_v.end(), [&v](size_t it1, size_t it2 ){return v[it1] < v[it2]; }  );
        return  index_v;
    }

    ////vector裁剪两端，保留中间部分
    template<typename  T>
    void VectorMidleCut( const double reserved_proportion,
                         std::vector<T>& vector ){
        long n = long( vector.size() );
        long exclude = long( n * ( 1 - reserved_proportion ) / 2 );
        vector.erase( vector.begin(), vector.begin() + exclude );
        vector.erase( vector.end() - exclude, vector.end() );
    }

    ////利用下标对vector选择性保存
    template<typename  T>
    void VectorSelect(  const std::vector<size_t> index_v, std::vector<T>& v ){
        std::vector<T> ret_v;
        for( ulong i = 0; i < index_v.size(); i++ ){
            ret_v.push_back( v[ index_v[ i ] ] );
        }
        v.clear();
        v.swap( ret_v );
    }

    ////求vector均值
    template< typename T>
    static T GetVetorMean( const std::vector<T>& vector ){
        double sum = std::accumulate( std::begin( vector ), std::end( vector ), 0.0 );
        return T( sum / vector.size() );
    }

    /**
    * @brief  ///求vector中间部分均值
    * @param  [in]   reserved_proportion    选取有效比例
    * @param  [in]   vector                 数据vector
    * @retval
    * @note
    */
    template<typename  T>
    T VectorMidleMean( const double valid_proportion,
                       std::vector<T>& vector ){
        ///先排序
        std::sort( std::begin( vector ), std::end( vector ) );
        //再截取
        VectorMidleCut( valid_proportion, vector );
        //求均值返回
        T mean = GetVetorMean( vector );
        return mean;
    }

}


#endif // STOOL_H





