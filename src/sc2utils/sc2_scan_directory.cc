#include "sc2_scan_directory.h"

#include <cassert>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

namespace sc2 {

namespace {

std::string JoinDirFile(const std::filesystem::path& directory_path, std::string_view name) {
    return (directory_path / name).string();
}

}  // namespace

int scan_directory(const char* directory_path, std::vector<std::string>& files, bool full_path, bool list_directories) {
    if (!directory_path || !*directory_path) {
        return 0;
    }

    DIR* dir;
    dir = opendir(directory_path);
    if (!dir) {
        return 0;
    }

    struct dirent* ent;

    while ((ent = readdir(dir)) != nullptr) {
        switch (ent->d_type) {
            case DT_REG: {
                if (list_directories) {
                    continue;
                }

                if (!full_path) {
                    files.push_back(ent->d_name);
                } else {
                    files.push_back(JoinDirFile(directory_path, ent->d_name));
                }
                break;
            }
            case DT_DIR: {
                if (!list_directories || !*ent->d_name) {
                    continue;
                }

                if (std::strcmp(ent->d_name, ".") == 0 || std::strcmp(ent->d_name, "..") == 0) {
                    continue;
                }

                if (!full_path) {
                    files.push_back(ent->d_name);
                } else {
                    files.push_back(JoinDirFile(directory_path, ent->d_name));
                }
                break;
            }
        }
    }

    return (int)files.size();
}

}  // namespace sc2
