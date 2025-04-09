//
//  NeoFaceObserver.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

#if !targetEnvironment(simulator)

  import Foundation
  import MLBCustomKit
  import NeoFaceUI

  class NeoFaceObserver: ObservableObject {
    enum InitializationState {
      case initializing
      case initializationError(Error)
      case ready(CustomKit)
    }

    @Published var initializationState = InitializationState.initializing

    // Passed as bindings to `FaceEnrollView`
    @Published var result: Person?
    @Published var error: Error?

    var captureError: NeoFaceScanError? {
        print((error as? NeoFaceScanError)?.errorDescription ?? "NEO FACE ERROR")
        return error as? NeoFaceScanError
    }

    @MainActor
    func initialize() async {
      do {
        initializationState = .ready(try await NeoFaceProvider.value)
      } catch {
          print(error)
          initializationState = .initializationError(error)
      }
    }
  }

  extension NeoFaceScanError {
    var correctionPrompt: String {
      switch self {
      case .tooClose:
        return "Slowly move your phone farther away from your face."
      case .tooFar:
        return "Slowly move your phone closer to your face."
      case .eyesNotOpen:
        return "Make sure you have both eyes open."
      case .allowedFacesExceeded:
        return "Only one face can be in the frame at a time."
      case .noFacesDetected:
        return "Your face was not detected inside the frame."
      case .notGoodPose:
        return "Please keep your face forward and your phone at eye level."
      case .accessoriesFound:
        return "Please remove any accessories during image capture."
      case .lowQuality:
        return "Quality is low. Try improving your lighting conditions."
      case .noNaturalFace:
        return "Look at the camera with a natural face. Don't smile or make faces."
      case .timeout:
        return "Image capture timed out. Please try again."
      @unknown default:
        return localizedDescription
      }
    }
  }

#endif
