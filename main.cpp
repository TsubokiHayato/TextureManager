#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include <windows.h>
#include "TextureConverter.h"

enum Argment
{
	kApplicationPath,
	kFilePath,

	NumArgments
};

int main(int argc, char* argv[]) {


	assert(argc >= NumArgments);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");
	return 0;
}