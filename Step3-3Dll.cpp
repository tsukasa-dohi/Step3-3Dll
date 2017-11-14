// Step3-3Dll.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

void SearchFile(const char* path, vector<string> &fileList);

int DirectryAnalysis(const char* folderPath, const char* outputPath) {

	// �o�͗p���X�g
	vector<string> fileList;

	SearchFile(folderPath, fileList);

	// �o�͐�t�@�C���ɏ�������
	ofstream outputFile(outputPath);
	for each (string filePath in fileList)
	{
		outputFile << filePath;
	}

	outputFile.close();

	return 1;
}

// �t�H���_�����ċA�Ńt�@�C������
void SearchFile(const char* path, vector<string> &fileList) {

	char* subPath = "";
	char* tempPath = "";
	//strcpy(tempPath, path);
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	// �t�@�C���T��
	hFind = FindFirstFile(tempPath, &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return;
	}

	do {
		// �t�H���_�̏ꍇ
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(fd.cFileName, "..") !=0 && strcmp(fd.cFileName,".") != 0) {
			//�ċA�Ńt�@�C������
			wsprintf(subPath, "%s%\\*", tempPath, fd.cFileName);
			SearchFile(subPath, fileList);
		}
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
			// �t�@�C���������X�g�ɒǉ�
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