#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <cmath>
#include <bitset>
using namespace std;
map<string, string> registers;
map<string, string> memory;
int PC;
int bit_12OverflowSim(int x)
{
	//x is offset
	//z is overflow
	int z=x;
	if (x > 2047)
	{
		z = x % 2047;
		z = -2048 + z;
	}
	else if (x < -2048)
	{
		z = x % 2048;
		z = 0 - z;
	}
	return z;
	
}
string Stringtobinary(string num) //working as intended
{
	int32_t r;
	bool n = 0;
	r = stoi(num);
	if (r < 0)
	{
		n = 1;
		num.erase(0, 1);
		r = stoi(num);
	}
	string binary = "";
	/*for (int i = 31; i >= 0; i--) {
		int k = r >> i;
		if (k & 1)
			binary+='1';
		else
			binary+='0';
	}*/
	while (r > 0)
	{
		int k = r % 2;
		binary += to_string(k);
		r = r / 2;
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
	map<string, string>::iterator it;
	cout << "Regisiters Values : " << endl;
	for (it=registers.begin(); it != registers.end(); it++)
	{
		cout << it->first << " : " <<" Decimal : " << it->second << " Hexa : " << Stringtohexa(it->second) <<" Binary : " << Stringtobinary(it->second) << endl;
	}
	cout << "Memory Values : " << endl;
	for (it=memory.begin(); it != memory.end(); it++)
	{
		cout << it->first << " : " << it->second << " Hexa : " << Stringtohexa(it->second) << " Binary : " << Stringtobinary(it->second) << endl;
	}
}
void ADD(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t1 = t2 + t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void SUB(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t1 = t1 - t2;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void AND(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t1 = t2 & t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void OR(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t1 = t2 | t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void XOR(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t1 = t2 ^ t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void ADDI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t1 = t2 + t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();

}
void XORI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t1 = t2 ^ t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();

}
void ORI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t1 = t2 | t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void ANDI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t1 = t2 & t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();
}
void SLT(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	int32_t t3;
	if (t1 < t2)
		t3 = 1;
	else
		t3 = 0;
	it = registers.find(rd);
	it->second = to_string(t3);
	PrintMem_Reg();
}
void SLTU(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	uint32_t t2 = stoi(it->second);
	bool t3;
	if (t1 < t2)
		t3 = 1;
	else
		t3 = 0;
	it = registers.find(rd);
	it->second = to_string(t3);
	PrintMem_Reg();
}
void SLTI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	bool t3;
	if (t1 < t2)
		t3 = 1;
	else
		t3 = 0;
	it = registers.find(rd);
	it->second = to_string(t3);
	PrintMem_Reg();
}
void SLTIU(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	uint32_t t2 = stoi(imm);
	bool t3;
	if (t1 < t2)
		t3 = 1;
	else
		t3 = 0;
	it = registers.find(rd);
	it->second = to_string(t3);
	PrintMem_Reg();
}
void SLL(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	uint32_t t2 = stoi(it->second);
	t2 = t1 << t2;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void SLLI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	uint32_t t2 = stoi(imm);
	t2 = t1 <<t2;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void SRL(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	uint32_t t2 = stoi(it->second);
	t2 = t2 >> t1;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void SRLI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	uint32_t t1 = stoi(it->second);
	uint32_t t2 = stoi(imm);
	t2 = t2 >> t1;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void SRA(string rd, string rs1, string rs2)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	it = registers.find(rs2);
	int32_t t2 = stoi(it->second);
	t2 = t2 >> t1;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void SRAI(string rd, string rs1, string imm)
{
	map<string, string>::iterator it;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t2 = t2 >> t1;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void LUI(string rd, string imm) 
{
	int32_t t1 = stoi(imm);
	uint32_t t2 = (t1 << 20);
	uint32_t t3 = (t2 >> 20);
	t2 = t1 - t3;
	map<string, string>::iterator it;
	it = registers.find(rd);
	it->second = to_string(t2);
	PrintMem_Reg();
}
void AUIPC(string rd, string imm) 
{
	int32_t t1 = stoi(imm);
	uint32_t t2 = (t1 << 20);
	uint32_t t3 = (t2 >> 20);
	t2 = t1 - t3;
	map<string, string>::iterator it;
	it = registers.find(rd);
	it->second = to_string(t2+PC);
	PrintMem_Reg();
}
void SW(string rs1, string rs2, string off) { // sw x9,0(x2)
	//int source_value, destination_value;
	//search for address
	//Found --> overwrite
	//Not Found --> Insert
	map<string, string>::iterator it;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); // t1 = src value
	it= registers.find(rs1);
	int32_t t2 = stoi(it->second); // t2 = dest value
	//Simulates overflow is offset larger than the 12bit signed cap
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t2 = t2 + t3; //dest = dest_reg + offset
	it = memory.find(to_string(t2));
	if (it == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t1));
	}
	else
	{
		it->second = to_string(t1);
	}
	PrintMem_Reg();
}
void LW(string rs1, string rd, string off) {
	map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second); // t1 = src value (mem)
	it = registers.find(rd);
	int32_t t2 = stoi(it->second); // t2 = dest value (reg)
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t1 = t1 + t3; //dest = dest_reg + offset
	it = memory.find(to_string(t1));
	if (it == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t1 << endl;
	}
	else
	{
		it2 = registers.find(rd);
		it2->second = it->second;
	}
	PrintMem_Reg();
}
void SH(string rs1, string rs2, string off) 
{
	//stores 16 lowest bits
	map<string, string>::iterator it;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); //t1 = rs2
	uint32_t t2 = (t1 << 16); //t2 = last 16bits
	uint32_t t3 = (t2 >> 16); //lowest 16bits + padding of rs2
	t2 = bit_12OverflowSim(stoi(off)); //t2 = offset
	it = registers.find(rs1); 
	t1 = stoi(it->second); //t1 = rs1 (dest)
	t2 = t2 + t1; // t2=offset + t1
	it = memory.find(to_string(t2));
	if (it == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t3));
	}
	else
	{
		it->second = to_string(t3);
	}
	PrintMem_Reg();
	//rs1 is dest
	//rs2 is source get lowest 16bits
}
void SB(string rs1, string rs2, string off)
{ 
	map<string, string>::iterator it;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); //t1 = rs2
	uint32_t t2 = (t1 << 24); //t2 = last 16bits
	uint32_t t3 = (t2 >> 24); //lowest 16bits + padding of rs2
	t2 = bit_12OverflowSim(stoi(off)); //t2 = offset
	it = registers.find(rs1);
	t1 = stoi(it->second); //t1 = rs1 (dest)
	t2 = t2 + t1; // t2=offset + t1
	it = memory.find(to_string(t2));
	if (it == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t3));
	}
	else
	{
		it->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LH(string rs1, string rd, string off) {
	//16BIT SIGNEXTENDED
	map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it = memory.find(to_string(t3));
	if (it == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 16); //t2 = last 16bits
		t3 = (t2 >> 16); //lowest 16bits + padding of rs2
		bitset<32> B3(t3);
		for (int i = 16; i < 32; i++)
		{
			if (B3[15] == 1)
			{
				B3[i] = 1;
			}
			else
			{
				B3[i] = 0;
			}
		}
		it2 = registers.find(rd);
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LB(string rs1, string rd, string off)
{
	//16BIT SIGNEXTENDED
	map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it = memory.find(to_string(t3));
	if (it == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 24); //t2 = last 16bits
		t3 = (t2 >> 24); //lowest 16bits + padding of rs2
		bitset<32> B3(t3);
		for (int i = 8; i < 32; i++)
		{
			if (B3[7] == 1)
			{
				B3[i] = 1;
			}
			else
			{
				B3[i] = 0;
			}
		}
		it2 = registers.find(rd);
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LBU(string rs1, string rd, string off)
{
	//16BIT SIGNEXTENDED
	map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it = memory.find(to_string(t3));
	if (it == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 24); //t2 = last 16bits
		t3 = (t2 >> 24); //lowest 16bits + padding of rs2
		it2 = registers.find(rd);
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LHU(string rs1, string rd, string off) {
	//16BIT SIGNEXTENDED
	map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it = memory.find(to_string(t3));
	if (it == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 16); //t2 = last 16bits
		t3 = (t2 >> 16); //lowest 16bits + padding of rs2
		it2 = registers.find(rd);
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
}

int main()
{
	//int32_t t1 = 2147483647;
	//bitset<32> B1(t1);
	//int32_t t2 = (t1 << 16); //t2 = last 16bits
	//bitset<32> B2(t2);
	//int32_t t3 = (t2 >> 16); //lowest 16bits + padding of rs2
	//bitset<32> B3(t3);
	//cout << B3[15] << endl;
	//for (int i = 16; i < 32; i++)
	//{
	//	if (B3[15] == 1)
	//	{
	//		B3[i] = 1;
	//	}
	//	else
	//	{
	//		B3[i] = 0;
	//	}
	//}
	//cout << B1 << '\n' << B2 << '\n' << B3 << endl;
	//cout << t1 << '\n' << t2 << '\n' << t3 << endl;
	//32 bit signed : 2147483647 --> -2147483648
	//32 bit unsigned: 0 --> 4294967295
	//cout<< Stringtobinary("-2147483647")<<endl; 
							//2147483648 == -2147483648
							//2147483647
	//cout << Stringtobinary(to_string(2147483647)) << endl;
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
