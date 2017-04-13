// SEC102 TP1 Exercice1 by Wilfried Poisson
// Objectif: Enumération récursive de fichiers d'un répertoire fournis en paramétre du programme par l'utilisateur
// <Nom du fichier><Taille><Type de fichier><Date création><Date modification><Dernier accés><Attributs fichier>
// V0.1: début du TP avec l'utilisation de l'API win32: GetFileSizeEx


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
	//Déclaration variable
	char strFilePath[32];

	// Saisie du répertoire par l'utilisateur
	cout << "Saisir le repertoire (exemple: M:\\<nom du repertoire>): " << endl;
	cin >> strFilePath;

	// cast en CString avec concaténation de \\*.*
	CString strNewFilePath = CString(strFilePath) + "\\*.*"; 	// \\*.* =>tous les fichiers du répertoire test

	// Appel de la fonction EnumFilesDirectory
	EnumFilesDirectory(strNewFilePath);

}
void EnumFilesDirectory(CString strFilePath)
{	
	// Déclaration des variables
	HANDLE hEnt;
	WIN32_FIND_DATA ent;
	DWORD dwFileSize;
	DWORD dwFileType;
	LARGE_INTEGER filesize;
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal;
	DWORD dwRet;
	LPTSTR lpszString;
	DWORD dwSize;
	TCHAR szBuf[MAX_PATH];
	// Utilisation de l'API FinFirstFile et FindNextFile pour récupérer le handle de chaque fichier du répertoire

	if ((hEnt = FindFirstFile(strFilePath, &ent)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			// Récupére le type du fichier
			dwFileType = GetFileType(hEnt);
			// Récupére la taille du fichier
			dwFileSize = GetFileSize(hEnt, NULL);
			filesize.LowPart = ent.nFileSizeLow;
			filesize.HighPart = ent.nFileSizeHigh;
			// Récupére la date et l'heure de la création du fichier
			BOOL WINAPI GetFileTime(
				_In_      HANDLE     hEnt,
				_Out_opt_ LPFILETIME lpCreationTime,
				_Out_opt_ LPFILETIME lpLastAccessTime,
				_Out_opt_ LPFILETIME lpLastWriteTime
			);
			GetFileTime(hEnt, &ftCreate, &ftAccess, &ftWrite);

			// Convert the last-write time to local time.
			FileTimeToSystemTime(&ftWrite, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

			// Build a string showing the date and time.
//			dwRet = StringCchPrintf(lpszString, dwSize,
	//			TEXT("%02d/%02d/%d  %02d:%02d"),
//				stLocal.wMonth, stLocal.wDay, stLocal.wYear,
	//			stLocal.wHour, stLocal.wMinute);
			_tprintf(TEXT("Mois: %02d "), stLocal.wMonth);
		

			// Affiche <Nom du fichier><Taille><type>
			_tprintf(TEXT("Nom du fichier: %s Taille:  %ld bytes type: %d\n"), ent.cFileName, filesize.QuadPart, dwFileType);
		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}
BOOL GetLastWriteTime(HANDLE hFile, LPTSTR lpszString, DWORD dwSize)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal;
	DWORD dwRet;

	// Retrieve the file times for the file.
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
		return FALSE;

	// Convert the last-write time to local time.
	FileTimeToSystemTime(&ftWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	// Build a string showing the date and time.
	dwRet = StringCchPrintf(lpszString, dwSize,
		TEXT("%02d/%02d/%d  %02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);

	if (S_OK == dwRet)
		return TRUE;
	else return FALSE;
}