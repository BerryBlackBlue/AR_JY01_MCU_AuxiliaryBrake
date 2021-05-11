#include "quaternion.h"
#include "math.h"

/*四元数的元素，代表估计方向*/
float q0 = 1;
float q1 = 0;
float q2 = 0;
float q3 = 0;

/*按比例缩小积分误差*/
float exInt = 0;
float eyInt = 0;
float ezInt = 0;

float yaw,pitch,roll;		//偏航角，俯仰角，翻滚角

void IMUupdate(float gx,float gy,float gz,float ax,float ay,float az)
{
	float norm;
	float vx,vy,vz;
	float ex,ey,ez;
	
	/*测量正常化*/
	norm = sqrt(ax*ax+ay*ay+az*az);
	ax = ax/norm;
	ay = ay/norm;
	az = az/norm;
	
	/*错误的领域和方向传感器测量参考方向之间的交叉乘积的总和*/
	ex = ay*vz-az*vy;
	ey = az*vx-ax*vz;
	ez = ax*vy-ay*vx;
	
	/*积分误差比例积分增益*/
	exInt = exInt+ex*KI;
	eyInt = eyInt+ey*KI;
	ezInt = ezInt+ez*KI;
	
	/*调整后的陀螺仪测量*/
	gx = gx+KP*ex+exInt;
	gy = gy+KP*ey+eyInt;
	gz = gz+KP*ez+ezInt;
	
	/*整合四元数率和正常化*/
	q0 = q0+(-q1*gx-q2*gy-q3*gz)*halfT;
	q1 = q1+(q0*gx+q2*gz-q3*gy)*halfT;
	q2 = q2+(q0*gy-q1*gz+q3*gx)*halfT;
	q3 = q3+(q0*gz+q1*gy-q2*gx)*halfT;
	
	/*正常化四元数*/
	q0 = q0/norm;
	q1 = q1/norm;
	q2 = q2/norm;
	q3 = q3/norm;
	
	pitch = asin(-2*q1*q3+2*q0*q2)*57.3;														//pitch,单位(deg)
	roll  = atan2(2*q2*q3+2*q0*q1,-2*q1*q1+1)*57.3;									//roll,单位(deg)
	yaw   = atan2(2*(q1*q2+q0*q3),q0*q0+q1*q1-q2*q2-q3*q3)*57.3;		//yaw,单位(deg)
}

