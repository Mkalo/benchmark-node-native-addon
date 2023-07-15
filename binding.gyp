{
  "targets": [
    {
      "target_name": "NativeModule",
      "sources": [
        "NativeModule.cpp",
        "methods.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
