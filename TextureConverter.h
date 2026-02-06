#pragma once
#include <DirectXTex.h>
#include <string>

class TextureConverter {
public:
	void Convert(const std::string& path);

private:
	static std::wstring ToWString(const std::string& s);

	DirectX::ScratchImage image_;
	DirectX::TexMetadata metadata_;
};
