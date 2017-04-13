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
			// Affiche <Nom du fichier><Taille><type>
			_tprintf(TEXT("hFile size: %10d\n"), filesize.HighPart);
			_tprintf(TEXT("Nom du fichier: %s Taille:  %ld bytes type: %d\n"), ent.cFileName, filesize.QuadPart, dwFileType);
		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}