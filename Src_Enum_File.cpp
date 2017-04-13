// SEC102 TP1 Exercice1 by Wilfried Poisson
// Objectif: Enum�ration r�cursive de fichiers d'un r�pertoire fournis en param�tre du programme par l'utilisateur
// <Nom du fichier><Taille><Type de fichier><Date cr�ation><Date modification><Dernier acc�s><Attributs fichier>
// V0.1: d�but du TP avec l'utilisation de l'API win32: GetFileSizeEx


#include <windows.h>
#include <stdio.h>
#include <string.h>
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
	char strFilePath[32];

	cout << "Saisir le repertoire (exemple: M:\\<nom du repertoire>): " << endl;
	cin >> strFilePath;
	
	CString strNewFilePath =CString( strFilePath) +"\\*.*";
	// syntax test\*.* => pour chercher tout les fichiers test alors que test\\*.* =>tous les fichiers du r�pertoire test
	//StringCchCopy(szDir, MAX_PATH, TEXT("M:\\test\*.*"));

	if ((hEnt = FindFirstFile(strNewFilePath, &ent)) != INVALID_HANDLE_VALUE)
	{

		do
		{
			dwFileType2 = GetFileType(hEnt);
			//dwFileSize2 = GetFileSize(hEnt, NULL);
			dwFileSize2 = GetFileSize(hEnt, NULL);
			filesize2.LowPart = ent.nFileSizeLow;
			filesize2.HighPart = ent.nFileSizeHigh;
			_tprintf(TEXT("hFile size: %10d\n"), filesize2.HighPart);
			_tprintf(TEXT("Nom du fichier: %s Taille:  %ld bytes type: %d\n"), ent.cFileName, filesize2.QuadPart, dwFileType2);
		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}