#!/usr/bin/env bash
set -euo pipefail

APP_NAME="$(basename "$0")"

usage() {
  cat <<EOF
Usage: $APP_NAME [output_dir]

Downloads the official Windows MinGW SDL3, SDL3_image, SDL3_mixer and
SDL3_ttf development packages to the given folder (default: ./deps/SDL3).

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

release_url() {
  local repo="$1"
  local asset_prefix="$2"

  if [[ "$SDL3_VERSION" == "latest" ]]; then
    local json
    json="$(curl -fsSL \
      -H "Accept: application/vnd.github+json" \
      -H "User-Agent: WinFea" \
      "https://api.github.com/repos/libsdl-org/${repo}/releases/latest")"

    printf '%s\n' "$json" | python3 -c '
import json, sys

prefix = sys.argv[1].lower()
obj = json.loads(sys.stdin.read())
for asset in obj.get("assets", []):
    name = asset.get("name", "")
    lname = name.lower()
    if prefix in lname and "mingw" in lname and lname.endswith(".tar.gz"):
        print(asset["browser_download_url"])
        raise SystemExit
print("")
' "$asset_prefix"
  else
    printf '%s\n' "https://github.com/libsdl-org/${repo}/releases/download/${SDL3_VERSION}/${asset_prefix}-${SDL3_VERSION}-mingw.tar.gz"
  fi
}

mkdir -p "$OUT_DIR"
TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

for component in \
  "SDL3:SDL:SDL3" \
  "SDL3_image:SDL_image:SDL3_image" \
  "SDL3_mixer:SDL_mixer:SDL3_mixer" \
  "SDL3_ttf:SDL_ttf:SDL3_ttf"; do
  IFS=':' read -r package repo asset_prefix <<< "$component"
  ASSET_URL="$(release_url "$repo" "$asset_prefix")"

  if [[ -z "$ASSET_URL" ]]; then
    echo "Error: could not find a MinGW ${package} archive for ${SDL3_VERSION}." >&2
    exit 1
  fi

  pkg_dir="$TMP_DIR/$package"
  mkdir -p "$pkg_dir"

  curl -fL --retry 3 --output "$pkg_dir/archive.tar.gz" "$ASSET_URL"
  tar -xzf "$pkg_dir/archive.tar.gz" -C "$pkg_dir"

  EXTRACTED_ROOT="$(find "$pkg_dir" -mindepth 1 -maxdepth 1 -type d | head -n 1)"
  if [[ -z "$EXTRACTED_ROOT" ]]; then
    echo "Error: the ${package} archive did not extract to a directory." >&2
    exit 1
  fi

  cp -a "$EXTRACTED_ROOT"/. "$OUT_DIR"/
done

PREFIX_HINT=""
if [[ -d "$OUT_DIR/x86_64-w64-mingw32" ]]; then
  PREFIX_HINT="$OUT_DIR/x86_64-w64-mingw32"
fi

cat <<EOF
SDL3, SDL3_image, SDL3_mixer and SDL3_ttf downloaded successfully.
Location: $OUT_DIR

CMake example:
  cmake -DCMAKE_TOOLCHAIN_FILE=mingw-cmake/mingw-toolchain.cmake \
        -DCMAKE_PREFIX_PATH="$PREFIX_HINT" \
        ..

If your SDL package uses a different root directory, point CMAKE_PREFIX_PATH to the
folder that contains lib/cmake/SDL3 (or SDL_image, SDL_mixer, SDL_ttf) or the
x86_64-w64-mingw32 directory.
EOF
