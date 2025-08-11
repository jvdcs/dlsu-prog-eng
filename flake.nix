{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/25.05";
  };

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells.${system}.default = pkgs.mkShell {
      name = "cproj";
      packages =
        (with pkgs.rustPackages; [
          cargo
          rustc
          clippy
          rustfmt
        ])
        ++ (with pkgs; [
          rust-analyzer
          gcc
          clang-tools
        ])
        ++ (with pkgs.llvmPackages;[
          lldb
        ]);
      shellHook = ''
        echo "";
        echo "[C+Rust]";
        echo "";
      '';
    };
  };
}
