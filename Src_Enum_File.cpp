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
			// Affiche <Nom du fichier><Taille><type>
			_tprintf(TEXT("hFile size: %10d\n"), filesize.HighPart);
			_tprintf(TEXT("Nom du fichier: %s Taille:  %ld bytes type: %d\n"), ent.cFileName, filesize.QuadPart, dwFileType);
		} while (FindNextFile(hEnt, &ent));

		FindClose(hEnt);
	}
}