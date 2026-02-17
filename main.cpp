#include "TextureConverter.h"
#include <filesystem>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (argc <= 1) {
		printf("画像 or フォルダを exe にドラッグしてください\n");
		system("pause");
		return 0;
	}

	// Parse arguments: support -m N or --mip N to set mipLevels, and @file to read list of paths
	size_t mipLevels = 1;
	std::vector<std::string> inputs;

	for (int i = 1; i < argc; ++i) {
		std::string a = argv[i];
		if (a == "-m" || a == "--mip") {
			if (i + 1 < argc) {
				try {
					int v = std::stoi(argv[++i]);
					if (v < 0) v = 0;
					mipLevels = static_cast<size_t>(v);
				} catch (...) {
					printf("Invalid mip level: %s\n", argv[i]);
					return 1;
				}
			} else {
				printf("Missing value for %s\n", a.c_str());
				return 1;
			}
		} else if (!a.empty() && a[0] == '@') {
			// Read paths from file
			std::string listfile = a.substr(1);
			std::ifstream ifs(listfile);
			if (!ifs) {
				printf("Failed to open list file: %s\n", listfile.c_str());
				return 1;
			}
			std::string line;
			while (std::getline(ifs, line)) {
				if (!line.empty()) inputs.push_back(line);
			}
		} else {
			inputs.push_back(a);
		}
	}

	TextureConverter converter;

	for (const auto& s : inputs) {
		fs::path p = s;

		if (fs::is_directory(p)) {
			for (auto& e : fs::directory_iterator(p)) {
				if (e.is_regular_file()) {
					auto ext = e.path().extension().string();
					if (ext == ".png" || ext == ".jpg") {
						converter.Convert(e.path().string(), mipLevels);
					}
				}
			}
		} else {
			converter.Convert(p.string(), mipLevels);
		}
	}

	system("pause");
	return 0;
}
