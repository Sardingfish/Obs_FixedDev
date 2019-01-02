#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TrObsFile.h"
#include "constants.h"
using namespace std;
ObsFile::ObsFile()
{
}

ObsFile::~ObsFile()
{
}

char* ObsFile::Substr(const char* s,int n1,int n2)
{
	char *sp;
	sp=new char[n2-n1+2]; //考虑到了‘/0’ 
	int i,j=0; 
	for (i=n1; i<=n2; i++) 
	{ 
		sp[j++]=s[i]; 
	} 
	sp[j]=0;//在字符串最后加上/0 确保sp为一个字符串而不是字符数组 
	return sp;
}

bool ObsFile::trobsfile()
{
	fstream file1;
    fstream file2;
	file1.open (InputFile,ios::in|ios::out);                                       //cout<<o_filename<<endl; 
	if(!file1)  {cout<<"o文件打开错误!";exit(1);}
	file2.open(OutputFile,ios::out);                    
	if(!file2)  {cout<<"o文件输出错误!";exit(1);}

	while(!file1.eof())
	{
	char str[MAX_CHAR];
	file1.getline(str,MAX_CHAR);

	file2<<str<<endl;

        if(!strcmp("# / TYPES OF OBSERV",Substr(str,60,78)))//观测值数量及类型
		{
			Total_Observe_Type=atoi(Substr(str,0,5));
		//	if(prohdr->Total_Observe_Type<=9)	//不必续航			
			    for(int i=0;i<Total_Observe_Type;i++)
				{
					if(!strcmp("L1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="L1";                        //L1,L2,P1,P2.......均为枚举类型
					if(!strcmp("L2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="L2"; 
					if(!strcmp("P1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="P1"; 
					if(!strcmp("P2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="P2"; 
					if(!strcmp("S1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="S1"; 
					if(!strcmp("S2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="S2"; 
					if(!strcmp("C1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="C1"; 
					if(!strcmp("D1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="D1"; 
					if(!strcmp("T1",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="T1"; 
					if(!strcmp("L5",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="L5"; 
					if(!strcmp("C2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="C2"; 
					if(!strcmp("D2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="D2"; 
					if(!strcmp("T2",Substr(str,10+6*i,11+6*i)))
						Obs_Type_List[i]="T2"; 
				}
		}

	  if(!strcmp("END OF HEADER",Substr(str,60,72)))
	  {
	   break;//跳出循环
	  }
	}

while(!file1.eof ())
{
	char line[MAX_CHAR]="0";
	char line1[MAX_CHAR]="\0";
	char line2[MAX_CHAR]="\0";
	int sTime=(int)(StarTime)*3600
			 +(int)((StarTime-(int)(StarTime))*100)*60;
			 +(StarTime*100-(int)(StarTime*100))*100;                                                            //cout<<sTime<<endl;
	int eTime=(int)(EndTime)*3600
			 +(int)((EndTime-(int)(EndTime))*100)*60
			 +(EndTime*100-(int)(EndTime*100))*100;                                                             //cout<<eTime<<endl;

          // if(Real_Time>=sTime && Real_Time<=eTime)
	
	file1.getline(line,MAX_CHAR);
	int Real_Time=3600*atoi(Substr(line,10,11))+60*atoi(Substr(line,13,14))+(int)atof(Substr(line,15,25));      //cout<<Real_Time<<endl;
	int sign_of_use =atoi(Substr(line,28,28));
	if(sign_of_use!=0 || Real_Time>eTime || Real_Time<sTime)
	{                                                               
		num_sat=atoi(Substr(line,29,31));                                        
 
				if(num_sat<=12) 
					file2<<line<<endl;
				else if((num_sat<=24)&&(num_sat>12))
				{
					file2<<line<<endl;
					//读取第二行
					file1.getline(line1,MAX_CHAR);
				    file2<<line1<<endl;
				}
        if(Total_Observe_Type<=5)
				{
					for(int i=0;i<num_sat;i++)//卫星
					{    
						file1.getline(line2,MAX_CHAR);
						
						file2<<line2<<endl;
					}	
				}
		if((Total_Observe_Type<=10)&&(Total_Observe_Type>5))
				{
					for(int i=0;i<num_sat;i++)
					{
						//第一行
						char line3[MAX_CHAR];
						file1.getline(line3,MAX_CHAR);
						file2<<line3<<endl;
						//第二行
						char line4[MAX_CHAR];
						file1.getline(line4,MAX_CHAR);
                        file2<<line4<<endl;
					}

				  }

	}
	else if(sign_of_use==0)
	{
	    num_sat=atoi(Substr(line,29,31));                                //cout<<Real_Time<<endl;
                                                                         
				if(num_sat<=12) 
					file2<<line<<endl;
				else if((num_sat<=24)&&(num_sat>12))
				{
					file2<<line<<endl;
					//读取第二行
					file1.getline(line1,MAX_CHAR);
				    file2<<line1<<endl;
				}
				
				 //读取观测数据
				if(Total_Observe_Type<=5)
				{
					for(int i=0;i<num_sat;i++)//卫星
					{    
						file1.getline(line2,MAX_CHAR);
						for(int j =0;j<Total_Observe_Type;j++)//观测值类型
						{   double temp =atof(Substr(line2,16*j,16*j+13));

						    if(temp!=0 && !strcmp(Obs_Type_List[j],"L1"))
						       temp=temp+DeltaT*FREQ1;                                 
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L2"))
						       temp=temp+DeltaT*FREQ2;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L5"))
						       temp=temp+DeltaT*FREQ5;                             
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C1"))
						       temp=temp+DeltaT*CLIGHT;                                
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C2"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P1"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P2"))
						       temp=temp+DeltaT*CLIGHT;
							else temp=temp;

							char buffer[50];
							int n;
							n=sprintf(buffer,"%14.3f",temp);
							if(temp!=0)
							{
							for(int l=0;l<14;l++)
							{
								line2[16*j+l]=buffer[l];                       
							}
							}
						}
						file2<<line2<<endl;
					}
				
				
				}

				 if((Total_Observe_Type<=10)&&(Total_Observe_Type>5))
				{
					for(int i=0;i<num_sat;i++)
					{
						//第一行
						char line3[MAX_CHAR];
						file1.getline(line3,MAX_CHAR);                              //cout<<endl;
						for(int j =0;j<5;j++)
						{
							double temp =atof(Substr(line3,16*j,16*j+13));          //cout<<Obs_Type_List[j];

							if(temp!=0 && !strcmp(Obs_Type_List[j],"L1"))
						       temp=temp+DeltaT*FREQ1;                                 
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L2"))
						       temp=temp+DeltaT*FREQ2;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L5"))
						       temp=temp+DeltaT*FREQ5;                             
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C1"))
						       temp=temp+DeltaT*CLIGHT;                                
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C2"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P1"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P2"))
						       temp=temp+DeltaT*CLIGHT;
							else temp=temp;

							char buffer[50];
							int n;
							n=sprintf(buffer,"%14.3f",temp);                           //cout<<"buffer="<<buffer<<endl;
							if(temp!=0)
							{
							for(int l=0;l<14;l++)
							{
								line3[16*j+l]=buffer[l];                     //cout<<"!!!!"<<endl;
							}
							}
						}
						file2<<line3<<endl;
						//第二行
						char line4[MAX_CHAR];
						file1.getline(line4,MAX_CHAR);
						for( int j =0;j<Total_Observe_Type-5;j++)
						{
							double temp =atof(Substr(line4,16*j,16*j+13));        

							if(temp!=0 && !strcmp(Obs_Type_List[j],"L1"))
						       temp=temp+DeltaT*FREQ1;                                 
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L2"))
						       temp=temp+DeltaT*FREQ2;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"L5"))
						       temp=temp+DeltaT*FREQ5;                             
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C1"))
						       temp=temp+DeltaT*CLIGHT;                                
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"C2"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P1"))
						       temp=temp+DeltaT*CLIGHT;
							else if(temp!=0 && !strcmp(Obs_Type_List[j],"P2"))
						       temp=temp+DeltaT*CLIGHT;
							else temp=temp;
							                                                        
							char buffer[50];
							int n;
							n=sprintf(buffer,"%14.3f",temp);                          
							if(temp!=0)
							{
							for(int l=0;l<14;l++)
							{
								line4[16*j+l]=buffer[l];                    
							}
							}
						}
                        file2<<line4<<endl;
					}

				   }
				
			}
}

	file1.close();
	file2.close();
	return true;
}
