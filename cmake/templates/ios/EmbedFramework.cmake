

# Copy and sign custom frameworks - equivalent to 'Embed framework' in Xcode IDE.
function(embed_framework target_name framework_name framework_src_dir framework_code_sign_identity)

  # Create Frameworks folder in app bundle
  add_custom_command(
      TARGET ${target_name}
      POST_BUILD COMMAND /bin/sh -c
      \"
      if ! ${CMAKE_COMMAND} -E make_directory "\${CONFIGURATION_BUILD_DIR}/\${FRAMEWORKS_FOLDER_PATH}" \&\>/dev/null \; then
          echo "Failed to create Frameworks directory in app bundle" \;
          exit 1 \;
      fi
      \"
  )

  # Copy framework to app bundle
  add_custom_command(
      TARGET ${target_name}
      POST_BUILD COMMAND /bin/sh -c
      \"
      if ! ${CMAKE_COMMAND} -E copy_directory "\${PROJECT_DIR}/${framework_src_dir}/${framework_name}.framework" "\${CONFIGURATION_BUILD_DIR}/\${FRAMEWORKS_FOLDER_PATH}/${framework_name}.framework" \&\>/dev/null \; then
          echo "Failed to copy framework ${framework_name} to app bundle" \;
          exit 1 \;
      fi
      \"
  )

  # Remove Headers from Framework in app bundle
  add_custom_command(
      TARGET ${target_name}
      POST_BUILD COMMAND /bin/sh -c
      \"
      if ! ${CMAKE_COMMAND} -E remove_directory "\${CONFIGURATION_BUILD_DIR}/\${FRAMEWORKS_FOLDER_PATH}/${framework_name}.framework/Headers/" \&\>/dev/null \; then
          echo "Failed to remove Headers from framework ${framework_name}" \;
          exit 1 \;
      fi
      \"
  )

  # Codesign framework
  add_custom_command(
      TARGET ${target_name}
      COMMENT "codesigning framework ${framework_name}"
      POST_BUILD COMMAND /bin/sh -c "codesign --force --verbose \${CONFIGURATION_BUILD_DIR}/\${FRAMEWORKS_FOLDER_PATH}/${framework_name}.framework --sign \'${framework_code_sign_identity}\' "
      VERBATIM
  )

endfunction()

