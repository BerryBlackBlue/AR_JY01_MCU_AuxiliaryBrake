#ifndef	__FILTER_H
#define __FILTER_H

#include "sys.h"

#define KP			100.0f		//��������֧�������������ٶȼ�/��ǿ��
#define KI			0.002f		//��������֧���ʵ�������ƫ����ν�
#define halfT		0.001f		//�������ڵ�һ��


void IMUupdate(float gx,float gy,float gz,float ax,float ay,float az);
	
#endif

