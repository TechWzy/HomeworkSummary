#include<iostream>
#include<cstring>
using namespace std;

const int maxLen = 1024;

bool virusCopy(char virusDna[]) {
	int dnaLen = strlen(virusDna);
	if (dnaLen >= 612) {
		printf("Dna���й���...\n");
		return false;
	}
	for (int i = 0;i < dnaLen;i++) {
		virusDna[dnaLen + i] = virusDna[i];
	}
	virusDna[2 * dnaLen] = '\0';
}

bool IdInfected(const char virusDna[],const  char personDna[], const int vlen) {
	int pLen = strlen(personDna);	//	�����ĳ���
	int vvLen = strlen(virusDna);	// ���Ʋ������ĳ���

	// pst������������ʼƥ��λ��
	for (int pst = 0;pLen - pst >= vlen;pst++) {
		//	����������ʼƥ��λ��
		for (int vst = 0;vvLen - vst >= vlen;vst++) {
			// ��ʼƥ��
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
		// ����DNA����
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