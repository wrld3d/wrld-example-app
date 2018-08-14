# SAML Authentication (Android-Only) Example

**Not intended for use in a production environment. Illustrative purposes only.**

### Requirements

This is a branch intended for use alongside the [WRLD SAML SP](https://github.com/wrld3d/wrld-saml-sp). 
Please follow the instructions on the `wrld-saml-sp` repository to get an instance of a SAML SP running before using this branch.

**Android**. There is no iOS SAML example yet.

### Authentication / Configuration

Follow the usual setup for Android development.

Copy the provided `samlconf.yml` over the `config/samlconf.yml` file in your local `wrld-saml-sp` folder and re-run `docker-compose up` on the Vagrant instance.

**Edit line 204 of `android\src\com\eegeo\mobileexampleapp\BackgroundThreadActivity.java` with the LAN IP of the machine that is running the SAML SP instance. This is necessary!**

**You will also need to add your LAN IP to the `saml_authentication_success_url` variables in `samlconf.yml`, so that it redirects properly!**

By default, this will use the Samling serverless IDP sandbox. 

When you launch wrld-example-app on Android, you will see a WebView on screen. Tap the `Login` link, and you will be redirected to the Samling serverless IDP sandbox. Write some information into the `Name Identifier` box, then press `Next` and then `Post Response!`. If all goes well, the WebView should automatically disappear when it detects that the correct cookie is present.