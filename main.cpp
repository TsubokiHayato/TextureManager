#include "TextureConverter.h"
#include <filesystem>
#include <stdio.h>
#include <windows.h>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (argc <= 1) {
		printf("画像 or フォルダを exe にドラッグしてください\n");
		system("pause");
		return 0;
	}

	TextureConverter converter;

	for (int i = 1; i < argc; ++i) {
		fs::path p = argv[i];

		if (fs::is_directory(p)) {
			for (auto& e : fs::directory_iterator(p)) {
				if (e.is_regular_file()) {
					auto ext = e.path().extension().string();
					if (ext == ".png" || ext == ".jpg") {
						converter.Convert(e.path().string());
					}
				}
			}
		} else {
			converter.Convert(p.string());
		}
	}

	system("pause");
	return 0;
}
