{

  "targets": [{
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions'],
      'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
      "target_name": "main",
      "sources": [
        "./src/main.cc",
        "./src/object-wrap.cc",
        "./src/object-factory.cc",
        "./src/addable.cc"
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        "include"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
  }]
}
