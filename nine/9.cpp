#include <iostream>
#include <vector>

typedef unsigned long long ull;


ull times(int* arry, int Size);

int main() {
    const int cache =10000* 1024; //в байтах
    std::vector<ull>results;

    for(int fragment = 1; fragment <= 32; fragment++)
	{

        int elemCount = cache / sizeof(int) / fragment;  // число элементов равных объему фрагменту в смещении

        int arry_size = cache / sizeof(int) * fragment;
	    int *arry = new int[arry_size];


        for(int i = 0; i < fragment; ++i)   //обращаемся ко всем прежним фрагментам
		{
            for(int j = 0; j < elemCount; ++j)
			{
                arry[i * cache / sizeof(int) + j] = (i + 1) * cache / sizeof(int) + j;  //заполняем в виде списка
            }
        }

        for(int i = 0; i < elemCount; ++i)   //для последнего фрагмента
		{
            arry[(fragment - 1) * cache / sizeof(int) + i] = i + 1;  //заполняем в виде списка
        }

        arry[ (cache / sizeof(int)*(fragment - 1) - 1)] = 0;

        results.push_back(times(arry, arry_size));

        delete[] arry;
    }


    for( int i = 0; i < results.size(); i++)
	{
        std::cout << results[i] << std::endl;
    }


    return 0;
}

ull times(int* arry, int Size)
{
	union ticks {
		unsigned long long t64;
		struct s32 {
			int th, tl;
		} t32;
	} start, end;

	ull all_time = -1;

	for (int j = 0; j < 5; ++j)
	{
		asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));

		int ind = 0;
		for (int i = 0; i < Size; ++i) { ind = arry[ind]; }

		asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));

		if (all_time > (end.t64 - start.t64))
		{
			all_time = end.t64 - start.t64;
		}
	}
	ull result = all_time / Size;
	return result;
}
