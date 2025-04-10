Pod::Spec.new do |s|
  s.name             = 'GoAheadPod'
  s.version          = '0.1.0' # Match your Swift Package version
  s.summary          = 'Cocoa Pod containing the NEC SDK'
  s.description      = <<-DESC
                        Cocoa Pod containing the NEC SDK
                       DESC
  s.homepage         = 'https://mlb.com'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'juan Garduno' => 'juan.garduno@mlb.com' }
  # Using a file URL to the local directory
  s.source           = { :http => 'file://' + __dir__ + '/GoAheadPod.tar.gz' }
  
  s.ios.deployment_target = '15.0' # Match your Swift Package's deployment target
  
  # Source files - all Swift files from your package
  s.source_files = 'Pod/Classes/**/*'
  
  # Resources if your package had any
  # s.resource_bundles = {
  #   'GoAheadPod' => ['Pod/Assets/**/*', '!Pod/Assets/**/*.xcframework/**']
  # }
  
  # Swift version - match what your package used
  s.swift_version = '5.0'
  
  # Frameworks directly in the Assets folder
  s.vendored_frameworks = [
    'Pod/Assets/Frameworks/NeoFaceGL2_1.xcframework', 
    'Pod/Assets/Frameworks/NeoFaceKit.xcframework',
    'Pod/Assets/Frameworks/NeoFaceUI.xcframework',
    'Pod/Assets/Frameworks/OrchestratorKit.xcframework',
    'Pod/Assets/Frameworks/ServiceContextKit.xcframework',
    'Pod/Assets/MLBCustomKit.xcframework',
    'Pod/Assets/MLBOrchestratorKit.xcframework'
  ]
  
  # Configuration to completely disable simulator builds
  s.pod_target_xcconfig = { 
    'ENABLE_BITCODE' => 'NO',
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64',
    'VALID_ARCHS' => 'arm64 armv7',
    'ONLY_ACTIVE_ARCH' => 'YES'
  }
  
  # User target configuration to disable simulator builds
  s.user_target_xcconfig = { 
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
  }

  s.spm_dependency   "SwiftUIExtras/SwiftUIExtras"

  # Specify that this is a static framework
  s.static_framework = true
  
  # Explicitly specify that this pod is only for devices
  s.platform = :ios, '15.0'
end
