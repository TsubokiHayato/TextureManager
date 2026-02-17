#include "TextureConverter.h"
#include <filesystem>
#include <stdio.h>
#include <windows.h>

using namespace DirectX;
namespace fs = std::filesystem;

void TextureConverter::Convert(const std::string& path, size_t mipLevels) {
	std::wstring wpath = ToWString(path);

	HRESULT hr = LoadFromWICFile(wpath.c_str(), WIC_FLAGS_NONE, &metadata_, image_);
	if (FAILED(hr)) {
		printf("Load failed: %s\n", path.c_str());
		return;
	}

	// If user requested mipLevels > 1, generate mipmaps. If mipLevels == 0, generate full chain.
	if (mipLevels != 1) {
		ScratchImage mipChain;
		size_t levels = mipLevels;
		if (levels == 0) // 0 indicates full chain in GenerateMipMaps
			levels = 0;

		hr = GenerateMipMaps(image_.GetImages(), image_.GetImageCount(), metadata_, TEX_FILTER_DEFAULT, levels, mipChain);
		if (FAILED(hr)) {
			printf("GenerateMipMaps failed: %s\n", path.c_str());
			return;
		}

		// Update metadata and image_ to mipChain
		metadata_ = mipChain.GetMetadata();
		image_ = std::move(mipChain);
	}

	fs::create_directory("DDS");

	fs::path out = fs::path("DDS") / fs::path(path).stem();
	out += ".dds";

	hr = SaveToDDSFile(image_.GetImages(), image_.GetImageCount(), metadata_, DDS_FLAGS_NONE, out.wstring().c_str());

	if (FAILED(hr)) {
		printf("Save failed\n");
		return;
	}

	printf("OK : %s\n", out.string().c_str());
}

std::wstring TextureConverter::ToWString(const std::string& s) {
	int size = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, nullptr, 0);
	std::wstring ws(size, L'\0');
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, ws.data(), size);
	return ws;
}
