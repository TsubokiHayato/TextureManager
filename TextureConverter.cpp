#include "TextureConverter.h"
#include <windows.h>

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {

	LoadWICTextureFromFile(filePath);



}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	// ファイルパスをワイド文字列に変換
	std::wstring wideFilePath = ConvertMultiByteStringToWideString(filePath);


}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) { 
	
	
	
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	std::wstring wideString;
	wideString.resize(filePathBufferSize);

	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wideString[0], filePathBufferSize);

	return wideString;
}
