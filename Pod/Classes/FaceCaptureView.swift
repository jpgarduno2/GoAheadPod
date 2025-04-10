//
//  FaceCaptureView.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

#if !targetEnvironment(simulator)
import SwiftUI
import MLBCustomKit
import NeoFaceUI

struct FaceCaptureView: View {

  // Receives a binding that the view updates with the personId
  @Binding var personID: String?
  @Binding var isEnrolling: Bool
  @Binding var showError: Bool

  @StateObject var observer = NeoFaceObserver()
  let validityEndDate: Date

  var dismiss: DismissAction

  var body: some View {
    VStack {
      switch observer.initializationState {
      case .initializing:
          Text("Initializing camera...")
      case .initializationError:
        ErrorView(
          onRetry: {
            dismiss()
          }, errorText: "There was an issue starting the camera. Please try again",
          buttonText: "Close"
        )
      case .ready(let mlbCustomKit):
        FaceEnrollView(
          customKit: mlbCustomKit,
          result: $observer.result,
          error: $observer.error,
          isEnrolling: $isEnrolling,
          validityEndDate: validityEndDate
        )
      }
    }
    .task {
      await observer.initialize()
    }
    .onChange(of: observer.result) { result in
      withAnimation {
        personID = result?.id
      }
    }
    .onReceive(
      observer.$error
        .compactMap { $0 }
        .throttle(for: .seconds(1), scheduler: RunLoop.main, latest: true)
    ) { error in
//      RUMMonitor.shared().addError(error: error)
      if isEnrolling && !(error is NeoFaceScanError) {
        showError = true
      }
    }
    .background(Color.black)
  }
}
#endif

