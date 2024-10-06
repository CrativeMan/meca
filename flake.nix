{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { self
    , nixpkgs
    , flake-utils
    ,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in
      with pkgs; {
        formatter = pkgs.alejandra;
        devShell = mkShell.override { stdenv = clangStdenv; } {
          packages = [
            clang-tools
            llvmPackages.clangUseLLVM
            gcc
            clang
            cmake
						ncurses
          ];
        };

        defaultPackage = stdenv.mkDerivation {
          name = "meca";
          src = ./.;
          buildInputs = [ gcc ];
          buildPhase = ''
            mkdir -p build
            make
            cp meca build/meca
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp build/meca $out/bin/
          '';

        };
      }
    );
}
