//
//  CaptureSimulation.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

import SwiftUI

/// Used as place holder for the actual NEC SDK facial recognition experience
struct CaptureSimulation: View {

  @Binding var personID: String?
  @Binding var isEnrolling: Bool

  var body: some View {
    Button("Simulate successful capture") {
      Task {
        isEnrolling = true
        try? await Task.sleep(nanoseconds: 300_000_000)
        personID = "\(Date().timeIntervalSince1970)"
      }
    }
  }
}
