// Step3-3Dll.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

void SearchFile(const char* path, vector<string> &fileList);

int DirectryAnalysis(const char* folderPath, const char* outputPath) {

	// 出力用リスト
	vector<string> fileList;

	SearchFile(folderPath, fileList);

	// 出力先ファイルに書き込み
	ofstream outputFile(outputPath);
	for each (string filePath in fileList)
	{
		outputFile << filePath;
	}

	outputFile.close();

	return 1;
}

// フォルダ内を再帰でファイル検索
void SearchFile(const char* path, vector<string> &fileList) {

	char* subPath = "";
	char* tempPath = "";
	//strcpy(tempPath, path);
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	// ファイル探索
	hFind = FindFirstFile(tempPath, &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return;
	}

	do {
		// フォルダの場合
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(fd.cFileName, "..") !=0 && strcmp(fd.cFileName,".") != 0) {
			//再帰でファイル検索
			wsprintf(subPath, "%s%\\*", tempPath, fd.cFileName);
			SearchFile(subPath, fileList);
		}
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
			// ファイル名をリストに追加
			wsprintf(subPath, "%s%s", tempPath, fd.cFileName);
			fileList.push_back(subPath);
		}

	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
}

//BOOLEAN DirectryAnalysisForBoost(string folderPath, string outputPath) {
//	
//	namespace fs = boost::filesystem;
//	const fs::path path(folderPath);
//
//	ofstream outputfile(outputPath);
//
//	BOOST_FOREACH(const fs::path& p, std::make_pair(fs::recursive_directory_iterator(path),
//													fs::recursive_directory_iterator())) {
//
//		if (!fs::is_directory(p)) {
//			outputfile << p << "\n" << std::endl;
//		}
//
//		outputfile.close();
//	}
//	
//
//	return TRUE;
//}