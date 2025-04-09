// swift-tools-version: 5.10
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "GoAheadPod",
    platforms: [.iOS(.v17)],
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "GoAheadPod",
            targets: ["GoAheadPod"]),
        .library(
          name: "NeoFaceKit",
          targets: ["NeoFaceKit", "NeoFaceGL"]),
        .library(
          name: "NeoFaceUI",
          targets: ["NeoFaceUI", "NeoFaceKit", "NeoFaceGL"]),
        .library(
          name: "OrchestratorKit",
          targets: ["OrchestratorKit", "ServiceContextKit"])
    ],
    dependencies: [
      .package(url: "https://github.com/ribtiago/SwiftUIExtras.git", from: "1.0.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .target(
            name: "GoAheadPod",
            dependencies: [
              "MLBCustomKit",
              "MLBOrchestratorKit",
              "NeoFaceKit",
              "NeoFaceUI",
              "OrchestratorKit",
              "SwiftUIExtras",
            ],
            resources: [
              .process("NEC/LicenseGL2.lic"),
            ]),
          .binaryTarget(name: "MLBCustomKit", path: "MLBCustomKit.xcframework"),
          .binaryTarget(name: "MLBOrchestratorKit", path: "MLBOrchestratorKit.xcframework"),
          .binaryTarget(name: "NeoFaceKit", path: "Frameworks/NeoFaceKit.xcframework"),
          .binaryTarget(name: "NeoFaceUI", path: "Frameworks/NeoFaceUI.xcframework"),
          .binaryTarget(name: "NeoFaceGL", path: "Frameworks/NeoFaceGL2_1.xcframework"),
          .binaryTarget(name: "OrchestratorKit", path: "Frameworks/OrchestratorKit.xcframework"),
          .binaryTarget(name: "ServiceContextKit", path: "Frameworks/ServiceContextKit.xcframework"),

    ]
)
