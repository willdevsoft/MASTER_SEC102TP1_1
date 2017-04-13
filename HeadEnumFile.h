#pragma once
/*
HeadEnumFile.h
---------------
Par Willdevsoft, SEC102 TP1 ex1
---------------
Rôle : prototypes des fonctions de l'énumération de fichiers
*/

void EnumFilesDirectory(CString strFilePath);
BOOL GetLastWriteTime(HANDLE hFile, LPTSTR lpszString, DWORD dwSize);