#include <bits/stdc++.h>
#define NO_OF_SAMPLE 4

using namespace std;

ifstream read_data;
ofstream z;

int main()
{
	read_data.open("data_set_aminar_dblp.v11/dblp_papers_v11.txt");
	z.open("data_set_aminar_dblp.v11/sample_of_dblp_papers_v11.txt");
	string a;
	int count = 0;
	while(read_data)
	{
		getline(read_data, a);
		z<<a<<endl;
		if(count == (NO_OF_SAMPLE - 1))
		{
			//z<<a<<endl;
			break;
		}
		count++;
	}
	return 0;
}