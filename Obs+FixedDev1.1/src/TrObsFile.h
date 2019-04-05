#pragma once

#include "constants.h"

class ObsFile
{
public:
		int    num_sat;
		int    Total_Observe_Type;
		char*  Obs_Type_List[OBS_NUM];                    //观测类型数组;每一个元素代表一种类型

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