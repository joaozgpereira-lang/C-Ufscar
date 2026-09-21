#!/usr/bin/env bash
# Instala a extensão "std:: Autocomplete" no Codespace (VS Code remoto).
# Rode de novo se o Codespace for reconstruído:
#   bash tools/install-ext.sh
set -euo pipefail

SRC="$(cd "$(dirname "$0")/std-autocomplete" && pwd)"
DEST="$HOME/.vscode-remote/extensions/local.std-autocomplete"

mkdir -p "$(dirname "$DEST")"
rm -rf "$DEST"
cp -r "$SRC" "$DEST"

echo "Extensão instalada em: $DEST"
echo
echo "Depois, recarregue a janela do VS Code:"
echo "  Ctrl+Shift+P -> Developer: Reload Window"