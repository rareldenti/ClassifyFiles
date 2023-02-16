#include <iostream>
#include <string>
#include <windows.h>
#include <io.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc,char* argv)
{
	// ��ȡ����·��
	WCHAR CrruentPath[256];
	GetCurrentDirectory(256, CrruentPath);
	wstring WSPath;
	WSPath.append(CrruentPath);

	for (size_t i = 0; i < WSPath.size(); i++)
	{
		if (WSPath[i] == '\\')
			WSPath[i] = '/';
	}

	string Path = string(WSPath.begin(), WSPath.end()) + '/';
	string FileType = "*.*";

	cout << "Ŀ��·��: " << Path << endl;

	// ��ȡ·����ȫ���ļ�����
	vector<string> Files;
	_finddata_t file;
	long long lf = _findfirst((Path + FileType).c_str(), &file);
	if (lf == -1)
	{
		return 0;
	}
	else 
	{
		cout << file.name << endl;
		Files.push_back(file.name);

		while (_findnext(lf, &file) != -1)
		{
			Files.push_back(file.name);
			cout << file.name << endl;
		}
	}

	// ��������ͬ�ļ������ļ��ƶ���ͬһ�Ը��ļ����������ļ���
	int total = 0;
	for (size_t i = 0; i < Files.size(); i++)
	{
		string FilePath = Path + Files[i];
		string FileNameWithoutType = Files[i].substr(0, Files[i].find('.'));
		string NewFilePath = Path + FileNameWithoutType + "/";
		string NewFilePathWithFileName = Path + FileNameWithoutType + "/" + Files[i];

		// �� string ת��Ϊ LPCWSTR
		// �ļ�����·��
		std::wstring WSFilePath = std::wstring(FilePath.begin(), FilePath.end());
		LPCWSTR LPFilePath = WSFilePath.c_str();
		// Ҫ�ƶ�����·���������ļ���
		std::wstring WSNewFilePathWithFileName = std::wstring(NewFilePathWithFileName.begin(), NewFilePathWithFileName.end());
		LPCWSTR LPNewFilePathWithFileName = WSNewFilePathWithFileName.c_str();
		// Ҫ�ƶ�����·��
		std::wstring WSNewFilePath = std::wstring(NewFilePath.begin(), NewFilePath.end());
		LPCWSTR LPNewFilePath = WSNewFilePath.c_str();

		CreateDirectory(LPNewFilePath, NULL);

		if (MoveFileW(LPFilePath, LPNewFilePathWithFileName))
		{
			cout << "Move File :" << FilePath << " To " << NewFilePathWithFileName << " suceesed" << endl;
			total++;
		}
	}

	cout << "���ƶ��� " << total << " ���ļ�" << endl;
	system("PAUSE");

	return 1;
}
