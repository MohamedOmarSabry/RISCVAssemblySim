#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
map<string, string> registers;
string Stringtobinary(string num) //working as intended
{
	long long r;
	bool n = 0;
	r = stoll(num);
	if (r < 0)
	{
		n = 1;
		num.erase(0, 1);
		r = stoll(num);
	}
	string binary = "";
	for (int i = 31; i >= 0; i--) {
		int k = r >> i;
		if (k & 1)
			binary+='1';
		else
			binary+='0';
	}
	if (n)
	{
		int b = binary.length();
		int i;
		for (i = b - 1; i >= 0; i--)
			if (binary[i] == '1')
				break;
		if (i == -1)
			return '1' + binary;
		for (int k = i - 1; k >= 0; k--)
		{
			if (binary[k] == '1')
				binary[k] = '0';
			else
				binary[k] = '1';
		}
	}

	return binary;
}
string Stringtohexa(string value) //works
{
	string binnum = Stringtobinary(value);
	//cout << binnum << endl;
	char hexa[8];
	int temp;
	long int i = 0, j = 0;
	while (binnum[i])
	{
		binnum[i] = binnum[i] - 48;
		i++;
	}
	i--;
	while (i - 2 >= 0)
	{
		temp = binnum[i - 3] * 8 + binnum[i - 2] * 4 + binnum[i - 1] * 2 + binnum[i];
		if (temp > 9)
			hexa[j++] = temp + 55;
		else
			hexa[j++] = temp + 48;
		i = i - 4;
	}
	if (i == 1)
		hexa[j] = binnum[i - 1] * 2 + binnum[i] + 48;
	else if (i == 0)
		hexa[j] = binnum[i] + 48;
	else
		--j;
	string s = "";
	while (j >= 0)
	{
		s += hexa[j--];
	}
	return s;
}
int binaryToDecimal(string n) //works
{
	string num = n;
	int dec_value = 0;
	int base = 1;
	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}
	return dec_value;
}
void PrintMem_Reg()
{

}
int main()
{
	cout<< Stringtohexa("2147483647")<<endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
