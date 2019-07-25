
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
 /*
int ***max(int sizeofarray2,int outs1,int outs2,int n,int***in, Mat image)
{
	int temp=0;
	int ***pool;
	int stride,i,x,j,k,l,y;
	int poolsize1=0;
	int poolsize2=0;
	printf("stride\n");
	scanf("%d",&stride);


	poolsize1 = (outs1 - sizeofarray2)/ stride +1;
	poolsize2 = (outs2 - sizeofarray2)/ stride +1;
	
	

	pool= (int***)malloc(n*sizeof(int**));


	for(i=0;i<n;i++)
	{
		*(pool+i)=(int**)malloc(poolsize1*sizeof(int*));
		for(j=0;j<poolsize1;j++)
		{
			*(*(pool+i)+j)=(int*)malloc(poolsize2*sizeof(int));
		}
	}


	
//////////////////////////////////////////

for(x=0;x<n;x++)
{

	for(k=0;k<poolsize1;k++)
	{	
		for(l=0;l<poolsize2;l++)
		{	
			for(i=0;i<sizeofarray2;i++)
			{
				for(j=0;j<sizeofarray2;j++)
				{

					if(in[x][i+stride*k][j+stride*l] > temp)
					{
					temp=in[x][i+stride*k][j+stride*l];
					}


				}	
					
			}
					pool[x][k][l]=temp;
					temp=0;
		}	
			
	}
}

	Mat image1(poolsize1,poolsize2,image.type());	
	for(int z=0;z<n;z++)
	{		
		for(int x=0;x<poolsize1;x++)
		{	
			for(int y=0;y<poolsize2;y++)	
			{
				image1.at<cv::Vec3b>(x,y)[z]=pool[z][x][y];

			}
		}
        }

	imwrite("original4.jpg",image1);
	

					return pool;
}	
*/
int ***createcnn(int row,int col,int n,int ***in,double **p,int sizeofarray2,int *outsize1,int *outsize2)  // 행렬,채널
{	
	int stride,padding;
	int i,j,k,l,x,y;
	int ***q,***pad;
	printf("padding\n");
	scanf("%d",&padding);
	printf("stride\n");
	scanf("%d",&stride);
	
	*outsize1 = ((row-sizeofarray2+2*padding)/stride)+1;
	*outsize2 = ((col-sizeofarray2+2*padding)/stride)+1;

	
	q= (int***)malloc(n*sizeof(int**));
	for(i=0;i<n;i++)
	{
		*(q+i)=(int**)malloc(*outsize1*sizeof(int*));
		for(j=0;j<*outsize1;j++)
		{
			*(*(q+i)+j)=(int*)malloc(*outsize2*sizeof(int));
		}
	}

	pad= (int***)malloc(n*sizeof(int**));
	for(i=0;i<n;i++)
	{
		*(pad+i)=(int**)malloc((row+2*padding)*sizeof(int*));
		for(j=0;j <row+2*padding;j++)
		{
			*(*(pad+i)+j)=(int*)malloc((col+2*padding)*sizeof(int));
		}
	}
		
	for(i=0;i<n;i++)
	{
		for(x=0;x<row+2*padding;x++)
		{
			for(y=0;y<col+2*padding;y++)
			{
				pad[i][x][y]=0;
			}
		}
	}
for(i=0;i<n;i++)
{
	for(x=0;x<row;x++)
	{
		for(y=0;y<col;y++)
		{
			pad[i][x+padding][y+padding]=in[i][x][y];
		}
	}
}

for(x=0;x<n;x++)
{
	for(k=0;k<*outsize1;k++)
	{		
		for(l=0;l<*outsize2;l++)
		{	
			for(i=0;i<sizeofarray2;i++)
			{
				for(j=0;j<sizeofarray2;j++)
				{
				q[x][k][l] +=pad[x][i+stride*k][j+stride*l]*p[i][j];
				}
			}	
				if(q[x][k][l] > 255)
				{
				q[x][k][l] =255;
				}
		

				else if(q[x][k][l]<0)
				{
				q[x][k][l]=0;
				}

		
		}	
			
	}
}
	

	return q;
}								//out .



double **createfilter(double**p, int sizeofarray2)
{	
	int i,j,k=0	;
	double blur[3][3]={{0.0625,0.125,0.0625},{0.125,0.25,0.125},{0.0625,0.125,0.0625}};//16
	p= (double**)malloc(sizeofarray2*sizeof(double*));
	for(i=0;i<sizeofarray2;i++)
	{
		*(p+i)=(double*)malloc(sizeofarray2*sizeof(double));
	}
	printf("나눌거");
	scanf("%d",&k);

	for(i=0;i<sizeofarray2;i++)
	{
		for(j=0;j<sizeofarray2;j++)
		{
			
				printf("filter = p[%d][%d]값\n",i,j);
				scanf("%lf",&p[i][j]);
				
				p[i][j]=p[i][j]/k;
				
		}

	}
	return p;
}
	
							//필터 함수

int main()

{

	
	int n=0;
	int i,j,k,l,x,m;
	int sizeofarray1,sizeofarray2;
	int sizeofarray3,sizeofarray4=0;	
	int outs1,outs2;
	double **p;  //필터
	int ***in;//입력
	//cnn
	int ***s; //padding
	int stride;
	int padding;
	int row;
	int col;
	double blur[3][3]={{0.0625,0.125,0.0625},{0.125,0.25,0.125},{0.0625,0.125,0.0625}};//16
	int blur1[3][3]={{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
	double blur2[5][5] = {{1,4,6,4,1},{4,16,24,16,4},{6,24,36,24,6},{4,16,24,16,4},{1,4,6,4,1}};//256

	
	
	
	
	printf("만들고싶은 필터사이즈\n");
	scanf("%d",&sizeofarray2);
	
	
	p = createfilter(p,sizeofarray2); //max pooling시 주석..


							
	

	Mat image;
	int ***out;
	
	
	image =imread("hee.jpg",IMREAD_COLOR);


	if (image.empty())
	{
		cout <<"could not open" <<endl;
		return -1;
	}

	row=image.rows;
	col=image.cols;
	n=3;


//////////////////////////////////////////////////////////////////////////////////////	
	in= (int***)malloc(n*sizeof(int**));
	for(i=0;i<n;i++)
	{
		*(in+i)=(int**)malloc(row*sizeof(int*));
		for(j=0;j < row;j++)
		{
			*(*(in+i)+j)=(int*)malloc(col*sizeof(int));
		}
	}

	
	for(int z=0;z<n;z++)
	{		
		for(int x=0;x<row;x++)
		{	
			for(int y=0;y<col;y++)	
			{
				in[z][x][y]=image.at<cv::Vec3b>(x,y)[z];
			}
		}
	}
					//input .
	
//////////////////////////////////////////////////////////////////////////////////////
	
	
	//out = max(sizeofarray2,row,col,n,in,image);

	out = createcnn(row,col,n,in,p,sizeofarray2,&outs1,&outs2); //max pooling시 주석..

	Mat image1(outs1,outs2,image.type(),CV_32F);	
	for(int z=0;z<n;z++)
	{		
		for(int x=0;x<image1.rows;x++)
		{	
			for(int y=0;y<image1.cols;y++)	
			{
				image1.at<cv::Vec3b>(x,y)[z]=out[z][x][y];

			}
		}
        }

	imwrite("hmm.jpg",image1);

	for(i=0;i<3;i++)
	{
	for(j=0;j<row;j++)
		{
	free(*(*(in+i)+j));
		}
	free(*(in+i));
	}
	free(in);

	
	for(i=0;i<3;i++)
	{
	for(j=0;j<outs1;j++)
		{
	free(*(*(out+i)+j));
		}
	free(*(out+i));
	}
	free(out);



	waitKey(0);

	return 0;
}


	


