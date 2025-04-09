//
//  NECConfigurable.swift
//  GoAheadPod
//
//  Created by Juan Garduno on 4/9/25.
//

import Foundation

public protocol NECConfigurable {
  var baseURL: String { get }
  var authenticationSubdomain: String { get }
  var workflowsSubdomain: String { get }
  var username: String { get }
  var password: String { get }
}
