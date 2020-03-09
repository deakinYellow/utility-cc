/*****************************************************************

 *简介：简易卡尔曼滤波

 *备注：卡尔曼算法要不断的更新,才能发挥作用.dt就是定时器的时间

***************************************************************/
#include <iostream>


#define  CH0_KALMAN_Q	  0.3  // 0.1 //0.5  //1
#define  CH0_KALMAN_R 	 100 * CH0_KALMAN_Q
/*---------------------------------------------------------------
        Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
        R:测量噪声，R增大，动态响应变慢，收敛稳定性变好
*/
static double CH0_KalmanFilter(  const double ResrcData,
                                 double ProcessNiose_Q,
                                 double MeasureNoise_R  ) {
        double R = MeasureNoise_R;
        double Q = ProcessNiose_Q;

        static  double x_last;
        static   double p_last;

        double x_mid = x_last;
        double x_now;


        double p_mid ;
        double p_now;
        double kg;

        x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
        p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
        kg=p_mid/(p_mid+R); //kalman filter,R为噪声
        x_now=x_mid+kg*(ResrcData-x_mid);//估计出最优值
        p_now=(1-kg)*p_mid;//最优值对应的covariance
        p_last = p_now; //更新covariance
        x_last = x_now; //更新系统状态值

        return x_now;
}

class  KalmanFilter
{
public:

    KalmanFilter() {}

    //含静态变量
    //对单个double型数据进行滤波,一个对象只能对应一个数据对象,不能用于多个数据对象
    double SingleValueFilter( const double resrc_data,
                              const double noise_Q,
                              const double noise_R  ) {

        double R = noise_R;
        double Q = noise_Q;

        double x_mid = sf_x_last_;
        double x_now;

        double p_mid ;
        double p_now;
        double kg;

        x_mid = sf_x_last_; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
        p_mid = sf_p_last_ + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
        kg = p_mid / (p_mid+R); //kalman filter,R为噪声
        x_now = x_mid + kg * ( resrc_data - x_mid );//估计出最优值
        p_now = (1-kg) * p_mid;//最优值对应的covariance
        sf_p_last_ = p_now; //更新covariance
        sf_x_last_ = x_now; //更新系统状态值
        return x_now;
    }


private:
    double sf_x_last_;
    double sf_p_last_;

};




