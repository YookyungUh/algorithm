#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int tc = 0;
	int cnt = 0;
	char str[1001];
	char *pStr = NULL;
	vector<short> strNum;

	strNum.reserve(500);

	cin >> tc;

	while (tc-- > 0)
	{
		cin >> str;
		pStr = str;

		while (*pStr != '\0')
		{
			strNum.push_back((short)(*pStr << 8) | *(pStr+1));
			pStr += 2;
		}

		sort(strNum.begin(), strNum.end());

		for (cnt = 0 ; cnt < strNum.size() ; cnt++)
			cout << (char)(strNum[cnt] >> 8) << (char)strNum[cnt];

		strNum.clear();
		cout << endl;
	}

	return 0;
}
