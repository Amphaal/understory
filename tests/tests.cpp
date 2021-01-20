// UnderStory
// An intuitive Pen & Paper experience
// Copyright (C) 2020-2021 Guillaume Vara <guillaume.vara@gmail.com>

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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

//
// Test cases
//

// using namespace UnderStory::Network;

// #include "src/core/AssetIntegrator.hpp"

// TEST_CASE("Test asset integration", "[assets]") {
//     spdlog::set_level(spdlog::level::debug);

//     // create package
//     auto path = fs::absolute("./tests/resources/test.png");
//     auto asset = UnderStory::AssetIntegrator::createAsset(path);
//     auto hash = asset.file().file_description().fnv1a_hash();

//     REQUIRE(asset.file().file_description().name() == "test");
//     REQUIRE(asset.file().file_description().file_extension() == ".png");
//     REQUIRE(hash == 9008380550126030887);
//     REQUIRE(asset.file().content_length() == 25579);
//     REQUIRE(asset.dimensions().width() == 290);
//     REQUIRE(asset.dimensions().height() == 300);

//     // integrate package to context
//     auto context = UnderStory::Context::random();
//     UnderStory::AssetContext assetContext(context);
//     assetContext.integrateAsset(asset);

//     // get package back from context
//     auto assetFromContext = assetContext.fetchAsset(hash);
//     REQUIRE(assetFromContext.file().content_length() == 25579);
// }

// #include "src/core/UpdateChecker.hpp"
// using UnderStory::UpdateChecker_Private;

// TEST_CASE("Version comparaison", "[update checker]") {
//     spdlog::set_level(spdlog::level::debug);

//     std::string test_localVersion("0.5.0");
//     auto testUpdateChecker = [test_localVersion](const std::string &remoteVersion) {
//         return UpdateChecker_Private::_isVersionNewerThanLocal(remoteVersion, test_localVersion);
//     };

//     REQUIRE(testUpdateChecker("0.5.1"));
//     REQUIRE(testUpdateChecker("0.5.10"));
//     REQUIRE(testUpdateChecker("1.0"));

//     REQUIRE_FALSE(testUpdateChecker(APP_CURRENT_VERSION));
//     REQUIRE_FALSE(testUpdateChecker("0.5.0"));
//     REQUIRE_FALSE(testUpdateChecker("0.4.10"));
// }