#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>
#include<deque>
#include<stdlib.h>
#include<queue>
#include <iomanip>
using namespace std;



struct car{
	int direction;//行走方向 
	int inputcol;
	int LSR;
	string englishdir;//方向的英文字母 

};

struct twocar{
    car car_a;
    car car_b;
    int number;
};

car North(char* a,int i)
{
	car Cartemp;
	if(strcmp (a,"1E") == 0)
	{
		Cartemp.direction=11;
		Cartemp.inputcol=i;
		Cartemp.LSR=2;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1S") == 0)
	{
		Cartemp.direction=9;
		Cartemp.inputcol=i;
		Cartemp.LSR=1;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1W") == 0)
	{
		Cartemp.direction=8;
		Cartemp.inputcol=i;
		Cartemp.LSR=0;
		Cartemp.englishdir=a;
	}
	return Cartemp;
	
}

car East(char* a,int i)
{
	car Cartemp;
	if(strcmp (a,"1N") == 0)
	{
		Cartemp.direction=4;
		Cartemp.inputcol=i;
		Cartemp.LSR=0;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1S") == 0)
	{
		Cartemp.direction=13;
		Cartemp.inputcol=i;
		Cartemp.LSR=2;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1W") == 0)
	{
		Cartemp.direction=12;
		Cartemp.inputcol=i;
		Cartemp.LSR=1;
		Cartemp.englishdir=a;
	}
	return Cartemp;
}

car South(char* a,int i)
{
	car Cartemp;
	if(strcmp (a,"1N") == 0)
	{
		Cartemp.direction=6;
		Cartemp.inputcol=i;
		Cartemp.LSR=1;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1E") == 0)
	{
		Cartemp.direction=2;
		Cartemp.inputcol=i;
		Cartemp.LSR=0;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1W") == 0)
	{
		Cartemp.direction=14;
		Cartemp.inputcol=i;
		Cartemp.LSR=2;
		Cartemp.englishdir=a;
	}
	return Cartemp;
}

car West(char* a,int i)
{
	car Cartemp;
	if(strcmp (a,"1E") == 0)
	{
		Cartemp.direction=3;
		Cartemp.inputcol=i;
		Cartemp.LSR=1;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1S") == 0)
	{
		Cartemp.direction=1;
		Cartemp.inputcol=i;
		Cartemp.LSR=0;
		Cartemp.englishdir=a;
	}
	else if(strcmp (a,"1N") == 0)
	{
		Cartemp.direction=7;
		Cartemp.inputcol=i;
		Cartemp.LSR=2;
		Cartemp.englishdir=a;
	}
	return Cartemp;
}


bool four_car_go(car one, car two, car three, car four,int time){
    if(one.inputcol<=time && two.inputcol<=time && three.inputcol<=time && four.inputcol<= time){ // 要注意等號要不要
        if(one.LSR==0 && two.LSR==0 && three.LSR==0 && four.LSR==0){     //都是右轉
            return true;
        }
        else return false;
    }
    else return false;
}
int three_car_go(car one,car two, car three , car four,int time){
    if((one.inputcol<=time && two.inputcol<=time && three.inputcol<=time)||(one.inputcol<=time && two.inputcol<=time && four.inputcol<=time)||
		(two.inputcol<=time && four.inputcol<=time && three.inputcol<=time)||(one.inputcol<=time && three.inputcol<=time && four.inputcol<=time)){
            if(!(one.direction & two.direction)&&!(one.direction & three.direction)&&!(two.direction & three.direction)&&(one.inputcol<=time && two.inputcol<=time && three.inputcol<=time )) {  // and 出來為0 表示沒有衝突
                return 4;                                                      // 告訴哪台車沒有走
            }
            else if(!(one.direction & two.direction)&&!(one.direction & four.direction)&&!(four.direction & two.direction)&&(one.inputcol<=time && two.inputcol<=time && four.inputcol<=time )){
                return 3;                                                  
            }
            else if(!(one.direction & three.direction)&&!(one.direction & four.direction)&&!(four.direction & three.direction)&&(one.inputcol<=time && four.inputcol<=time && three.inputcol<=time )){
                return 2;                                                  
            }
            else if(!(two.direction & three.direction)&&!(two.direction & four.direction)&&!(four.direction & three.direction)&&(four.inputcol<=time && two.inputcol<=time && three.inputcol<=time )){
                return 1; 
            }
            else 
			{
				return 0;   // 0表示不能三台車走
    		}
    }
    else return 0;
}

int two_car_go(car one,car two, car three , car four,int time){
        vector<twocar> check_two;
        twocar tempa ;
        int match_pair=0;
        if((one.inputcol<=time && two.inputcol<=time)||(one.inputcol<=time && three.inputcol<=time)||(one.inputcol<=time && four.inputcol<=time)||(two.inputcol<=time && three.inputcol<=time)||
		(two.inputcol<=time && four.inputcol<=time)||(three.inputcol<=time && four.inputcol<=time)){
                
			if(!(one.direction & two.direction )&&one.inputcol<=time && two.inputcol<=time){	
				tempa.car_a=one;
                tempa.car_b=two;
                tempa.number=12;
                check_two.push_back(tempa);
                match_pair++;
        	}
            if(!(one.direction & three.direction )&&one.inputcol<=time && three.inputcol<=time){
                tempa.car_a=one;
                tempa.car_b=three;
                tempa.number=13;
                check_two.push_back(tempa);
                match_pair++;
            }
            if(!(one.direction & four.direction )&&one.inputcol<=time && four.inputcol<=time){
                tempa.car_a=one;
                tempa.car_b=four;
                tempa.number=14;
                check_two.push_back(tempa);
                match_pair++;
            }
             if(!(two.direction & three.direction)&&three.inputcol<=time && two.inputcol<=time){
                tempa.car_a=two;
                tempa.car_b=three;
                tempa.number=23;
                check_two.push_back(tempa);
                match_pair++;

            }
           if(!(two.direction & four.direction )&&four.inputcol<=time && two.inputcol<=time){
                tempa.car_a=two;
                tempa.car_b=four;
                tempa.number=24;
                check_two.push_back(tempa);
                match_pair++;
            }
            if(!(three.direction & four.direction )&&three.inputcol<=time && four.inputcol<=time){
                tempa.car_a=three;
                tempa.car_b=four;
                tempa.number=34;
                check_two.push_back(tempa);
                match_pair++;
            }
        }
     	if(match_pair==0)
        	return 0;
    	else{             ///Two_car_go true : greedy algo: L>S>R
             for (vector<twocar>::iterator it =check_two.begin() ; it != check_two.end(); ++it){     //判斷有左轉就先走
               if( (*it).car_a.LSR==2 || (*it).car_b.LSR==2)  return (*it).number ;
            }
              for (vector<twocar>::iterator it =check_two.begin() ; it != check_two.end(); ++it){    // 判斷有直走的就先走
                if( (*it).car_a.LSR==1 ||(*it).car_b.LSR==1)  return (*it).number ;
            }
            vector<twocar>::iterator it=check_two.begin();                                                     //僅有右轉的情況下，就隨便走
            return  (*it).number ;
    		}
}



int one_car_go(deque<deque<car> > &cartemp,int time)
{
	
	if(cartemp[0][0].inputcol<=time||cartemp[1][0].inputcol<=time||cartemp[2][0].inputcol<=time||cartemp[3][0].inputcol<=time)
	{
		bool Turn[4]={false,false,false,false};
	
		for(int i=0;i<4;i++)
		{
			if(cartemp[i][0].inputcol<=time)
			{
				if(cartemp[i][0].LSR==2)
					Turn[i]=true;
			}
		}
		int l=0;
		for(int i=0;i<4;i++)
			if(Turn[i]) l++;
		if(l==0)
		{
			for(int i=0;i<4;i++)
			{
				if(cartemp[i][0].inputcol<=time)
				{
					if(cartemp[i][0].LSR==1)
						Turn[i]=true;
				}
			}
			for(int i=0;i<4;i++)
				if(Turn[i]) l++;
			if(l==0)
			{
				for(int i=0;i<4;i++)
				{
					if(cartemp[i][0].inputcol<=time)
					{
						if(cartemp[i][0].LSR==0)
							Turn[i]=true;
					}
				}
				for(int i=0;i<4;i++)
				if(Turn[i])
					return (i+1);///有R可以走的 
			}
			else
			{
				for(int i=0;i<4;i++)
				if(Turn[i])
					return (i+1);//有S可以走的判斷是 
			}	
		}
		else
		{
			for(int i=0;i<4;i++)
				if(Turn[i])
					return (i+1);///有L可以走的判斷是 
		}
		
	
	}
	
	else return 0;
}

void lastoutput(deque<deque<string> > &output, ostream &fout)
{
	for(int i=0;i<4;i++)
	{
		if(i==0)
		{
			fout<<"N:";
			for(deque<string>::iterator it = output[i].begin() ; it != output[i].end(); ++it)
				fout<<" "<<*it;
			fout<<endl;
		}
		if(i==1)
		{
			fout<<"E:";
			for(deque<string>::iterator it = output[i].begin() ; it != output[i].end(); ++it)
				fout<<" "<<*it;
			fout<<endl;
		}
		if(i==2)
		{
			fout<<"S:";
			for(deque<string>::iterator it = output[i].begin() ; it != output[i].end(); ++it)
				fout<<" "<<*it;
			fout<<endl;
		}
		if(i==3)
		{
			fout<<"W:";
			for(deque<string>::iterator it = output[i].begin() ; it != output[i].end(); ++it)
				fout<<" "<<*it;
			fout<<endl;
		}
	}
}

int main(int argc,char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);	
	
	deque<deque<car> > allcar;
	allcar.resize(4);
	int i=0;
	string commandbuffer;
	car Cartemp;
	for(int j=0;j<4;j++)
	{
		getline(fin,commandbuffer,'\n');
		char* cstr= new char[commandbuffer.length()+1];
		strcpy(cstr,commandbuffer.c_str());
		char *p=strtok(cstr," ");
		
		p=strtok(NULL," \r\n");
		if(j==0)
		{
			while(p)
			{
				if(strcmp (p,"00") == 0)
				{
					i++;
					p=strtok(NULL," \r\n");
				}
				else
				{
					Cartemp=North(p,i);
					allcar[j].push_back(Cartemp);
					i++;
					p=strtok(NULL," \r\n");
				}
			}
			i=0;
		}
		if(j==1)
		{
			while(p)
			{
				if(strcmp (p,"00") == 0)
				{
					i++;
					p=strtok(NULL," \r\n");
				}
				else
				{
					Cartemp=East(p,i);
					allcar[j].push_back(Cartemp);
					i++;
					p=strtok(NULL," \r\n");
				}
			}
			i=0;
		}
		if(j==2)
		{
			while(p)
			{
				if(strcmp (p,"00") == 0)
				{
					i++;
					p=strtok(NULL," \r\n");
				}
				else
				{
					Cartemp=South(p,i);
					allcar[j].push_back(Cartemp);
					i++;
					p=strtok(NULL," \r\n");
				}
			}
			i=0;
		}
		if(j==3)
		{
			while(p)
			{
				if(strcmp (p,"00") == 0)
				{
					i++;
					p=strtok(NULL," \r\n");
				}
				else
				{
					Cartemp=West(p,i);
					allcar[j].push_back(Cartemp);
					i++;
					p=strtok(NULL," \r\n");
				}
			}
			i=0;
		}
	}
	Cartemp.direction=0000;
	Cartemp.inputcol=2147483647;
	Cartemp.englishdir="00";
	
	for(int j=0;j<4;j++)//加最後的dummy node 
		allcar[j].push_back(Cartemp);//
	
	i=0;
	deque<deque<string> > output;
	output.resize(4);
	int k;//用來存要走的車的指標 
	
	while(allcar[0][0].inputcol!=2147483647||allcar[1][0].inputcol!=2147483647||allcar[2][0].inputcol!=2147483647||allcar[3][0].inputcol!=2147483647)
	{
		//cout<<"test"<<endl;
		if(four_car_go(allcar[0][0],allcar[1][0],allcar[2][0],allcar[3][0],i))
		{
			for(int j=0;j<4;j++)
			{
				output[j].push_back(allcar[j][0].englishdir);
				allcar[j].pop_front();
			}	
			i++;	
		}
		else if(k=three_car_go(allcar[0][0],allcar[1][0],allcar[2][0],allcar[3][0],i))
		{
			
			for(int j=0;j<4;j++)
			{
				if(j!=(k-1))
				{
					output[j].push_back(allcar[j][0].englishdir);
					allcar[j].pop_front();
				}
				else
				{
					output[j].push_back("00");
				}
			}
			i++;
			
		}
		if(k=two_car_go(allcar[0][0],allcar[1][0],allcar[2][0],allcar[3][0],i))
		{
			for(int j=0;j<4;j++)
			{
				if(j==(k/10-1)||j==(k%10-1))
				{
					output[j].push_back(allcar[j][0].englishdir);
					allcar[j].pop_front();
				}
				else
				{
					output[j].push_back("00");
				}
			}
			i++;
		}
		else
		{
			
			k=one_car_go(allcar,i);
			for(int j=0;j<4;j++)
			{
				if(j==(k-1))
				{
					output[j].push_back(allcar[j][0].englishdir);
					allcar[j].pop_front();
				}
				else
				{
					output[j].push_back("00");
				}
			}
			i++;
		}
	}
	
	lastoutput(output,fout);

	
	
	fin.close();
	fout.close();
	return 0;
};
	
