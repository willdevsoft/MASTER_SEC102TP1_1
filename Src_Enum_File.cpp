// SEC102 TP1 Exercice1 by Wilfried Poisson
//1
// How to get file size using WIN32 API ?
// V1.0: début du TP avec l'utilisation de l'API win32: GetFileSizeEx
//Enumération de fichiers dans un répertoire
//How to get file size using WIN32 API ? Is there any direct API available ?

#include <windows.h>
#include <stdio.h>
#include <string>
#include <atlstr.h> 
#include <iostream>
#include <tchar.h>
#include <strsafe.h>
using namespace std;
int main(void)
{
	HANDLE hEnt;
	WIN32_FIND_DATA ent;
	CString folder = "M:\\test\*.*";
	TCHAR szDir[MAX_PATH];
	DWORD dwFileSize2;
	DWORD dwFileType2;
	LARGE_INTEGER filesize2;
	// syntax test\*.* => pour chercher tout les fichiers test alors que test\\*.* =>tous les fichiers du répertoire test
	StringCchCopy(szDir, MAX_PATH, TEXT("M:\\test\\*.*"));
	if ((hEnt = FindFirstFile(szDir, &ent)) != INVALID_HANDLE_VALUE)
	{

		do
		{
			dwFileType2 = GetFileType(hEnt);
			//dwFileSize2 = GetFileSize(hEnt, NULL);
			dwFileSize2 = GetFileSize(hEnt, NULL);
			filesize2.LowPart = ent.nFileSizeLow;
			filesize2.HighPart = ent.nFileSizeHigh;
			_tprintf(TEXT("hFile size: %10d\n"), filesize2.HighPart);
			_tprintf(TEXT("  %s  %ld bytes type= %d\n"), ent.cFileName, filesize2.QuadPart, dwFileType2);
		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}