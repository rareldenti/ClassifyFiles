#include <iostream>
#include <string>
#include <windows.h>
#include <io.h>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	// 获取程序路径
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

	cout << "目标路径: " << Path << endl;

	// 获取路径下全部文件名称
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

	// 把所有相同文件名的文件移动到同一以该文件名命名的文件夹
	int total = 0;
	for (size_t i = 0; i < Files.size(); i++)
	{
		string FilePath = Path + Files[i];
		string FileNameWithoutType = Files[i].substr(0, Files[i].find('.'));
		string NewFilePath = Path + FileNameWithoutType + "/";
		string NewFilePathWithFileName = Path + FileNameWithoutType + "/" + Files[i];

		// 把 string 转化为 LPCWSTR
		// 文件本身路径
		std::wstring WSFilePath = std::wstring(FilePath.begin(), FilePath.end());
		LPCWSTR LPFilePath = WSFilePath.c_str();
		// 要移动到的路径，包含文件名
		std::wstring WSNewFilePathWithFileName = std::wstring(NewFilePathWithFileName.begin(), NewFilePathWithFileName.end());
		LPCWSTR LPNewFilePathWithFileName = WSNewFilePathWithFileName.c_str();
		// 要移动到的路径
		std::wstring WSNewFilePath = std::wstring(NewFilePath.begin(), NewFilePath.end());
		LPCWSTR LPNewFilePath = WSNewFilePath.c_str();

		CreateDirectory(LPNewFilePath, NULL);

		if (MoveFileW(LPFilePath, LPNewFilePathWithFileName))
		{
			cout << "Move File :" << FilePath << " To " << NewFilePathWithFileName << " suceesed" << endl;
			total++;
		}
	}

	cout << "共移动了 " << total << " 个文件" << endl;
	system("PAUSE");

	return 1;
}
