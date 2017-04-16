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
#include "HeadEnumFile.h"

using namespace std;

int main(void)
{
	//D�claration variable
	char strFilePath[32];

	// Saisie du r�pertoire par l'utilisateur
	cout << "Saisir le repertoire (exemple: M:\\<nom du repertoire>): " << endl;
	cin >> strFilePath;

	// cast en CString avec concat�nation de \\*.*
	CString strNewFilePath = CString(strFilePath) + "\\*.*"; 	// \\*.* =>tous les fichiers du r�pertoire test

	// Appel de la fonction EnumFilesDirectory
	EnumFilesDirectory(strNewFilePath);


}
void EnumFilesDirectory(CString strFilePath)
{
	// D�claration des variables
	HANDLE hEnt;
	WIN32_FIND_DATA ent;
	DWORD dwFileSize;
	DWORD dwFileType;
	LARGE_INTEGER filesize;
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal, stCreate, stAccess, stWrite;
	DWORD dwRet;
	LPTSTR lpszString;
	DWORD dwSize;
	TCHAR szBuf[MAX_PATH];
	// Utilisation de l'API FinFirstFile et FindNextFile pour r�cup�rer le handle de chaque fichier du r�pertoire

	if ((hEnt = FindFirstFile(strFilePath, &ent)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			// R�cup�re le type du fichier
			dwFileType = GetFileType(hEnt);
			// R�cup�re la taille du fichier
			dwFileSize = GetFileSize(hEnt, NULL);
			filesize.LowPart = ent.nFileSizeLow;
			filesize.HighPart = ent.nFileSizeHigh;
			// R�cup�re la date et l'heure de la cr�ation du fichier
			BOOL WINAPI GetFileTime(
				_In_      HANDLE     hEnt,
				_Out_opt_ LPFILETIME lpCreationTime,
				_Out_opt_ LPFILETIME lpLastAccessTime,
				_Out_opt_ LPFILETIME lpLastWriteTime
			);
			GetFileTime(hEnt, &ftCreate, &ftAccess, &ftWrite);

			// Conversion de la date de la derni�re �criture.
			FileTimeToSystemTime(&ftWrite, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stCreate);

			FileTimeToSystemTime(&ftCreate, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stAccess);

			FileTimeToSystemTime(&ftCreate, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stWrite);

			// Affiche <Nom du fichier><Taille><type><cr�ation><acc�s><�criture>
			_tprintf(TEXT("Nom du fichier: %s \n Taille:  %ld bytes type: %d\n"), ent.cFileName, filesize.QuadPart, dwFileType);
			_tprintf(TEXT("Cree le: %02d/%02d/%d a %02d:%02d\n "), stCreate.wDay, stCreate.wMonth, stCreate.wYear, stCreate.wHour, stCreate.wMinute);
			_tprintf(TEXT("Dernier acces en �criture: %02d/%02d/%d � %02d:%02d\n\n "), stWrite.wDay, stWrite.wMonth, stWrite.wYear, stWrite.wHour, stWrite.wMinute);

		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}

