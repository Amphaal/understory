// UnderStory
// An intuitive Pen & Paper experience
// Copyright (C) 2020 Guillaume Vara

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Any graphical resources available within the source code may
// use a different license and copyright : please refer to their metadata
// for further details. Graphical resources without explicit references to a
// different license and copyright still refer to this GPL.

#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>

#include "src/models/File.pb.h"

#include "hash_fnv1a.hpp"

namespace UnderStory {

class FileIntegrator {
 public:
    static File* createFile(const std::filesystem::path &filePath) {
        assert(std::filesystem::exists(filePath));

        // read file content
        std::ifstream fileStream(filePath.c_str(), std::ifstream::in | std::ios::binary);
        std::string fileContent;
        fileContent.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());

        // get file hash
        auto hash = hash_64_fnv1a(fileContent.c_str(), fileContent.length());

        // bind to File
        auto asset = new File;
        asset->set_name(filePath.stem().string());
        asset->set_fileextension(filePath.extension().string());
        asset->set_fnv1ahash(hash);
        asset->set_content(fileContent.c_str());
        asset->set_contentlength(fileContent.length());

        return asset;
    }
};

}  // namespace UnderStory

