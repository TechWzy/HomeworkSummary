#include<iostream>
#include<cstring>
using namespace std;

const int maxLen = 1024;

bool virusCopy(char virusDna[]) {
	int dnaLen = strlen(virusDna);
	if (dnaLen >= 612) {
		printf("Dna序列过长...\n");
		return false;
	}
	for (int i = 0;i < dnaLen;i++) {
		virusDna[dnaLen + i] = virusDna[i];
	}
	virusDna[2 * dnaLen] = '\0';
}

bool IdInfected(const char virusDna[],const  char personDna[], const int vlen) {
	int pLen = strlen(personDna);	//	主串的长度
	int vvLen = strlen(virusDna);	// 复制病毒串的长度

	// pst代表主串的起始匹配位置
	for (int pst = 0;pLen - pst >= vlen;pst++) {
		//	病毒串的起始匹配位置
		for (int vst = 0;vvLen - vst >= vlen;vst++) {
			// 开始匹配
			bool flag = true;
			for (int i = 0;i < vlen;i++) {
				if (virusDna[i + vst] != personDna[i + pst]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return flag;
			}
		}
	}
	return false;
}

int main() {
	char virusDna[maxLen];
	char personDna[maxLen];

	while (cin >> virusDna >> personDna && virusDna[0]!='0'&& personDna[0]!='0') {
		// 病毒DNA复制
		int vLen = strlen(virusDna);
		bool res = virusCopy(virusDna);
		if (!res) {
			break;
		}
		res = IdInfected(virusDna, personDna, vLen);
		if (res) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	return 0;
}