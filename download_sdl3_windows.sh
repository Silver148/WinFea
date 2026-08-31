#!/usr/bin/env bash
set -euo pipefail

APP_NAME="$(basename "$0")"

usage() {
  cat <<EOF
Usage: $APP_NAME [output_dir]

Downloads the official Windows MinGW SDL3 development package to the given
folder (default: ./deps/SDL3).

Examples:
  ./$APP_NAME
  ./$APP_NAME ./deps/SDL3
  SDL3_VERSION=3.2.18 ./$APP_NAME
  SDL3_VERSION=latest ./$APP_NAME
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

OUT_DIR="${1:-$PWD/deps/SDL3}"
SDL3_VERSION="${SDL3_VERSION:-latest}"

if ! command -v curl >/dev/null 2>&1; then
  echo "Error: curl is required but not installed." >&2
  exit 1
fi

if ! command -v python3 >/dev/null 2>&1; then
  echo "Error: python3 is required but not installed." >&2
  exit 1
fi

if [[ "$SDL3_VERSION" == "latest" ]]; then
  ASSET_URL="$(curl -fsSL "https://api.github.com/repos/libsdl-org/SDL/releases/latest" \
    | python3 -c 'import sys, json; data = json.load(sys.stdin); matches = [a["browser_download_url"] for a in data.get("assets", []) if "SDL3-devel" in a.get("name", "") and "mingw" in a.get("name", "").lower() and a.get("name", "").endswith(".tar.gz")]; print(matches[0] if matches else "")')"

  if [[ -z "$ASSET_URL" ]]; then
    echo "Error: could not find a MinGW SDL3 archive in the latest SDL release." >&2
    exit 1
  fi
else
  ASSET_URL="https://github.com/libsdl-org/SDL/releases/download/${SDL3_VERSION}/SDL3-devel-${SDL3_VERSION}-mingw.tar.gz"
fi

mkdir -p "$OUT_DIR"
TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

curl -fL --retry 3 --output "$TMP_DIR/sdl3.tar.gz" "$ASSET_URL"

tar -xzf "$TMP_DIR/sdl3.tar.gz" -C "$TMP_DIR"

EXTRACTED_ROOT="$(find "$TMP_DIR" -mindepth 1 -maxdepth 1 -type d | head -n 1)"

if [[ -z "$EXTRACTED_ROOT" ]]; then
  echo "Error: the SDL3 archive did not extract to a directory." >&2
  exit 1
fi

cp -a "$EXTRACTED_ROOT"/. "$OUT_DIR"/

PREFIX_HINT=""
if [[ -d "$OUT_DIR/x86_64-w64-mingw32" ]]; then
  PREFIX_HINT="$OUT_DIR/x86_64-w64-mingw32"
fi

cat <<EOF
SDL3 downloaded successfully.
Location: $OUT_DIR

CMake example:
  cmake -DCMAKE_TOOLCHAIN_FILE=mingw-cmake/mingw-toolchain.cmake \
        -DCMAKE_PREFIX_PATH="$PREFIX_HINT" \
        ..

If your SDL3 package uses a different root directory, point CMAKE_PREFIX_PATH to the
folder that contains lib/cmake/SDL3 or the x86_64-w64-mingw32 directory.
EOF
