#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <cmath>
#include <bitset>
#include <unordered_map>
#include<fstream>
#include<sstream>
using namespace std;
unordered_map<string, string> registers;
map<string, string> memory;
map<int, string>PC_Mem_Ptr;
map<string, string> memory_inst;
int PC=0;
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
	unordered_map<string, string>::iterator it;
	cout << "Regisiters Values : " << endl;
	for (int i = 0; i < 32; i++)
	{
		it = registers.find("x" + to_string(i));
		cout << it->first << " : " << " Decimal : " << it->second << " Hexa : " << Stringtohexa(it->second) << " Binary : " << Stringtobinary(it->second) << endl;
	}
	map<string, string>::iterator it2;
	cout << "Memory Values : " << endl;
	for (it2=memory.begin(); it2 != memory.end(); it2++)
	{
		cout << it2->first << " : " << it2->second << " Hexa : " << Stringtohexa(it2->second) << " Binary : " << Stringtobinary(it2->second) << endl;
	}
}
void ADD(string rd, string rs1, string rs2)
{
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
	int32_t t1 = stoi(it->second);
	int32_t t2 = stoi(imm);
	t1 = t2 + t1;
	it = registers.find(rd);
	it->second = to_string(t1);
	PrintMem_Reg();

}
void XORI(string rd, string rs1, string imm)
{
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
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
	unordered_map<string, string>::iterator it;
	map<int, string>::iterator it2;
	it = registers.find(rd);
	it2 = PC_Mem_Ptr.find(PC);
	it->second = to_string(t2+stoi(it2->second));
	PrintMem_Reg();
}
void SW(string rs1, string rs2, string off) { // sw x9,0(x2)
	//int source_value, destination_value;
	//search for address
	//Found --> overwrite
	//Not Found --> Insert
	unordered_map<string, string>::iterator it;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); // t1 = src value
	it= registers.find(rs1);
	int32_t t2 = stoi(it->second); // t2 = dest value
	//Simulates overflow is offset larger than the 12bit signed cap
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t2 = t2 + t3; //dest = dest_reg + offset
	map <string, string>::iterator it2;
	it2 = memory.find(to_string(t2));
	if (it2 == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t1));
	}
	else
	{
		it2->second = to_string(t1);
	}
	PrintMem_Reg();
}
void LW(string rs1, string rd, string off) {
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	int32_t t1 = stoi(it->second); // t1 = src value (mem)
	it = registers.find(rd);
	int32_t t2 = stoi(it->second); // t2 = dest value (reg)
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t1 = t1 + t3; //dest = dest_reg + offset
	it2 = memory.find(to_string(t1));
	if (it2 == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t1 << endl;
	}
	else
	{
		it = registers.find(rd);
		it->second = it2->second;
	}
	PrintMem_Reg();
}
void SH(string rs1, string rs2, string off) 
{
	//stores 16 lowest bits
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); //t1 = rs2
	uint32_t t2 = (t1 << 16); //t2 = last 16bits
	uint32_t t3 = (t2 >> 16); //lowest 16bits + padding of rs2
	t2 = bit_12OverflowSim(stoi(off)); //t2 = offset
	it = registers.find(rs1); 
	t1 = stoi(it->second); //t1 = rs1 (dest)
	t2 = t2 + t1; // t2=offset + t1
	it2 = memory.find(to_string(t2));
	if (it2 == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t3));
	}
	else
	{
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
	//rs1 is dest
	//rs2 is source get lowest 16bits
}
void SB(string rs1, string rs2, string off)
{ 
	unordered_map<string, string>::iterator it;
	it = registers.find(rs2);
	int32_t t1 = stoi(it->second); //t1 = rs2
	uint32_t t2 = (t1 << 24); //t2 = last 16bits
	uint32_t t3 = (t2 >> 24); //lowest 16bits + padding of rs2
	t2 = bit_12OverflowSim(stoi(off)); //t2 = offset
	it = registers.find(rs1);
	t1 = stoi(it->second); //t1 = rs1 (dest)
	t2 = t2 + t1; // t2=offset + t1
	map<string, string>::iterator it2;
	it2 = memory.find(to_string(t2));
	if (it2 == memory.end())
	{
		memory.emplace(to_string(t2), to_string(t3));
	}
	else
	{
		it2->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LH(string rs1, string rd, string off) {
	//16BIT SIGNEXTENDED
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it2 = memory.find(to_string(t3));
	if (it2 == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it2->second); // t1 = mem[rs1 + offset]
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
		it = registers.find(rd);
		it->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LB(string rs1, string rd, string off)
{
	//16BIT SIGNEXTENDED
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it2 = memory.find(to_string(t3));
	if (it2 == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it2->second); // t1 = mem[rs1 + offset]
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
		it = registers.find(rd);
		it->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LBU(string rs1, string rd, string off)
{
	//16BIT SIGNEXTENDED
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it2 = memory.find(to_string(t3));
	if (it2 == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it2->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 24); //t2 = last 16bits
		t3 = (t2 >> 24); //lowest 16bits + padding of rs2
		it = registers.find(rd);
		it->second = to_string(t3);
	}
	PrintMem_Reg();
}
void LHU(string rs1, string rd, string off) {
	//16BIT SIGNEXTENDED
	unordered_map<string, string>::iterator it;
	map<string, string>::iterator it2;
	it = registers.find(rs1);
	//offset RS1, then load 16bit only
	int32_t t1 = stoi(it->second); //t1 = rs1
	int32_t t3 = bit_12OverflowSim(stoi(off)); //t3 = 12bit offset 
	t3 = t1 + t3; //t3 = rs1 + offset
	it2 = memory.find(to_string(t3));
	if (it2 == memory.end())
	{
		cout << "No Data at Selected Source" << " : " << t3 << endl;
	}
	else
	{
		t1 = stoi(it2->second); // t1 = mem[rs1 + offset]
		int32_t t2 = (t1 << 16); //t2 = last 16bits
		t3 = (t2 >> 16); //lowest 16bits + padding of rs2
		it = registers.find(rd);
		it->second = to_string(t3);
	}
	PrintMem_Reg();
}
void RegisterInit()
{
	for (int i = 0; i < 32; i++)
	{
		string name = "x" + to_string(i);
		registers.emplace(name, "0");
	}
}
void Inst_Print()
{
	map<int, string>::iterator it;
	map<string, string>::iterator it2;
	for (it = PC_Mem_Ptr.begin(); it != PC_Mem_Ptr.end(); it++)
	{
		cout << it->first << " " << it->second<<" ";
		it2 = memory_inst.find(it->second);
		cout << it2->second << endl;

	}
}

int main()
{
	RegisterInit();
	PrintMem_Reg();
	int Strt_Address;
	cout << "Enter the starting address in decimal: " << endl;
	cin >> Strt_Address;
	int FLchoice;
	int IMchoice;
	bool loop1 = 1;
	bool loop2 = 1;
	bool loop3 = 1;
	cin.ignore();
	string instructions;
	map<int, string>::iterator it;
	map<string, string>::iterator it2;
	while (loop1)
	{
		cout << "1. Instruction Entry Options" << endl;
		cout << "2. Data Entry Options" << endl;
		cout << "3. Change Starting Address" << endl;
		cout << "4. Terminate Program" << endl;
		cout << "5. Run Assembly Simulator" << endl;
		cin >> FLchoice;
		//cin.ignore();
			switch (FLchoice)
			{
				case 1:
					loop2 = 1;
					int IEchoice;
					cout << "1. Insert Instructions Manually" << endl;
					cout << "2. Insert Instructions From File" << endl;
					cout << "3. Go Back" << endl;
					cin >> IEchoice;
					cin.ignore();
						switch (IEchoice)
						{
							case 1:
								while (loop2)
								{
									loop3 = 1;
									cout << "1. Insert Instructions" << endl;
									cout << "2. Delete the last instruction" << endl;
									cout << "3. Go Back" << endl;
									cin >> IMchoice;
									cin.ignore();
									switch (IMchoice)
										{
											case 1:
												while (loop3)
												{
													getline(cin, instructions);
													memory_inst.emplace(to_string(Strt_Address), instructions);
													PC_Mem_Ptr.emplace(PC, to_string(Strt_Address));
													Inst_Print();
													PC++;
													Strt_Address -= 4;
													if (instructions == "FENCE" || instructions == "ECALL" || instructions == "EBREAK")
													{
														loop3 = 0;
													}
												}
												break;
											case 2:
												if (memory_inst.size() > 0)
												{
													memory_inst.erase(to_string(Strt_Address + 4));
													PC_Mem_Ptr.erase(PC - 1);
													PC++;
													Strt_Address += 4;
													Inst_Print();
												}
												else
												{
													cout << "No instructions in memory" << endl;
												}
												break;
											case 3:
												loop2 = 0;
												break;
										}
									
								}
								break;
							case 2:
								//Insert from file.
							case 3:
								break;

						}
					break;
				case 2:

					cout << "1. Insert Data Manually" << endl;
					cout << "2. Insert Data From File" << endl;
					cout << "3. Go Back" << endl;
					break;
				case 3:
					cin >> Strt_Address;
					break;
				case 4:
					cout << "Terminated Program." << endl;
					loop1 = 0;
					break;
				case 5:
					cout << "Running RISC-V Assembly Simulator" << endl;
					
					it= PC_Mem_Ptr.begin();
					while (it != PC_Mem_Ptr.end())
					{
						//PC_PTR int, memory address
						//mem_inst memory address, instruction
						cout << endl;
						cout << "Instruction Count : " << it->first << endl;
						cout << "Address Number : " << it->second << endl;
						string line = it->second;
						stringstream s(line);
						getline(s, instructions, ' ');
						if (instructions == "ADD")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << line << endl;
								cout << "Can't modify register x0 " << endl;
								return 0;
							}
							ADD(rd, rs1, rs2);
						}
						else if (instructions == "ADDI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << line << endl;
								cout << "Can't modify register x0 " << endl;
								return 0;
							}
							ADDI(rd, rs1, imm);

						}
						else if (instructions == "SUB")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SUB(rd, rs1, rs2);
						}
						else if (instructions == "XOR")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							XOR(rd, rs1, rs2);

						}
						else if (instructions == "XORI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							XORI(rd, rs1, imm);

						}
						else if (instructions == "OR")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							OR(rd, rs1, rs2);
						}
						else if (instructions == "ORI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							ORI(rd, rs1, imm);

						}
						else if (instructions == "AND")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							AND(rd, rs1, rs2);

						}
						else if (instructions == "ANDI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							ANDI(rd, rs1, imm);

						}
						else if (instructions == "SLT")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLT(rd, rs1, rs2);

						}
						else if (instructions == "SLTU")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLTU(rd, rs1, rs2);

						}
						else if (instructions == "SLTI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLTI(rd, rs1, imm);

						}
						else if (instructions == "SLTIU")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLTIU(rd, rs1, imm);

						}
						else if (instructions == "SLL")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLL(rd, rs1, rs2);
						}
						else if (instructions == "SRL")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SRL(rd, rs1, rs2);
						}
						else if (instructions == "SRA")
						{
							string rd, rs1, rs2;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, rs2);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SRA(rd, rs1, rs2);
						}
						else if (instructions == "SLLI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SLLI(rd, rs1, imm);
						}
						else if (instructions == "SRLI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SRLI(rd, rs1, imm);
						}
						else if (instructions == "SRAI")
						{
							string rd, rs1, imm;
							getline(s, rd, ',');
							getline(s, rs1, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							SRAI(rd, rs1, imm);
						}
						else if (instructions == "BNE")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							//PC_PTR int, memory address
							//mem_inst memory address, instruction
							unordered_map<string, string>::iterator it1;
							it1 = registers.find(rs1);
							int t1 = stoi(it1->second);
							it1 = registers.find(rs2);
							int t3 = bit_12OverflowSim(stoi(imm));
							int t2 = stoi(it1->second);
							if (t1 != t2)
								//address = it->first + t3;
							//Inst_Print();
							// Logic: t3 % 4 and check if = 0 --> correct then PC+ (t3)/4 Offeset from current instruction
								//PRINT THE NEXT INSTRUCTION
						}
						else if (instructions == "BEQ")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							auto it1 = registers.find(rs1);
							int temp1 = stoi(it1->second[0]);
							it1 = registers.find(rs2);
							int temp2 = stoi(it1->second[0]);
							if (temp1 == temp2)
								address = it->first + stoi(imm);
							printMap();
						}
						else if (instructions == "BLT")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							auto it1 = registers.find(rs1);
							int temp1 = stoi(it1->second[0]);
							it1 = registers.find(rs2);
							int temp2 = stoi(it1->second[0]);
							if (temp1 < temp2)
								address = it->first + stoi(imm);

							printMap();

						}
						else if (instructions == "BLTU")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							auto it1 = registers.find(rs1);
							unsigned int temp1 = stoi(it1->second[0]);
							it1 = registers.find(rs2);
							unsigned int temp2 = stoi(it1->second[0]);
							if (temp1 < temp2)
								address = it->first + stoi(imm);
							printMap();

						}
						else if (instructions == "BGE")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							auto it1 = registers.find(rs1);
							int temp1 = stoi(it1->second[0]);
							it1 = registers.find(rs2);
							int temp2 = stoi(it1->second[0]);
							if (temp1 > temp2)
								address = it->first + stoi(imm);
							printMap();

						}
						else if (instructions == "BGEU")
						{
							string rs1, rs2, imm;
							getline(s, rs1, ',');
							getline(s, rs2, ',');
							getline(s, imm);
							auto it1 = registers.find(rs1);
							unsigned int temp1 = stoi(it1->second[0]);
							it1 = registers.find(rs2);
							unsigned int temp2 = stoi(it1->second[0]);
							if (temp1 > temp2)
								address = it->first + stoi(imm);
							printMap();

						}
						else if (instructions == "JAL")
						{
							string ra, imm;
							getline(s, ra, ',');
							getline(s, imm);

							if (ra == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							auto it1 = registers.find(ra);
							it1->second[0] = to_string(address - 4);
							address = it->first + stoi(imm);

							printMap();

						}
						else if (instructions == "JALR")
						{
							string zero, ra, offset;
							getline(s, zero, ',');
							getline(s, offset, '(');
							getline(s, ra, ')');

							auto it1 = registers.find(ra);
							address = stoi(it1->second[0]) + stoi(offset) + 4;


						}
						else if (instructions == "SW")
						{
							string source, destination, offset;
							getline(s, source, ',');
							getline(s, offset, '(');
							getline(s, destination, ')');
							Sw(source, destination, offset);

						}
						else if (instructions == "SH")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							SH(source, destination, offset);

						}
						else if (instructions == "SB")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							SB(source, destination, offset);

						}
						else if (instructions == "LH")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							if (destination == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							LH(source, destination, offset);

						}
						else if (instructions == "LB")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							if (destination == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							LB(source, destination, offset);

						}
						else if (instructions == "LBU")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							if (destination == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							LBU(source, destination, offset);

						}
						else if (instructions == "LHU")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							if (destination == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							LHU(source, destination, offset);

						}
						else if (instructions == "LW")
						{
							string source, destination, offset;
							getline(s, destination, ',');
							getline(s, offset, '(');
							getline(s, source, ')');
							if (destination == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							lw(source, destination, offset);

						}
						else if (instructions == "LUI")
						{
							string rd, imm;
							getline(s, rd, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							LUI(rd, imm);

						}
						else if (instructions == "AUIPC")
						{
							string rd, imm;
							getline(s, rd, ',');
							getline(s, imm);
							if (rd == "x0")
							{
								cout << "Invalid Input !" << endl;
								cout << line << endl;
								cout << "Can't modify register 0 " << endl;
								return 0;
							}
							int value;
							value = stoi(imm) + address;
							AUIPC(rd, to_string(value));

						}
						else if (instructions == "FENCE" || instructions == "ECALL" || instructions == "EBREAK")
						{
							cout << "Halting Instruction Detected. Ending Simulation" << endl;
						}

						else
						{
							cout << "Invalid Input : " << line << endl;
						}

						PC++;
						it = PC_Mem_Ptr.find(PC);
					}
					loop1 = 0;
					break;
				default:
					cout << "Please enter a valid value." << endl;
			}
	}
	
	
	
	//cout << Stringtobinary("-21") << endl;
	//cout << Stringtohexa("-21") << endl;
	/*{
	string input_file_name, program_file_name;
	int address;
	ifstream code, address_file;
	string instruction, line;
	//inisalize  map
	//get user input
	cout << "Enter Assembly Program File name" << endl;
	cin >> input_file_name;
	cout << "Enter the starting address: " << endl;
	cin >> address;
	cout << "Enter Program Data File name" << endl;
	cin >> program_file_name;
	//read and store instructions
	code.open(input_file_name);
	while (getline(code, line))
	{
		insta_addresses.insert({ address ,line });
		address += 4;
	}
	code.close();
	//read and set memory address
	address_file.open(program_file_name);
	while (!address_file.eof()) {
		string address, value;
		getline(address_file, line);
		stringstream s(line);
		getline(s, address, ',');
		getline(s, value, ',');
		memory_address_values.insert({ stoi(address),{value,"0b" + tobinary(value),"0x" + tohexa(value)} });
	}
	address_file.close();
	//generate each instruction
	
	return 0;
	}
	*/
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
