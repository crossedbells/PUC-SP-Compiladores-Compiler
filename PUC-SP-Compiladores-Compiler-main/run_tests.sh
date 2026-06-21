#!/usr/bin/env bash
set -euo pipefail

COMPILER="./minipasc"
TESTS_DIR="./tests"
PASS=0
FAIL=0

RED='\033[0;31m'; GREEN='\033[0;32m'; NC='\033[0m'

pass() { echo -e "${GREEN}[PASS]${NC} $1"; ((PASS++)); }
fail() { echo -e "${RED}[FAIL]${NC} $1"; ((FAIL++)); }

run_test() {
    local name="$1"
    local src="${TESTS_DIR}/${name}.pas"
    local bin="${TESTS_DIR}/${name}"
    local args="${2:-}"
    local expected="$3"

    if [[ ! -f "$src" ]]; then
        fail "${name}: source not found (${src})"
        return
    fi

    # compile
    if ! "${COMPILER}" -o "${bin}" "${src}" 2>/tmp/compile_err; then
        fail "${name}: compile error — $(cat /tmp/compile_err)"
        return
    fi

    # run
    local actual
    actual=$(${bin} ${args} 2>&1) || true

    if [[ "$actual" == "$expected" ]]; then
        pass "${name} [args: ${args:-<none>}]"
    else
        fail "${name} [args: ${args:-<none>}]"
        echo "    expected: $(echo "$expected" | head -3)"
        echo "    actual  : $(echo "$actual"   | head -3)"
    fi
}

echo "══════════════════════════════════════════"
echo " Mini-Pascal Compiler — Test Suite"
echo "══════════════════════════════════════════"

# ── factor ───────────────────────────────────
run_test "factor" "84"  "2 2 3 7"
run_test "factor" "1"   "1"
run_test "factor" "97"  "97"

# ── isprime ──────────────────────────────────
run_test "isprime" "7"   "true"
run_test "isprime" "10"  "false"
run_test "isprime" "2"   "true"
run_test "isprime" "1"   "false"

# ── fibonacci ────────────────────────────────
run_test "fibonacci" "1"   "1"
run_test "fibonacci" "7"   "13"
run_test "fibonacci" "10"  "55"

# ── pidigits ─────────────────────────────────
run_test "pidigits" "5"   "31415"
run_test "pidigits" "1"   "3"

echo "══════════════════════════════════════════"
echo " Results: ${PASS} passed, ${FAIL} failed"
echo "══════════════════════════════════════════"

[[ $FAIL -eq 0 ]]
