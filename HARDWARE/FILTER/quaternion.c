#include "quaternion.h"
#include "math.h"

/*��Ԫ����Ԫ�أ�������Ʒ���*/
float q0 = 1;
float q1 = 0;
float q2 = 0;
float q3 = 0;

/*��������С�������*/
float exInt = 0;
float eyInt = 0;
float ezInt = 0;

float yaw,pitch,roll;		//ƫ���ǣ������ǣ�������

void IMUupdate(float gx,float gy,float gz,float ax,float ay,float az)
{
	float norm;
	float vx,vy,vz;
	float ex,ey,ez;
	
	/*����������*/
	norm = sqrt(ax*ax+ay*ay+az*az);
	ax = ax/norm;
	ay = ay/norm;
	az = az/norm;
	
	/*���������ͷ��򴫸��������ο�����֮��Ľ���˻����ܺ�*/
	ex = ay*vz-az*vy;
	ey = az*vx-ax*vz;
	ez = ax*vy-ay*vx;
	
	/*������������������*/
	exInt = exInt+ex*KI;
	eyInt = eyInt+ey*KI;
	ezInt = ezInt+ez*KI;
	
	/*������������ǲ���*/
	gx = gx+KP*ex+exInt;
	gy = gy+KP*ey+eyInt;
	gz = gz+KP*ez+ezInt;
	
	/*������Ԫ���ʺ�������*/
	q0 = q0+(-q1*gx-q2*gy-q3*gz)*halfT;
	q1 = q1+(q0*gx+q2*gz-q3*gy)*halfT;
	q2 = q2+(q0*gy-q1*gz+q3*gx)*halfT;
	q3 = q3+(q0*gz+q1*gy-q2*gx)*halfT;
	
	/*��������Ԫ��*/
	q0 = q0/norm;
	q1 = q1/norm;
	q2 = q2/norm;
	q3 = q3/norm;
	
	pitch = asin(-2*q1*q3+2*q0*q2)*57.3;														//pitch,��λ(deg)
	roll  = atan2(2*q2*q3+2*q0*q1,-2*q1*q1+1)*57.3;									//roll,��λ(deg)
	yaw   = atan2(2*(q1*q2+q0*q3),q0*q0+q1*q1-q2*q2-q3*q3)*57.3;		//yaw,��λ(deg)
}

