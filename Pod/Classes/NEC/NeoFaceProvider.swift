//
//  NeoFaceProvider.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

#if !targetEnvironment(simulator)

  import Foundation
  import os
  import MLBCustomKit

  enum NeoFaceProvider {
    // NeoFace can only be initialized once
    private static var task: Task<CustomKit, Error>?

    static func configure(_ config: NECConfigurable) async {
      if task != nil { return }
      task = .init {
        let loader = try await NeoFaceLoader(config: config)
        return loader.customKit
      }
    }

    static var value: CustomKit {
      get async throws {
        guard let task = task else { throw NeoFaceProviderError.configureNotCalled }
        return try await task.value
      }
    }

    static let logger = os.Logger(
      subsystem: "com.mlb.AtTheBallpark.GoAhead", category: "NeoFaceProvider")
  }

  extension NeoFaceProvider {
    private actor NeoFaceLoader {
      let downloadsURL: URL
      let licensePath: String
      let customKit: CustomKit

      static var licensePath: String {
        get throws {
          guard let licensePath = Bundle.module.path(forResource: "LicenseGL2", ofType: "lic")
          else {
            throw NeoFaceProviderError.nilLicensePath
          }
          print(licensePath)
          return licensePath
        }
      }

      init(config: NECConfigurable) async throws {
        // Initialization has many failure points and cannot succeed if using the debugger,
        // hence the heavy handed error handling and logging here
        func log(_ error: Error, step: String) {
          NeoFaceProvider.logger.error("\(step): \(error.localizedDescription)")
//          RUMMonitor.shared().addAttribute(forKey: "NECLoaderStep", value: step)
          dump(error)
        }

        do {
          downloadsURL = try await DownloadManager().completedDownloadsURL
        } catch {
          log(error, step: "download")
          throw error
        }

        do {
          licensePath = try Self.licensePath
        } catch {
          log(error, step: "license")
          throw error
        }

        do {
          self.customKit = try await CustomKit(
            baseURL: config.baseURL,
            authenticationSubdomain: config.authenticationSubdomain,
            workflowsSubdomain: config.workflowsSubdomain,
            username: config.username,
            password: config.password,
            licensePath: licensePath,
            dictionaryPath: downloadsURL.path)
        } catch {
          log(error, step: "configure")
          throw error
        }
      }
    }
  }

  extension NeoFaceProvider {

    private struct DownloadManager {

      var completedDownloadsURL: URL {
        get async throws {
          let fileManger = FileManager.default
          let logger = NeoFaceProvider.logger

          let downloadStartDate = Date()
          logger.info("beginning resource downloads")

          let bucketPath = "bp-nec"
          guard
            let docsDirectoryURL = fileManger.urls(for: .documentDirectory, in: .userDomainMask)
              .first
          else {
            throw NeoFaceProviderError.nilDirectory
          }

          let downloadsDirectoryURL = docsDirectoryURL.appendingPathComponent(bucketPath)

          if !fileManger.fileExists(atPath: downloadsDirectoryURL.path) {
            try fileManger.createDirectory(
              at: downloadsDirectoryURL, withIntermediateDirectories: true)
            logger.info("directory created")
          }

//          let storage = Storage.storage().reference().child(bucketPath)
//          let result = try await storage.listAll()

//          for item in result.items {
//
//            let itemURL = downloadsDirectoryURL.appendingPathComponent(item.name)
//
//            if fileManger.fileExists(atPath: itemURL.path) {
//              RUMMonitor.shared().addAttribute(forKey: "NECDownloadSkip", value: true)
//              logger.info("skipping download of \(item.name) because the file already exists")
//              continue
//            }
//
//            logger.info("downloading: \(item.name)")
//            let _ = try await item.writeAsync(toFile: itemURL)
//            let resourceDownloadTime = (Date().timeIntervalSince(downloadStartDate) * 1000)
//
//            RUMMonitor.shared().addAttribute(forKey: "NECDownloadTime", value: resourceDownloadTime)
//            logger.info("download complete: \(item.name)")
//          }

          logger.info("completed resource downloads")

          return downloadsDirectoryURL
        }
      }
    }
  }

  enum NeoFaceProviderError: Error {
    case nilLicensePath
    case nilDirectory
    case nilServerConfig
    case configureNotCalled
  }

#endif
