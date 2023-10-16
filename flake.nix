{
  description = "Tester";

  inputs = {
    nixpkgs.url = "nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }: {
    overlays.default = final: _: {
      cmput415-Tester = final.stdenv.mkDerivation {
        pname = "cmput415-Tester";
        version = "0.1.0";
        src = builtins.path { path = ./.; name = "cmput415-Tester-src"; };
        nativeBuildInputs = [ final.cmake ];
        installPhase = ''
          runHook preInstall

          install -D ../bin/tester $out/bin/tester

          runHook postInstall
        '';
      };
    };
  } // utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        overlays = [ self.overlays.default ];
        inherit system;
      };
      inherit (pkgs) cmake cmput415-Tester mkShell;
    in
    {
      packages.default = cmput415-Tester;

      devShells.default = mkShell {
        packages = [ cmake ];
      };
    });
}
