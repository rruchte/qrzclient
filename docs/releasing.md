# QRZ Client release process

The workflow `.github/workflows/release.yml` compiles the CLI on Windows x64, Intel macOS and Ubuntu 24.04 Linux x64. It runs `ctest`, packages the binary and LICENSE/README, and checks the three platform packages before publishing.

## Publish

After merging a green CI PR to `main`, choose a **new** version tag. Historical `v1.0.0`, `v1.1.0` and `v1.2.0` tags already exist and must not be reused. For the first multiplatform release, if that tag is unused:

```bash
git switch main
git pull --ff-only
git tag -a v1.3.0 -m "QRZ Client v1.3.0"
git push origin v1.3.0
```

The tagged workflow produces:

- `qrz-windows-x64.zip`
- `qrz-macos-x64.tar.gz` (Intel x86_64, unsigned)
- `qrz-linux-x64.tar.gz` (Ubuntu 24.04 build baseline)
- `SHA256SUMS`

It must pass build/tests for all three platforms before publishing the GitHub Release. A pull request exercises the build and artifact validation but does not publish. CI runs the offline GTest unit tests; existing `AppControllerTests` instantiate the real interactive controller and are **excluded from unattended CI**. They can be enabled locally with `-DQRZCLIENT_ENABLE_INTERACTIVE_TESTS=ON` in a configured interactive environment. These tests are not yet hermetic and should ultimately use injected mock clients. CI cannot validate live QRZ authentication without credentials. Smoke-test installation and live callsign, DXCC, and biography queries on each supported OS before publishing.

## Known limitations

Static third-party linking is used to minimize runtime dependencies, but Linux still depends on a compatible system glibc and platform libraries. Windows and macOS packages are CLI binaries, not installers. macOS is not signed or notarized, and there is no native Apple Silicon artifact yet.

## Security follow-up

Poco's current HTTPS configuration disables peer-certificate validation (`VERIFY_NONE`). This must be corrected before describing transport security as fully authenticated. The local password encryption also derives its key from the callsign and is not a replacement for OS credential storage. Neither is changed by the CI/release workflow.
