#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <iterator>


using namespace std;
using namespace cv;

class TEST
{
	private:
		Mat imgGray;
		Mat imgIntermediateResult;
		Mat imgRez;
		int temp;
		float matrix1[1000][1000];
		
		

	public:
		int ROWS;
		int COLS;		
		
		Mat imgIn;
		Mat imgPFIM14;
		void getImage(Mat src)
		{
			imgIn = src.clone();
		}

		void img2Gray()
		{
			cvtColor(imgIn,imgGray,CV_BGR2GRAY);
			imgRez = imgGray.clone();
		}

    void getSize()
		{
			int r,c;
			Size s = imgRez.size();
			r = s.height;
			c = s.width;
			ROWS = r;
			COLS = c;
			cout << ROWS << " " << COLS << endl;
			int row = ROWS; 
			int col = COLS;			
			for(int r=1; r<row-1; r++)
			{
				for(int c=1; c<col-1 ;c++)
				{
					matrix1[r][c] = imgRez.at<uchar>(r,c);
					
				}
			}
		} 	

		void normalise()
		{
			//namedWindow("result");			
			//imshow("result",imgIntermediateResult);
			int row = ROWS; 
			int col = COLS;
			for(int r=1; r<row-1; r++)
			{
				for(int c=1; c<col-1 ;c++)
				{
					if(matrix1[r][c] > 255)
					{
						imgRez.at<uchar>(r,c) = 255;
					}
					else if(matrix1[r][c] <= 255 && matrix1[r][c] > 0)
					{					
						imgRez.at<uchar>(r,c) = matrix1[r][c];
					}
					else if(matrix1[r][c] >= -255 && matrix1[r][c] < 0)
					{					
						imgRez.at<uchar>(r,c) = -matrix1[r][c];
					}
					else
					{
						imgRez.at<uchar>(r,c) = 255;
					}
				}
			}
			
		}
	
		void showResult()
		{
			namedWindow("test");
			imshow("test",imgRez);
			imwrite("test.png",imgRez);
			waitKey(0);
		}

		void threshout()
		{
			int row = ROWS; 
			int col = COLS;
			for(int r=1; r<row-1; r++)
			{
				for(int c=1; c<col-1 ;c++)
				{			

					if(imgRez.at<uchar>(r,c) < 10)
					{
						imgRez.at<uchar>(r,c) = 255;
					}
				}
			}			
		}
		
		void mean5x5()
		{
			int row = ROWS; 
			int col = COLS;
			int matrix[1000][1000] = {0};
			int temp;	
				
			for(int r=2; r<row-2; r++)
			{
				for(int c=2; c<col-2 ;c++)
				{
					matrix[r][c] = matrix1[r][c];
					//cout << "gfdfsG" << endl;	
					//cout << matrix[r][c] << endl;				
				}
			}

			for(int r=2; r<row-2; r++)
			{
				for(int c=2; c<col-2 ;c++)
				{
					temp = (matrix[r-2][c-2] + matrix[r-2][c-1] + matrix[r-2][c] + matrix[r-2][c+1] + matrix[r-2][c+2] + matrix[r-1][c-2] + matrix[r-1][c-1] + matrix[r-1][c] + matrix[r-1][c+1] + matrix[r-1][c+2] + matrix[r][c-2] + matrix[r][c-1] + matrix[r][c] + matrix[r][c+1] + matrix[r][c+2] + matrix[r+1][c-2] + matrix[r+1][c-1] + matrix[r+1][c] + matrix[r+1][c+1] + matrix[r+1][c+2] + matrix[r+2][c-2] + matrix[r+2][c-1] + matrix[r+2][c] + matrix[r+2][c+1] + matrix[r+2][c+2])/25;

				matrix1[r][c] = temp;	
				}	
			}

			
			//temp = imgGray.at<uchar>(row,col);
			//cout << matrix[12][51] << endl;
		}
		
		void sqrtc()
		{
			int row = ROWS; 
			int col = COLS;			
			float c1;
			float c2;
			for(int r=0; r<row-1; r++)
			{
				for(int c=0; c<col-1 ;c++)
				{
					c1 = matrix1[r][c];
					if(c1>=0)
					{
						c2 = sqrt(c1);
					}
					else
					{
						c2 = -sqrt(-c1);
					}
					//cout << c2 << endl;
					matrix1[r][c] = c2;
					
				}
			}
		}
		
		
		void subc()
		{
			int row = ROWS; 
			int col = COLS;			
			int c1 = 10;
			for(int r=0; r<row-1; r++)
			{
				for(int c=0; c<col-1 ;c++)
				{
					matrix1[r][c] = matrix1[r][c] - c1;
				}
			}
		}


    void mulc()
		{
			int row = ROWS; 
			int col = COLS;			
			float c1 = 5;
			float temp;
			for(int r=0; r<row-1; r++)
			{
				for(int c=0; c<col-1 ;c++)
				{
					temp = matrix1[r][c];					
					temp= temp*c1;
					matrix1[r][c] = temp;
				}
			}
		}

    void med5x5()
		{
			int row = ROWS; 
			int col = COLS;
			int matrix[1000][1000] = {0};
			//int emil[9];
			int y = 25;
			int v;
			int final[25];	
				
			for(int r=1; r<row-1; r++)
			{
				for(int c=1; c<col-1 ;c++)
				{
					matrix[r][c] = matrix1[r][c];
					//cout << "gfdfsG" << endl;	
					//cout << matrix[r][c] << endl;				
				}
			}

			for(int r=1; r<row-1; r++)
			{
				for(int c=1; c<col-1 ;c++)
				{
					int emil[26] = {matrix[r-2][c-2],matrix[r-2][c-1],matrix[r-2][c],matrix[r-2][c+1],matrix[r-2][c+2],matrix[r-1][c-2],matrix[r-1][c-1],matrix[r-1][c],matrix[r-1][c+1],matrix[r-1][c+2],matrix[r][c-2],matrix[r][c-1],matrix[r][c],matrix[r][c+1],matrix[r][c+2],matrix[r+1][c-2],matrix[r+1][c-1],matrix[r+1][c],matrix[r+1][c+1],matrix[r+1][c+2],matrix[r+2][c-2],matrix[r+2][c-1],matrix[r+2][c],matrix[r+2][c+1],matrix[r+2][c+2]};

					for(int x=0;x<y;x++)
					{
               					for(int z=0;z<y;z++)
	       					{
                    					v = z;
                    					if(emil[z] < emil[z+1])
		    					{
                	        				v = emil[z];
                	        				emil[z] = emil[z+1];
                	        				emil[z+1] = v;
                    					}
                				}
         				}

					for(int i=0;i<25;i++)
					{
						final[24-i] = emil[i];
					}
					matrix1[r][c] = emil[13];
				
				}	
			}

		}
		
};


int main()
{
	Mat image = imread("test2.png");

	TEST test;

	test.getImage(image);
	
	test.img2Gray();
	
	test.getSize();
	
	test.mean5x5();
	test.sqrtc();
	test.subc();
	test.sqrtc();
	test.mulc();
	test.subc();
	test.mulc();
	test.mulc();
	test.sqrtc();
	test.med5x5();
	
	test.normalise();
	test.threshout();	
	test.showResult();

}
