#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <opencv2\opencv.hpp>
#include "Eigen/Dense"
#include "Eigen/Core"



///////////////////////////////////////////////////////////////////////值传递
int value_transfer1(int v1)//v1是形参会开辟新的内存空间
{
	v1 = 0;
	return v1;
}

int value_transfer2(int* p1) //p1是指针，是形参，会开辟新的内存空间
{
	*p1 = 0;
	return *p1;
}

/////////////////////////////////////////////////////////////////////////引用传递
int value_transfer3(int& r1) {
	r1 = 0;
	return r1;
}


/// ////////////////////////////////////////////////////////////////////////传递数组
int array_transfer1(int* a1)//int* a1=array1;
{
	a1[0] = 0; 
	a1[1] = 0; 
	a1[2] = 0; 
	a1[3] = 0; 
	a1[4] = 0;
	return 0;
}
int array_transfer2(int a1[])//int a1[]=array1;
{
	a1[0] = 1;
	a1[1] = 1;
	a1[2] = 1;
	a1[3] = 1;
	a1[4] = 1;
	return 0;
}
int array_transfer3(int (*a1)[2])//int a1[]=array1;
{
	a1[0][0] = 0;
	a1[0][1] = 0;
	a1[1][0] = 0;
	a1[1][1] = 0;
	return 0;
}
int array_transfer4(int a1[][2])//int a1[]=array1;
{
	a1[0][0] = 1;
	a1[0][1] = 1;
	a1[1][0] = 1;
	a1[1][1] = 1;
	return 0;
}


//////////////////////////////////////////////////////////////////////传递结构体
struct study//定义结构体
{
	int content;
	int time[5];
};
typedef struct study study1;//对结构体重命名

int struct_transfer1(study s1)
{
	s1 = { 0,0,0,0,0,0 };
	return 0;
}
int struct_transfer2(study* s1)
{
	*s1 = { 1,1,1,1,1,1 };
	return 0;
}
int struct_transfer3(study& s1)
{
	s1 = { 2,2,2,2,2,2 };
	return 0;
}
////////////////////////////////////////////////////////////////////传递结构体数组
struct study2//定义结构体
{
	int content;
	int time[5];

	//study2()//构造函数初始化。
	//{
	//	content = 20;
	//	memset(time, -1, sizeof(time));//memset() 赋值时不是只能赋值为0，任意字符都是可以的，初始化成0是最常用的。int类型的一般都是赋值0或-1，其他的值都不行。
	//}
};

int structarray_transfer1(study2 s1[])
{
	s1[0] = {0,0,0,0,0,0};
	s1[1] = { 0,0,0,0,0,0 };
	s1[2] = { 0,0,0,0,0,0 };
	return 0;
}

int structarray_transfer2(study2* s1)
{
	s1[0] = { 1,1,1,1,1,1 };
	s1[1] = { 1,1,1,1,1,1 };
	s1[2] = { 1,1,1,1,1,1 };
	return 0;
}



//////////////////////////////////////////////////////////////////结构体和类的区别
struct study_struct1
{
	int content;
	int time[5];
};
struct study_struct2
{
	int content;
	int time[5];

	study_struct2()
	{
		content = 1;
		time[0]=1;time[1] = 1;time[2] = 1;time[3] = 1;time[4] = 1;
	}
	study_struct2(int con)
	{
		this->content = con;
		time[0] = 2;time[1] = 2;time[2] = 2;time[3] = 2;time[4] = 2;
	}
};


class  study_class1
{
public:
	int content=0;
	int time[5] = {0,0,0,0,0};

private:
	int private_content=0;
};
class  study_class2
{
public:
	int content ;
	int time[5];

	study_class2()
	{
		content = 1;
		time[0] = 1; time[1] = 1; time[2] = 1; time[3] = 1; time[4] = 1;
		private_content = 1;
	}
	study_class2(int con)
	{
		content = con;
		time[0] = 2; time[1] = 2; time[2] = 2; time[3] = 2; time[4] = 2;
		private_content = 2;
	}

private:
	int private_content;
};
class  study_class3
{
public:
	int content;
	int time[5];

	study_class3(int a,int b) :content(a), private_content(b){};

private:
	int private_content;
};



////////////////////////////////////////////////////////////////////////////构造函数和析构函数
class class_gouzao
{
public:
	int member1;
	int member2[3];

	class_gouzao()//无参构造函数，
	{
		//默认构造函数：如果没有手动写构造函数，编译器会默认生成一个无参构造函数，并调用
		//默认构造函数的缺点：
		//当类的成员变量中，有指针操作时，默认构造函数初始化的状态未知；
		//默认构造函数初始化的值，不一定全是０, 编译器不同，结果不同；
		//默认构造函数无法初始化出一个指定的非０初始值；
		member1 = 0;
		member2[0] = 0; member2[1] = 0; member2[2] = 0;
	}
	class_gouzao(int a, int b)//有参构造函数
	{
		member1 = a;
		member2[0] = b; member2[1] = b; member2[2] = b;
	}
	class_gouzao(const class_gouzao &A)
	{
		member1 = A.member1;
		member2[0] = A.member2[0]; member2[1] = A.member2[1]; member2[2] = A.member2[2];
	}

	~class_gouzao()//析构函数，如果没有手动写析构函数，编译器会默认生成一个析构函数，并调用
	{
	}
};


int main()
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////指针
	int variable1 = 255;
	int* pointer1 = &variable1; //int*——指针，开辟新的内存空间，内部存放地址   &——取地址
								//定义一个指针的时候没有给指针初始化，则会出现野指针。野指针不知道会访问到什么地址，很危险。
	
	int* pointer11 = &variable1;
	int variable2 = 100;       //*指针——取指针所指的值
	pointer11 = &variable2;     //pointer1的地址不会变化，pointer1内容存放的地址会变化，变为variable2的地址
	*pointer11 = 1000;   //pointer11的地址不会变化，pointer11内容存放的地址不会变化，但是variable2的值会改变

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////二重指针
	int** pointerpointer = &pointer1; //pointerpointer存放pointer1的地址


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////引用
	int &reference1 = variable1; //int&——引用，编译器不会为引用开辟新的内存空间，与variable1共用一块内存空间
	int* reference1_pointer1 = &reference1;

	// int& reference1;        //报错，引用在定义时就必须初始化

	int variable3 = 20;
	reference1 = variable3;
	int* reference1_pointer2 = &reference1;//reference1的地址不会改变还是variable1的地址，reference1内容存放的值变为20，variable1内容存放的值变为20

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////值传递
	int value1 = 20;
 	int res1 = value_transfer1(value1);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////指针传递
	int value2 = 20;
	int* pointer2 = &value2;
	int res2 = value_transfer2(pointer2);//int* p = pointer2;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////引用传递
	int value3 = 20;
	int res3 = value_transfer3(value3);//int& p = value3;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////传递数组（指针传递）
	int array1[5] = {20,20,20,20,20};
	int res4 = 0;
	res4 = array_transfer1(array1);//一维数组传递
	res4 = array_transfer2(array1);
	int array2[2][2] = { {20,20},{20,20} };
	res4 = array_transfer3(array2);//二维数组传递
	res4 = array_transfer4(array2);

	int array3[2][2] = { {1,2},{3,4} };
	//int* a = *array1;//*array1是int类型，a是指针类型，所以会报错
	//int* a = array3; //array3是int(*)[2]类型，a是指针类型，所以会报错
	int* a = *array3;//array3是二维数组，*array3是指针类型


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////传递结构体(可值传递，指针传递，引用传递)
	study study1 = {20,20,20,20,20,20};//结构体初始化

	int res5 = 0;
	res5 = struct_transfer1(study1);//传递结构体—值传递
	res5 = struct_transfer2(&study1);//传递结构体—指针传递
	res5 = struct_transfer3(study1);//传递结构体—引用传递


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////传递结构体数组
	study2 study2[3];
	int res6 = 0;
	res6 = structarray_transfer1(study2);
	res6 = structarray_transfer2(study2);



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////结构体和类的初始化
	study_struct1 s_s1;
	s_s1 = { 0,0,0,0,0,0 }; //结构体初始化方法1——定义时初始化
	study_struct1 s_s2;
	s_s2.content = 1;//结构体初始化方法2——定义后逐个赋值
	memset(s_s2.time,-1,sizeof(s_s2.time));
	study_struct2 s_s3;//结构体初始化方法3——构造函数初始化
	study_struct2 s_s4(2);
	 
	study_class1 s_c1;//类初始化方法1——定义时初始化
	study_class2 s_c2;//类初始化方法2——构造函数初始化
	study_class2 s_c3(2);
	study_class3 s_c4(3,3);//类初始化方法3——初始化列表

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////构造函数
	//用于初始化类成员
	class_gouzao gz1();//无参构造函数调用
	class_gouzao gz2(1, 1);//有参构造函数调用，括号法
	class_gouzao gz22(1, 1);//有参构造函数调用，等号法
	class_gouzao gz3 = class_gouzao(2, 2);//拷贝构造函数调用


	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////析构函数
	//释放对象所占用的资源

	//C++内存管理
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////C++五种内存分区
	//栈——由编译器自动管理，自动开辟大小，无需手动控制；
	//char11,i11,p11存放在栈区,"abcd"放在常量存储区
	char char11[] = "abcd";
	int i11 = 1;
	int* p11 = &i11;


	//堆——需要程序员自己申明大小，也由程序员控制释放，容易产生内存泄露
	//      分配方式：动态分配
	int* p21 = (int*)malloc(sizeof(int)*4);
	int* p22 = (int*)calloc(4, sizeof(int));
	int* p23 = (int*)realloc(p22, sizeof(int) * 4);
	free(p21);
	//free(p22);  报错calloc会自动释放内存
	free(p23);
	int* p24 = new int;
	int* p25 = new int(3);
	int* p26 = new int[3];
	int* p27 = new int[3]{ 1,2,3 };
	delete p24;
	delete p25;
	delete p26;
	delete p27;



	//自由存储区

	//全局/静态存储区
	static int int41 = 1;//int41存放在静态存储区

	//常量存储区
	char char51[] = "abcd";//"abcd"放在常量存储区；char51在栈区

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//智能指针——实现用户申请的内存自动释放——释放堆上程序员申请的内存
	auto n1 = std::shared_ptr<int>();
	auto n2 = std::make_shared<int>();
	auto n3 = std::unique_ptr<int>();
	std::shared_ptr<int> q1 = std::shared_ptr<int>(new int(5));
	std::shared_ptr<int> q2 = std::make_shared<int>(5); 
	//std::shared_ptr<int> q3 = std::make_shared<int>(new int(5));



	//线程


	


	

	return 0;
}
