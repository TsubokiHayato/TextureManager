#pragma once
#include <string>
#include <DirectXTex.h>

class TextureConverter {



	public:

		void ConvertTextureWICToDDS(const std::string& filePath);

		void LoadWICTextureFromFile(const std::string& filePath);

		static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	private:
	    DirectX::TexMetadata metadata_;
	    DirectX::ScratchImage scratchImage_;

};
