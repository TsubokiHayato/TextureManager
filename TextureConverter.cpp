#include "TextureConverter.h"
#include <assert.h>
#include <windows.h>

using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {

	// jpg / png を読み込み
	LoadWICTextureFromFile(filePath);

	// 出力DDSパスを作成（拡張子だけ .dds に変更）
	std::string ddsPath = filePath;
	size_t pos = ddsPath.find_last_of('.');
	if (pos != std::string::npos) {
		ddsPath = ddsPath.substr(0, pos);
	}
	ddsPath += ".dds";

	std::wstring wideDDSPath = ConvertMultiByteStringToWideString(ddsPath);

	// DDSとして保存
	HRESULT hr = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, wideDDSPath.c_str());

	assert(SUCCEEDED(hr));
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	std::wstring wideFilePath = ConvertMultiByteStringToWideString(filePath);

HRESULT hr = LoadFromWICFile(wideFilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {

	int size = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	std::wstring wideString(size, L'\0');

	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wideString[0], size);

	return wideString;
}
