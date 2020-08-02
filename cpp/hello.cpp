#include <iostream>  //Input Output Stream 输入输出流

using namespace std;//声明了命名空间 std，后续如果有未指定命名空间的符号，那么默认使用 std，代码中的 string、cin、cout 都位于命名空间 std



int main()
{
	int x;
	float y;

	cout<< "Please input an int numnber:" <<endl;//输出
	cin>>x;//输入
	cout<< "the number of x is:" << x <<endl;

	cout<< "Please input an float numnber:" <<endl;//输出
	cin>>y;//输入
	cout<< "the number of x is:" << y <<endl;

	//连续输入
	cout<< "Please input an int number and a float number:" <<endl;
	cin>>x>>y;
	cout<< "the number of x is:" << x <<endl;
	cout<< "the number of y is:" << y <<endl;

	return 0;
}

