{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/25.05";
  };

  outputs = {
    nixpkgs,
    ...
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells.${system}.default = pkgs.mkShell {
      name = "cproj";
      packages = with pkgs; [
        gcc
        clang-tools
      ];
      shellHook = ''
        echo "welcome to c!";
      '';
    };
  };
}
