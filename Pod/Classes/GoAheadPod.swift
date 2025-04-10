// The Swift Programming Language
// https://docs.swift.org/swift-book

import SwiftUI
import AVFoundation

public struct GoAheadPayNECView: View {
  @State private var personID: String? = nil
  @State private var isEnrolling: Bool = false
  @State private var showError: Bool = false
  @State private var cameraPermissionGranted: Bool = false
  @State private var isCheckingPermission: Bool = true
  private let validityEndDate: Date = Date().addingTimeInterval(86400 * 30) // 30 days from now
  @Environment(\.dismiss) var dismiss

  public init(){
    // Public initializer to make the view accessible from other modules
  }
  
  public var body: some View {
    ZStack {
      if isCheckingPermission {
        ProgressView("Checking camera permission...")
          .onAppear {
            checkCameraPermission()
          }
      } else if cameraPermissionGranted {
        #if targetEnvironment(simulator)
          CaptureSimulation(personID: $personID, isEnrolling: $isEnrolling)
        #else
          
          FaceCaptureView(
            personID: $personID,
            isEnrolling: $isEnrolling,
            showError: $showError,
            validityEndDate: validityEndDate,
            dismiss: dismiss
          )
        #endif
      } else {
        CameraPermissionView(onRequestPermission: requestCameraPermission)
      }
    }.task {
        #if !targetEnvironment(simulator)
            await NeoFaceProvider.configure(NECConfig())
        #endif
    }
  }
  
  private func checkCameraPermission() {
    switch AVCaptureDevice.authorizationStatus(for: .video) {
    case .authorized:
      // Permission already granted
      cameraPermissionGranted = true
      isCheckingPermission = false
    case .notDetermined:
      // Permission not requested yet
      isCheckingPermission = false
    case .denied, .restricted:
      // Permission denied or restricted
      cameraPermissionGranted = false
      isCheckingPermission = false
    @unknown default:
      // Handle future cases
      cameraPermissionGranted = false
      isCheckingPermission = false
    }
  }
  
  private func requestCameraPermission() {
    AVCaptureDevice.requestAccess(for: .video) { granted in
      DispatchQueue.main.async {
        cameraPermissionGranted = granted
      }
    }
  }
}

/// Helper struct to get NEC's environment configuration
struct NECConfig: NECConfigurable {
  var baseURL: String
  var authenticationSubdomain: String
  var workflowsSubdomain: String
  var username: String
  var password: String

  init() {
//      baseURL = "https://mlb-portal.necidelight.com/api"
//      authenticationSubdomain = "auth"
//      workflowsSubdomain = "workflows"
//      username = "WMSClient"
//      password = "Dkzcx7Drg8uJ8KOrTmuEoX4uzDbizzg4"
      baseURL = "https://didndp141.tst.nec-asd.tech/api"
      authenticationSubdomain = "wms-auth-mlb"
      workflowsSubdomain = "wms-workflows-mlb"
      username = "WMS_CLIENT_MLB"
      password = "SNbk6vetD5h15WgAZLCmSb96Wo4ELrqv"
  }
}

// View shown when camera permission is needed
private struct CameraPermissionView: View {
  var onRequestPermission: () -> Void
  
  var body: some View {
    VStack(spacing: 20) {
      Image(systemName: "camera.fill")
        .font(.system(size: 70))
        .foregroundColor(.blue)
      
      Text("Camera Access Required")
        .font(.title2)
        .fontWeight(.bold)
      
      Text("This app needs access to your camera to capture facial data for authentication purposes.")
        .multilineTextAlignment(.center)
        .padding(.horizontal)
      
      Button(action: onRequestPermission) {
        Text("Request Camera Access")
          .fontWeight(.semibold)
          .foregroundColor(.white)
          .padding()
          .background(Color.blue)
          .cornerRadius(10)
      }
      .padding(.top)
      
      Button(action: {
        if let url = URL(string: UIApplication.openSettingsURLString) {
          UIApplication.shared.open(url)
        }
      }) {
        Text("Open Settings")
          .fontWeight(.medium)
          .foregroundColor(.blue)
      }
      .padding(.top, 8)
    }
    .padding()
  }
}
