//
//  ErrorView.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

import SwiftUI

struct ErrorView: View {

  var onRetry: (() -> Void)

  let errorText: String

  var buttonText: String

  init(onRetry: @escaping () -> Void, errorText: String, buttonText: String) {
    self.onRetry = onRetry
    self.errorText = errorText
    self.buttonText = buttonText
  }

  var body: some View {
    VStack {
        Text(errorText)
//      HomePlateShape()
//        .stroke(Color.gray.opacity(0.1), lineWidth: 5)
//        .frame(width: .infinity)
//        .aspectRatio(1.1, contentMode: .fit)
//        .background {
//          Image("mlbLogo", bundle: .module)
//            .resizable()
//            .scaledToFill()
//            .aspectRatio(2.0, contentMode: .fit)
//            .frame(width: 130)
//            .clipped()
//        }
//        .offset(y: 50)
//        .accessibilityHidden(true)
      Spacer()
//      Text(errorText)
//        .textStyle(.heading2)
//        .foregroundColor(.white)
//        .multilineTextAlignment(.center)
//        .padding([.leading, .trailing], 20)
//        .padding(.bottom, 40)
//        .accessibilitySortPriority(2)
//      Button(buttonText, action: onRetry)
//        .buttonStyle(.primary(textStyle: .label3Emphasis, colorScheme: .dark))
//        .padding([.leading, .trailing], 15)
//        .padding(.bottom, 20)
//        .accessibilitySortPriority(1)
//        .trackRUMTapAction(name: "Cancel on Error View")
    }
    .background(Color.black)
  }
}

struct ErrorView_Previews: PreviewProvider {
  static var previews: some View {
    ErrorView(
      onRetry: {}, errorText: "There was an error uploading your Go-Ahead ID...",
      buttonText: "Retry")
  }
}
