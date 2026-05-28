cargo build --release --manifest-path quick_migrate/Cargo.toml

cmake -S . -B build

cmake --build build --config Release

mv build/Anoncord bot