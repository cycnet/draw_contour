// draw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "draw.h"

#define ULONG_PTR ULONG
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorIThm>
#include <math.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
using namespace Gdiplus;
struct posz
{
	int x;
	int y; 
	float z;
};

static COLORREF tt_color[24] = {
RGB(40,93,253),
RGB(32,125,253),
RGB(28,141,253),
RGB(24,157,253),
RGB(20,173,253),
RGB(16,189,253),
RGB(12,205,253),
RGB(8,222,253),
RGB(4,237,253),
RGB(0,253,253),
RGB(122,255,254),
RGB(255,255,255),
RGB(254,254,205),
RGB(254,254,156),
RGB(255,220,100),
RGB(255,210,35),
RGB(255,186,30),
RGB(255,163,25),
RGB(251,140,52),
RGB(247,128,79),
RGB(250,110,65),
RGB(255,89,25),
RGB(255,45,14),
RGB(255,0,0)
};

static COLORREF rr_color[8]={
	RGB(254,254,205),
		RGB(254,254,156),
		RGB(166,242,143),
		RGB(61,186,61),
		RGB(97,184,255),
		RGB(0,0,255),
		RGB(255,0,255),
		RGB(128,0,64)
};

static COLORREF pp_color[13]={
	RGB(255,0,0),
		RGB(255,89,25),
		RGB(247,128,79),
		RGB(255,163,25),
		RGB(255,210,35),
		RGB(254,254,156),
		RGB(255,255,255),
		RGB(0,253,253),
		RGB(8,222,253),
		RGB(16,189,253),
		RGB(24,157,253),
		RGB(32,125,253),
		RGB(40,93,253)
};
static COLORREF ss_color[24] = {
	RGB(40,93,253),
		RGB(32,125,253),
		RGB(28,141,253),
		RGB(24,157,253),
		RGB(20,173,253),
		RGB(16,189,253),
		RGB(12,205,253),
		RGB(8,222,253),
		RGB(4,237,253),
		RGB(0,253,253),
		RGB(122,255,254),
		RGB(255,255,255),
		RGB(254,254,205),
		RGB(254,254,156),
		RGB(255,220,100),
		RGB(255,210,35),
		RGB(255,186,30),
		RGB(255,163,25),
		RGB(251,140,52),
		RGB(247,128,79),
		RGB(250,110,65),
		RGB(255,89,25),
		RGB(255,45,14),
		RGB(255,0,0)
};

/*static COLORREF jp_color[10]={	
	RGB(255,89,25),////////////
		RGB(247,128,79),
		RGB(255,163,25),
		RGB(255,210,35),
		RGB(254,254,156),
		RGB(255,255,255),
		RGB(0,253,253),
		RGB(8,222,253),
		RGB(16,189,253),
		RGB(24,157,253)
};*/
static COLORREF jp_color[20]={	

		RGB(255,89,25),//
				RGB(250,110,65),
			RGB(247,128,79),
		RGB(251,140,52),
		RGB(255,163,25),
			RGB(255,186,30),
		RGB(255,210,35),
		RGB(255,220,100),
		RGB(254,254,156),
			RGB(254,254,205),
		RGB(255,255,255),
		RGB(122,255,254),
		RGB(0,253,253),
		RGB(4,237,253),
		RGB(8,222,253),
		RGB(12,205,253),
		RGB(16,189,253),
			RGB(20,173,253),
		RGB(24,157,253),
		RGB(28,141,253),

};
static COLORREF wdjp_color[24] = {
	RGB(40,93,253),
		RGB(32,125,253),
		RGB(28,141,253),
		RGB(24,157,253),
		RGB(20,173,253),
		RGB(16,189,253),
		RGB(12,205,253),
		RGB(8,222,253),
		RGB(4,237,253),
		RGB(0,253,253),
		RGB(122,255,254),
		RGB(255,255,255),
		RGB(254,254,205),
		RGB(254,254,156),
		RGB(255,220,100),
		RGB(255,210,35),
		RGB(255,186,30),
		RGB(255,163,25),
		RGB(251,140,52),
		RGB(247,128,79),
		RGB(250,110,65),
		RGB(255,89,25),
		RGB(255,45,14),
		RGB(255,0,0)
};


struct colorz
{
	int x;
	int y;
	int z;
	bool operator <(const colorz&drs)const	
	{  
		return   x < drs.x;
	}
    bool   operator >  (const  colorz&   drs   )const
	{  
		return   x > drs.x;
    }
};

struct lnglat
{
	float lng;
	float lat;
	bool operator < (const lnglat&lgt)const
	{
		return lng<lgt.lng;
	}
	bool operator > (const lnglat&lgt)const
	{
		return lng>lgt.lng;
	}
};


float l_lng=109.0;
float r_lng=118.1;
float b_lat=20.0;
float t_lat=26.1;

float lng=0.0,lat=0.0;
int fangda=100;


CLSID encoderClsid;

TCHAR szPath[MAX_PATH],drive[MAX_PATH],dir[MAX_PATH],fname[MAX_PATH],ext[MAX_PATH],pp [MAX_PATH],wind_u[MAX_PATH],wind_v[MAX_PATH];


const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
/* Base64 编码 */ 
char* base64_encode(const char* data, int data_len); 
/* Base64 解码 */ 
char *base64_decode(const char* data, int data_len); 
void GetBaseByPath(string filename,string outhtml);

vector<float> vecZs;
void setPath();
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void Read(string filename);
void readmap(string txt,Graphics *g1,int type);

void getZ(int colortype,COLORREF *Colors,int color_pos,string types,string times,string danwei,string outfile,string html);

int getsize(ifstream *read_file);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	char filename[MAX_PATH],outhtml[MAX_PATH];
	char m_types[MAX_PATH],m_times[256],m_danwei[256];

	setPath();

	
//	sprintf(filename,"%sstation_krig.txt",szPath);
	sprintf(filename,"%s%s",szPath,argv[1]);
	Read(filename);

	char outfile[MAX_PATH];
	COLORREF *colorss[]={rr_color,tt_color,pp_color,ss_color,jp_color,wdjp_color};
	int color_count[]={8,24,13,24,20,24};
	
	int m_color=5;
	//sprintf(outfile,"%s%s",szPath,"最低温度距平.png");
	sprintf(outfile,"%s%s",szPath,argv[2]);
	sprintf(outhtml,"%s%s",szPath,argv[3]);
	m_color=atoi(argv[4]);

	strcpy(m_types,argv[5]);
	strcpy(m_times,argv[6]);
	strcpy(m_danwei,argv[7]);

	getZ(m_color,colorss[m_color],color_count[m_color],m_types,m_times,m_danwei,outfile,outhtml);
	return 0;
}



void setPath()
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);
	
	GetModuleFileName( NULL, szPath, MAX_PATH );
	_tsplitpath( szPath,drive,dir,fname,ext );
	strcpy( szPath, drive );
	strcat( szPath, dir );
	return;
}


int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num= 0;
	UINT size= 0;
	ImageCodecInfo* pImageCodecInfo= NULL;
	GetImageEncodersSize(&num, &size);
	if(size== 0)
	{
		return -1;
	}

	pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo== NULL)
	{
		return -1;
	}
	
	GetImageEncoders(num, size, pImageCodecInfo);
	
	for(int j=0; j< num; ++j)
	{
		if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
		{
			*pClsid= pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	
	free(pImageCodecInfo);
	return -1;
	
}


void Read(string filename)
{
	ifstream in(filename.c_str());
	if(!in) {
		cout<<"打开样本文件失败！"<< endl;
		return;
	}

	vecZs.clear();


	string line;

	while(getline(in, line))
	{
		float z=atof(line.c_str());
		vecZs.push_back(z);
	}
	
	cout << vecZs.size()<<endl;
	cout << "ok!"<< endl;
	in.close();
	in.clear();
}


void getZ(int colortype,COLORREF *Colors,int color_pos,string types,string times,string danwei,string outfile,string html)
{

	float dTemp1=(r_lng-l_lng)*fangda;
	CString sTemp1=_T("");
	sTemp1.Format(_T("%0.1f"),dTemp1); 
	int nWidth=atoi(sTemp1);
	
	float dTemp2=(t_lat-b_lat)*fangda;
	CString sTemp2=_T("");
	sTemp2.Format(_T("%0.1f"),dTemp2); 
	int nHeight=atoi(sTemp2);

	vector<posz> vecZs2;
	vector<posz> vecZs3;
	
	vecZs3.clear();
	vecZs2.clear();

	int counts=nHeight*nWidth;
	cout << vecZs.size()<< endl;
	cout << counts<< endl;

	for(int  m=0; m<nHeight; m++)
	{
		for(int n=0; n<nWidth; n++) 
		{
			float x=l_lng+n*0.01;
			float y=t_lat-m*0.01;
			int pos=n+m*nWidth;
			float z=vecZs[pos];	
			posz tmpposz;
			tmpposz.x=n;
			tmpposz.y=m;
			tmpposz.z=z;
			vecZs3.push_back(tmpposz);
		}
	}


	cout << "插值完成"<<endl;

	int len=vecZs.size();
	vecZs2.clear();
	vecZs.clear();
	for(int kk=0;kk<vecZs3.size();kk++)
	{
		posz tmpposz=vecZs3[kk];
		vecZs2.push_back(tmpposz);
		vecZs.push_back(tmpposz.z);	
	}
	

/*
	float interval=0.1/2;
	float m_dThickMin=-1.1/2;
	float m_dThickMax=1.2/2;
*/

	vector<float>::iterator iter;
	iter = max_element(vecZs.begin(), vecZs.end());
	double m_dThickMax = *iter;
	iter = min_element(vecZs.begin(), vecZs.end());
	double m_dThickMin = *iter;
	double interval = (m_dThickMax - m_dThickMin) / color_pos;

	if(colortype == 5)
	{
	
		if( (m_dThickMax-m_dThickMin)<0.5 )
		{
			interval=0.1;
			m_dThickMin=-1.2;
			m_dThickMax=1.2;
		}else
		{
			interval=0.2;
			m_dThickMin=-2.4;
			m_dThickMax=2.4;
		}
			cout << "interval"<< interval<< endl;
	}
	
	double maxinterval=10;
	if(colortype == 4)
	{
		if(m_dThickMax/10 >0 && -m_dThickMin/10 >0)
		{
			maxinterval=(m_dThickMax-0)/10;
			if(maxinterval<(0-m_dThickMin)/10)
			{
				maxinterval=(0-m_dThickMin)/10;
			}
		}
	
		interval=maxinterval;
		m_dThickMin=0-maxinterval*10;
		m_dThickMax=maxinterval*10;
	}

	if(colortype == 1)
	{
		interval=0.5;
	}


	int mHeight=nHeight+100;
	int mWidth=nWidth+150;

	BYTE* picData = new BYTE[mWidth*mHeight*4];
	memset(picData,0,mWidth*mHeight*4);
	
	Bitmap bm(mWidth,mHeight,mWidth*4,PixelFormat32bppARGB,picData);//创建bitmap  

	Graphics g1(&bm);
	g1.SetSmoothingMode(SmoothingModeHighQuality);
	CRect rect;
	Pen m_Pen(Color::Black,1.0f);
	PointF points[10] ;
	SolidBrush backbrush(Color(255,255,255,255));
	
	g1.FillRectangle(&backbrush,0,0,mWidth,mHeight);

	int*m_color=new int[mWidth*mHeight];
	memset(m_color,0,mWidth*mHeight*4);


	char provicePath[MAX_PATH];
	sprintf(provicePath,"%smapinfo\\广东.txt",szPath);
	readmap(provicePath,&g1,1);
	int len2=vecZs2.size();

	for(int i=0;i<vecZs2.size();i++)
	{
		posz tmpposz=vecZs2[i];

		double z=tmpposz.z;

		int index = (int)((z - m_dThickMin) / interval);

		if(index>=24)
		{
			index=24;
		}
		
		if(index<=0)
		{
			index=0;
		}
		int row=tmpposz.y+30;
		int col=tmpposz.x+45;

		m_color[row*mWidth+col]=index;

		if(	picData[row*mWidth*4+col*4+0]== 0 )
  		{
			picData[row*mWidth*4+col*4+0] = GetBValue(Colors[index]);    //B
			picData[row*mWidth*4+col*4+1] = GetGValue(Colors[index]);
			picData[row*mWidth*4+col*4+2] = GetRValue(Colors[index]);
			picData[row*mWidth*4+col*4+3] = 255;    //Alpha
	
		}
		else
		{
			picData[row*mWidth*4+col*4+0] = 255;    //B
			picData[row*mWidth*4+col*4+1] = 255;
			picData[row*mWidth*4+col*4+2] = 255;
			picData[row*mWidth*4+col*4+3] = 255;    //Alpha
		
		}
	}
	cout << "色斑完成"<<endl;


	colorz t_colorz;
	vector< vector<colorz> >vv_cz;
	vector<colorz> v_cz;
	vv_cz.clear();
	v_cz.clear();
	for(int t=0;t<color_pos;t++)
	{
		vv_cz.push_back(v_cz);
	}
	
	for(int y=30;y<nHeight+30;y++)
	{
		for(int x=45;x<nWidth+45;x++)
		{
			int i1=m_color[(y-1)*mWidth+x];
			int i2=m_color[(y+1)*mWidth+x];
			int i3=m_color[y*mWidth+x-1];
			int i4=m_color[y*mWidth+x+1];
			int i5=m_color[(y-1)*mWidth+x-1];
			int i6=m_color[(y+1)*mWidth+x+1];
			int i7=m_color[(y-1)*mWidth+x+1];
			int i8=m_color[(y+1)*mWidth+x-1];
			int i9=m_color[y*mWidth+x];
			//if(i1==i2 ||||i3==i4 || i5==i6 || i7== i8 )
			if(i1==i9 &&i2==i9 && i3==i9 && i4== i9 && i5== i9&& i6== i9 && i7== i9 && i8== i9)
			{

			}else
			{
				if(i9-i1==1 ||i9-i2==1  ||i9-i3==1  ||i9-i4==1  ||i9-i5==1  ||i9-i6==1  ||i9-i7==1  ||i9-i8==1 )
				{
// 					picData[y*mWidth*4+x*4+0] = 0;    //B
// 					picData[y*mWidth*4+x*4+1] = 0;
// 					picData[y*mWidth*4+x*4+2] = 0;
// 					picData[y*mWidth*4+x*4+3] = 255;    //Alpha

					t_colorz.x=x;
					t_colorz.y=y;
					t_colorz.z=i9;
					for(int t=0;t<color_pos;t++)
					{
						if(i9==t)
						{
							if(	!(picData[(y-1)*mWidth*4+(x-1)*4+0]==255 &&
								  picData[(y-1)*mWidth*4+(x+1)*4+0]==255 && 
								  picData[(y+1)*mWidth*4+(x-1)*4+0]==255 &&
								  picData[(y+1)*mWidth*4+(x+1)*4+0]==255 &&
								  picData[(y-1)*mWidth*4+(x-1)*4+1]==255 &&
								  picData[(y-1)*mWidth*4+(x+1)*4+1]==255 && 
								  picData[(y+1)*mWidth*4+(x-1)*4+1]==255 &&
								  picData[(y+1)*mWidth*4+(x+1)*4+1]==255 &&
								  picData[(y-1)*mWidth*4+(x-1)*4+2]==255 &&
								  picData[(y-1)*mWidth*4+(x+1)*4+2]==255 && 
								  picData[(y+1)*mWidth*4+(x-1)*4+2]==255 &&
								  picData[(y+1)*mWidth*4+(x+1)*4+2]==255
								  ) )
  							{
								vv_cz[t].push_back(t_colorz);
							}
						}
					}
				}
				
			}
		}
	}

	PointF b_p;
	PointF e_p;
	PointF  tpoint;
	char t_char[256];
	CString t_string="";
	FontFamily fontfamily(L"宋体");  
	Gdiplus::Font font(&fontfamily,12,FontStyleRegular,UnitPixel); 
	Gdiplus::Font font1(&fontfamily,12,FontStyleRegular,UnitPixel); 
	SolidBrush gzbrush(Color(255,0,0,0));


	rect.left=45;
	rect.right=nWidth+45;
	rect.top=30;
	rect.bottom=nHeight+30;
	
//	vector<int>v_x;
	for(t=0;t<vv_cz.size()-1;t++)
	{
		v_cz=vv_cz[t];
		sort(v_cz.begin(),v_cz.end());//升序
		colorz t_colorz;
		int md=v_cz.size()/8;
		int mcount=0;

		if(md==0)
		{
			md=1;
		}
	//	v_x.clear();
		for(int k=0;k<v_cz.size();k++)
		{

			t_colorz=v_cz[k];
			int x=t_colorz.x;
			int y=t_colorz.y;
			int z=t_colorz.z;

			
			if( k%md==1  && k>md  && k<(v_cz.size()-md))
			{
			
				if(mcount%2==0)
				{
					memset(t_char,0,256);
					//int index = (int)((z - m_dThickMin) / interval);
				
					sprintf(t_char,"%0.1f",z*interval+m_dThickMin);//int index = (int)((z - m_dThickMin) / interval);
					
					//sprintf(t_char,"%0.1f",z);
					t_string=t_char;
					tpoint.X=x-6;
					tpoint.Y=y-4;
					if(y>rect.top+2 && y<rect.bottom-2)
					{
						g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);
						//v_x.push_back(x);
					}
					
				}
				
				mcount++;
			}else
			{
				picData[y*mWidth*4+x*4+0] = 0;    //B
				picData[y*mWidth*4+x*4+1] = 0;
				picData[y*mWidth*4+x*4+2] = 0;
				picData[y*mWidth*4+x*4+3] = 255;    //Alpha
			}
			
		}



	}
	

	cout << "等值线完成"<<endl;
	delete m_color;  


	sprintf(provicePath,"%smapinfo\\广东.txt",szPath);
	readmap(provicePath,&g1,0);

	sprintf(provicePath,"%smapinfo\\县边界.txt",szPath);
	readmap(provicePath,&g1,0);
	cout <<"地理信息完成"<< endl;

	g1.FillRectangle(&backbrush,-1,-1,mWidth+1,rect.top+1);
	g1.FillRectangle(&backbrush,-1,rect.bottom,mWidth+1,mHeight-rect.bottom+1);
	g1.FillRectangle(&backbrush,-1,0,rect.left+1,mHeight+1);
	g1.FillRectangle(&backbrush,rect.right,-1,mWidth-rect.right+1,mHeight+1);

	points[0].X=rect.left;
	points[0].Y=rect.top;
	points[1].X=rect.right;
	points[1].Y=rect.top;
	
	points[2].X=rect.right;
	points[2].Y=rect.bottom;
	
	points[3].X=rect.left;
	points[3].Y=rect.bottom;
	points[4]=points[0];
 	g1.DrawLines(&m_Pen, points, 5);
	cout <<"边框完成"<< endl;

	

	for(int n=0; n<=nWidth; n=n+100) 
	{
		float i=l_lng+n*0.01;
	//	float j=t_lat-m*0.01;
		b_p.Y=rect.bottom;
		e_p.Y=rect.bottom+8;
		
		b_p.X=rect.left+n;
		e_p.X=b_p.X;
		g1.DrawLine(&Pen(Color::Black, 1),b_p,e_p);

		memset(t_char,0,256);
		sprintf(t_char,"%0.0f゜E",i);
		t_string=t_char;
		tpoint.X=b_p.X-3;
		tpoint.Y=e_p.Y+3;
		g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);

	}

	for( m=0; m<=nHeight; m=m+100)
	{
		float j=b_lat+m*0.01;
		b_p.X=rect.left-8;
		e_p.X=rect.left;
	
		b_p.Y=rect.bottom-m;
		e_p.Y=b_p.Y;
		g1.DrawLine(&Pen(Color::Black, 1),b_p,e_p);

		memset(t_char,0,256);
		sprintf(t_char,"%0.0f゜N",j);
		t_string=t_char;
		tpoint.X=rect.left-43;
		tpoint.Y=rect.bottom-m-10;
		g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);
	}

	
	memset(t_char,0,256);

	sprintf(t_char,"%s \t\t %s  \t\t单位:%s \t\t广东省气象台制作",types.c_str(),times.c_str(),danwei.c_str());

	t_string=t_char;
	tpoint.X=rect.left+100;
	tpoint.Y=rect.bottom+38;
	g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);
	cout<<"底部信息完成"<< endl;


	float s_interval=(m_dThickMax-m_dThickMin)/(color_pos-1) ;


	memset(t_char,0,256);
	sprintf(t_char,"单位：%s",danwei.c_str());
	t_string=t_char;
	tpoint.X=rect.right+5;
	tpoint.Y=rect.bottom-25-color_pos*20;
	g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);
	
	
	for(int k=0;k<color_pos;k++)
	{
		SolidBrush backbrush2(Color(GetRValue(Colors[k]),GetGValue(Colors[k]),GetBValue(Colors[k])));
		g1.FillRectangle(&backbrush2,rect.right+8,rect.bottom-30-k*20,20,20);
		g1.DrawRectangle(&m_Pen,rect.right+8,rect.bottom-30-k*20,20,20);
		
		if(k<color_pos)
		{
			memset(t_char,0,256);
		
			sprintf(t_char,"%0.1f",m_dThickMin+interval*k);
			t_string=t_char;
			tpoint.X=rect.right+30;
			tpoint.Y=rect.bottom-20-k*20;
			g1.DrawString(t_string.AllocSysString(),-1,&font,tpoint,&gzbrush);
		}
	
		//m_dThickMax
		//double interval = (m_dThickMax - m_dThickMin) / (24 - 1);
	}
	cout<<"色标完成"<<endl;

	

	CString outfile1=outfile.c_str();
	BSTR outbstr;
	outbstr=outfile1.AllocSysString();
	GetEncoderClsid(L"image/jpeg", &encoderClsid);
	bm.Save(outbstr,&encoderClsid);

	GetBaseByPath(outfile.c_str(),html.c_str());
}


void readmap(string txt,Graphics *g1,int type)
{
	int nWidth=(r_lng-l_lng)*fangda;
	int nHeight=(t_lat-b_lat)*fangda;
	
	ifstream read_file;
	string line,input_ret;
	vector<string> vString;
	lnglat m_lnglat;
	vector<lnglat> v_lnglat;
	
	Pen m_Pen(Color(255, 0, 0, 0),0.8f);
	SolidBrush m_Brush(Color(255, 0, 0, 0));
	read_file.open(txt.c_str());
	if(!read_file.is_open())
	{
		return;
	}
	v_lnglat.clear();
	int count=0,count2=0;
	int pos=0;
	for(int i=0;i<3;i++)
	{
		getline(read_file, line);
	}

	count=getsize(&read_file);
	
	int allcount=0;
	for(i=0;i<count;i++)
	{
		count2=getsize(&read_file);
		PointF *p=new PointF[count2];
		for(int j=0;j<count2;j++)
		{
			getline(read_file, line);
			stringstream input(line);
			vString.clear();
			while(input>>input_ret)
			{
				vString.push_back(input_ret);
			}
			
			lng=atof(vString[0].c_str());
			lat=atof(vString[1].c_str());
			//lat=y_lonLat2Mercator(lat);
			//if(lng<70 || lng>180) return;
			int x=(lng-l_lng)*fangda;
			int y=(t_lat-lat)*fangda;
			
			p[j].X=x+45;
			p[j].Y=y+30;
			
			
		}
		
		GraphicsPath path;
		path.AddLines(p,count2);
		
		if(type==1)
		{
			g1->FillPath(&m_Brush,&path);
		}
		
		
		g1->DrawLines(&m_Pen, p, count2);
		//g1->FillRectangle(&m_Brush,0,0,rect.left,)
		
		if(p)delete p;
	}
	
	read_file.close();
	read_file.clear();
	return;
}

int getsize(ifstream *read_file)
{
	string line,input_ret;
	int ret=0;
	vector<string> vString;
	getline(*read_file, line);
	
	stringstream input(line);
	vString.clear();
	while(input>>input_ret)
	{
		vString.push_back(input_ret);
	}
	ret=atof(vString[0].c_str());
	return ret;
}


void GetBaseByPath(string filename,string outhtml)
{
	CString mm_base64="<img src=\"data:image/png;base64,";
	FILE* filein;
	int allcount=0;
	if((filein=fopen(filename.c_str(),"rb"))!=NULL)
	{	
		fseek(filein,0,SEEK_END);
		int m_iSize=ftell(filein);
		fseek(filein,0,SEEK_SET);
		char *data=new char[m_iSize+1];
		fread(data,m_iSize,1,filein);
		mm_base64+=base64_encode(data,m_iSize);
	}
	mm_base64+="\" />";
	ofstream outfiles(outhtml.c_str());
	if(outfiles.is_open())
	{
		
		outfiles<< mm_base64.GetBuffer(mm_base64.GetLength())<<endl;
		
	}
	cout<< "文件生成"<< endl;
	outfiles.close();
	outfiles.clear();
	
	
	return;
}

char *base64_encode(const char* data, int data_len) 
{ 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
      
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            //printf("tmp = %d\n", tmp); 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            //printf("%.2X", changed[i]); 
            f++; 
        } 
    } 
    *f = '\0'; 
      
    return ret; 
      
} 

/* 转换算子 */ 
static char find_pos(char ch)   
{ 
    char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
    return (ptr - base); 
} 

/* Base64 解码 */ 
char *base64_decode(const char *data, int data_len) 
{ 
    int ret_len = (data_len / 4) * 3; 
    int equal_count = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    int temp = 0;
    int prepare = 0; 
    int i = 0; 
    if (*(data + data_len - 1) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 2) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 3) == '=') 
    {//seems impossible 
        equal_count += 1; 
    } 
    switch (equal_count) 
    { 
    case 0: 
        ret_len += 4;//3 + 1 [1 for NULL] 
        break; 
    case 1: 
        ret_len += 4;//Ceil((6*3)/8)+1 
        break; 
    case 2: 
        ret_len += 3;//Ceil((6*2)/8)+1 
        break; 
    case 3: 
        ret_len += 2;//Ceil((6*1)/8)+1 
        break; 
    } 
    ret = (char *)malloc(ret_len); 
    if (ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < (data_len - equal_count)) 
    { 
        temp = 0; 
        prepare = 0; 
        while (temp < 4) 
        { 
            if (tmp >= (data_len - equal_count)) 
            { 
                break; 
            } 
            prepare = (prepare << 6) | (find_pos(data[tmp])); 
            temp++; 
            tmp++; 
        } 
        prepare = prepare << ((4-temp) * 6); 
        for (i=0; i<3 ;i++ ) 
        { 
            if (i == temp) 
            { 
                break; 
            } 
            *f = (char)((prepare>>((2-i)*8)) & 0xFF); 
            f++; 
        } 
    } 
    *f = '\0'; 
    return ret; 
}