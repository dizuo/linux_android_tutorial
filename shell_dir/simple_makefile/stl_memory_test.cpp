#include <vector>
#include <string>
#include <iostream>

using namespace std;

template<class T>
void STLClearObject(T* obj)
{
	T tmp;
	tmp.swap(*obj);
	obj->reserve(0);
}

void test()
{
	vector<string> str_vec;
	
	const int kTestNum = 1000;
	
	for (int i = 0; i < kTestNum; i++)
	{
		str_vec.push_back("hello world");
	}

	str_vec.clear();

	for (int i=0; i<kTestNum*2; i++) str_vec.push_back("test");
	str_vec.clear();

	// vector<string>().swap(str_vec);
	STLClearObject(&str_vec);
}

int main()
{
	test();
	
	cin.get();

	return 0;
}


