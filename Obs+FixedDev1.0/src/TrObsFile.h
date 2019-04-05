#pragma once

#include "constants.h"

class ObsFile
{
public:
		int    num_sat;
		int    Total_Observe_Type;
		char*  Obs_Type_List[OBS_NUM];                    //�۲���������;ÿһ��Ԫ�ش���һ������

		double DeltaT;                                  
		double StarTime;                                 
        double EndTime;                                 
		char*  InputFile;
		char*  OutputFile;

		ObsFile();
		~ObsFile();
		bool trobsfile();
		char* Substr(const char* s,int n1,int n2);	    
};